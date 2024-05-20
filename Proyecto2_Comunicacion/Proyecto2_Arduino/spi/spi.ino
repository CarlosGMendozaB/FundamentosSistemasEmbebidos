#include <SPI.h>

#define SS_PIN 10 // Pin de selección del esclavo (slave select)
const int numPines = 8; // Número de pines que deseas leer
int pines[numPines] = {2, 3, 4, 5, 6, 7, 8, 9}; // Definir los pines que deseas leer

void setup() {
  SPI.begin(); // Inicia la comunicación SPI
  pinMode(SS_PIN, OUTPUT); // Configura el pin SS como salida
  digitalWrite(SS_PIN, HIGH); // Desactiva el esclavo inicialmente
}

void loop() {
  // Envía el estado de cada pin digital a través de SPI
  for (int i = 0; i < numPines; ++i) {
    digitalWrite(SS_PIN, LOW); // Activa el esclavo
    SPI.transfer(digitalRead(pines[i])); // Envía el estado del pin
    digitalWrite(SS_PIN, HIGH); // Desactiva el esclavo
//    delay(10); // Breve retraso entre envíos
  }
  
  // Espera un tiempo antes de la próxima lectura
 // delay(1000);
}
