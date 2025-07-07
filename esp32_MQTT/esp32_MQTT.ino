#include <WiFi.h>
#include <PicoMQTT.h> // Ensure this library is installed

#define WIFI_SSID "Luminar_Ruckus4"        // Your WiFi SSID
#define WIFI_PASSWORD "space_bar"       // Your WiFi password
#define LED_PIN 2                      // ESP32 onboard LED (confirm this pin for your board)

// Define your custom MQTT server class for authentication
class MyMQTTServer : public PicoMQTT::Server {
protected:
  // This is the correct method to override for authentication in PicoMQTT::Server
  PicoMQTT::ConnectReturnCode auth(const char *client_id, const char *username, const char *password) override {
    Serial.println("auth() called");
    if (!username || !password) {
      return PicoMQTT::CRC_NOT_AUTHORIZED;
    }

    if ((String(username) == "alice" && String(password) == "secret") ||
        (String(username) == "bob" && String(password) == "password")) {
      Serial.println("MQTT Auth accepted");
      return PicoMQTT::CRC_ACCEPTED;
    }

    Serial.println("MQTT Auth rejected");
    return PicoMQTT::CRC_BAD_USERNAME_OR_PASSWORD;
  }
};

// Create a single instance of your custom MQTT server
MyMQTTServer mqtt;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Ensure LED is off initially

  Serial.printf("Connecting to WiFi: %s\n", WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.printf("\nWiFi connected, IP: %s\n", WiFi.localIP().toString().c_str());

  mqtt.begin();
  Serial.println("MQTT server started");

  // *** IMPORTANT: Subscribe to the topic using a lambda function with the correct signature ***
  // The lambda will be called when a message is received on the "led" topic
  mqtt.subscribe("led", [](char *topic_ptr, PicoMQTT::IncomingPacket& packet) {
    Serial.println("Lambda handleMqttMessage called"); // For debugging

    String topic = String(topic_ptr);

    // *** CORRECTED PAYLOAD READING HERE ***
    // Read the payload from the IncomingPacket stream
    size_t payload_len = packet.get_remaining_size(); // Get the total size of the payload
    char payload_buffer[payload_len + 1]; // Create a buffer big enough for payload + null terminator
    packet.read((uint8_t*)payload_buffer, payload_len); // Read payload bytes into the buffer
    payload_buffer[payload_len] = '\0'; // Null-terminate the string

    String msg = String(payload_buffer); // Create String from the null-terminated buffer

    Serial.printf("Received on topic [%s]: %s\n", topic.c_str(), msg.c_str());

    if (topic == "led") {
      if (msg == "on") {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("LED turned ON");
      } else if (msg == "off") {
        digitalWrite(LED_PIN, LOW);
        Serial.println("LED turned OFF");
      } else {
        Serial.printf("Unknown command for LED: %s\n", msg.c_str());
      }
    }
  });

  Serial.println("MQTT server subscribed to 'led' topic with lambda callback");
}

void loop() {
  mqtt.loop();  // Run the MQTT server loop
}