#define BLYNK_TEMPLATE_ID "TMPL3W4qv9tNj"
#define BLYNK_TEMPLATE_NAME "ESP32_Servo"
#define BLYNK_AUTH_TOKEN "lHTUR_IwPhBwM_U988oe3la0xutsY3Sc"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>

char ssid[] = "HUWAI-EXT";
char pass[] = "chiramal5598";

Servo myServo;

#define SERVO_PIN 13 

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  myServo.setPeriodHertz(50); 
  myServo.attach(SERVO_PIN, 500, 2400); 
}

BLYNK_WRITE(V1) {
  int angle = param.asInt();  
  myServo.write(angle);
  Serial.print("Servo Angle: ");
  Serial.println(angle);
}

void loop() {
  Blynk.run();
}

