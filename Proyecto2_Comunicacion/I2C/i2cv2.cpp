#include <iostream>
#include <wiringPiI2C.h>
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <unistd.h> // Para la función sleep

#define DEVICE_ID 0x08

int main (int argc, char **argv)
{
    // Setup I2C communication
    int fd = wiringPiI2CSetup(DEVICE_ID);
    if (fd == -1) {
        std::cout << "Failed to init I2C communication.\n";
        return -1;
    }
    std::cout << "I2C communication successfully setup.\n";

    // Send data to arduino
   // uint8_t data_to_send = 17;
   // wiringPiI2CWrite(fd, data_to_send);
   // std::cout << "Sent data: " << (int)data_to_send << "\n"
   // ;


    // Read data from arduino

    std::ofstream tiempo_file("tiempoI2C.txt", std::ofstream::out|std::ofstream::trunc);
    std::ofstream valor_file("valorI2C.txt", std::ofstream::out|std::ofstream::trunc);
    int received_data = wiringPiI2CRead(fd);
 
    for(int i=1;i<=1000;i++){
    //   std::cout<<i<<std::endl;
       for(int j=0;j<8;++j){
          received_data = wiringPiI2CRead(fd);
          //std::cout << "Data received: " << received_data << "\n";
    	  auto t = std::chrono::high_resolution_clock::now();
    	  auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t.time_since_epoch()).count();

    	  // std::cout << i << std::endl;
    	  tiempo_file.open("tiempoI2C.txt",std::ofstream::out|std::ofstream::app);
    	  valor_file.open("valorI2C.txt",std::ofstream::out|std::ofstream::app);
    	  if (tiempo_file.is_open() && valor_file.is_open()) {
          	tiempo_file << duration << std::endl;
          	valor_file << received_data << std::endl;
    	}
	    
    tiempo_file.close();
    valor_file.close();
       }
    }

    //if (received_data == data_to_send) {
      //  std::cout << "Success!\n";
   // }
    return 0;
}
