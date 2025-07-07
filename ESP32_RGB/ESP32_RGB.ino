#define BLYNK_TEMPLATE_ID "TMPL3ccgWAFbi"
#define BLYNK_TEMPLATE_NAME "RGB"
#define BLYNK_AUTH_TOKEN "JZUetuDa4j3KQ9mR4_U5BXWO9J6o2ODQ"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Luminar_Ruckus4";
char pass[] = "space_bar";

// Define RGB Pins
#define RED_PIN 25
#define GREEN_PIN 26
#define BLUE_PIN 27

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  
  // Turn off initially
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
}

// Red control
BLYNK_WRITE(V2) {
  int state = param.asInt();
  digitalWrite(RED_PIN, state);
  Serial.println(state ? "Red ON" : "Red OFF");
}

// Green control
BLYNK_WRITE(V3) {
  int state = param.asInt();
  digitalWrite(GREEN_PIN, state);
  Serial.println(state ? "Green ON" : "Green OFF");
}

// Blue control
BLYNK_WRITE(V4) {
  int state = param.asInt();
  digitalWrite(BLUE_PIN, state);
  Serial.println(state ? "Blue ON" : "Blue OFF");
}

void loop() {
  Blynk.run();
}
