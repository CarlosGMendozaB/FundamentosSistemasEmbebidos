const int numPins = 8;
int pins[numPins] = {2, 3, 4, 5, 6, 7, 8, 9};
int values[numPins];

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < numPins; i++) {
    pinMode(pins[i], INPUT);
  }
}

void loop() {
  for (int i = 0; i < numPins; i++) {
    values[i] = digitalRead(pins[i]);
    Serial.println(values[i]);
  }

  //Serial.println();
 // delay(1000);
}
