#include <Wire.h>

#define SLAVE_ADDRESS 0x08
const int numPines = 8; // Número de pines que deseas leer
int pines[numPines] = {2, 3, 4, 5, 6, 7, 8, 9}; // Definir los pines que deseas leer

//byte data_to_echo = 0;

void setup() 
{
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);

 // Wire.onReceive(receiveData);
 // Wire.onRequest(sendData);
  for (int pin = 0; pin <numPines; pin++) {
    pinMode(pines[pin], INPUT);
  }
 // Serial.println("I2C");
}

void loop() { 

//void receiveData(int bytecount)
//{
  
  for (int pin= 0; pin <numPines; pin++) {
    int valor_pin=digitalRead(pines[pin]);
    //Serial.print("Pin ");
    //Serial.print(pines[pin]);
   // Serial.print(" ");
   // Serial.println(valor_pin);
    Wire.write(valor_pin);
   // data_to_echo = Wire.read();
    //Serial.print(data_to_echo);
  }
  delay(1000);
}

/*void sendData()
{
  Wire.write(data_to_echo);
}*/
