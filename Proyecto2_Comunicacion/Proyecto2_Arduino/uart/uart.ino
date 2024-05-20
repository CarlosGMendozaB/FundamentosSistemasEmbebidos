void setup() {
  Serial.begin(9600);
 for (int i = 2; i <= 9; i++) {
    pinMode(i, INPUT);
  }
}

void loop() {
 // Serial.print(1);
//  delay(1000);
  for (int i = 2; i <= 9; i++) {
    int pinValue = digitalRead(i);
    // Enviar el valor del pin actual por el puerto serial
    Serial.print(pinValue);
  }
 //Serial.println();
}
