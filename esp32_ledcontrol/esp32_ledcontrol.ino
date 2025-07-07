#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "HUWAI-EXT";         
const char* password = "chiramal5598"; 

const int ledPin = 2;

WebServer server(80);


String htmlPage() {
  String html = "<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  html += "<style>body{font-family:Arial;text-align:center;}button{padding:20px;margin:10px;font-size:20px;}</style></head><body>";
  html += "<h1>ESP32 LED Control</h1>";
  html += "<p><a href=\"/on\"><button style=\"background-color:green;color:white;\">ON</button></a>";
  html += "<a href=\"/off\"><button style=\"background-color:red;color:white;\">OFF</button></a></p>";
  html += "</body></html>";
  return html;
}

void handleRoot() {
  server.send(200, "text/html", htmlPage());
}

void handleOn() {
  digitalWrite(ledPin, HIGH);
  server.send(200, "text/html", htmlPage());
}

void handleOff() {
  digitalWrite(ledPin, LOW);
  server.send(200, "text/html", htmlPage());
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); 

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);

  server.begin();
  Serial.println("Web server running...");
}

void loop() {
  server.handleClient();
}