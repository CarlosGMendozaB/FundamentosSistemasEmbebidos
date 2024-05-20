#include <SPI.h>

// Definir los pines de selección de esclavo (Slave Select, SS)
const int slaveSelectPin = 10; // Puedes usar cualquier pin digital para SS

const int pines[8] = {2, 3, 4, 5, 6, 7, 8, 9};
int i;

void setup() {
  Serial.begin(9600);
  SPI.begin(); // Inicializar la comunicación SPI
  pinMode(slaveSelectPin, OUTPUT); // Configurar el pin SS como salida

  for (i = 0; i <= 7; i++) {
    pinMode(pines[i], INPUT);
  }
}
void loop() {
  int valor = 0;
  for (i = 0; i <= 7; i++) {
    int valori = digitalRead(pines[i]);
    valor += valori;
    Serial.print(valori);
  }
  Serial.println();
  Serial.println(valor);

  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);

  // Seleccionar el esclavo (activar el SS correspondiente)
  digitalWrite(slaveSelectPin, LOW);

  // Enviar datos al esclavo a través de SPI (puedes usar SPI.transfer())
  SPI.transfer(valor);
  SPI.transfer(sensorValue);

  // Deseleccionar el esclavo
  digitalWrite(slaveSelectPin, HIGH);

  delay(100);
}
