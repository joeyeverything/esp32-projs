#define BLYNK_TEMPLATE_ID "TMPL3o3Xl5rge"
#define BLYNK_TEMPLATE_NAME "ESP32 LED"

#define BLYNK_AUTH_TOKEN "4PCD-BcRjWukL7w_rgeQZ7aN-cbNzpQd"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "HUWAI-EXT";
char pass[] = "chiramal5598";

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);  // Usually GPIO 2 on ESP32
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

BLYNK_WRITE(V0) {
  int value = param.asInt();  // Get value from app
  digitalWrite(2, value);  // Turn LED on/off
}

void loop() {
  Blynk.run();
}

