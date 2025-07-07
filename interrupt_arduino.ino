const int irSensorPin = 14; 

void setup() {
  Serial.begin(115200);
  pinMode(irSensorPin, INPUT);

  Serial.println("Execution started. Waiting for 10 seconds...");
  unsigned long startTime = millis();

  while (millis() - startTime < 10000) { 
    if (digitalRead(irSensorPin) == LOW) { 
      Serial.println("Object detected!");
      return; 
    }
    delay(100); 
  }

  Serial.println("No object detected in 10 seconds.");
}

void loop() {
  
}
