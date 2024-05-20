#include <iostream>
#include <wiringPiSPI.h>
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <unistd.h> // Para la función sleep

#define CHANNEL 0
#define SPEED 1000000 // Velocidad de la comunicación SPI en Hz

int main() {
    // Inicia la comunicación SPI en la Raspberry Pi
    int fd = wiringPiSPISetup(CHANNEL, SPEED);
    //std::cout << "Valor de fd: " << fd << std::endl;
    if (fd == -1) {
        std::cerr << "Error al inicializar la comunicación SPI." << std::endl;
        return 1;
    }
    std::cout << "SPI communication successfully setup.\n";
    // Lee datos desde el Arduino a través de SPI
    std::ofstream tiempo_file("tiempoSPI.txt", std::ofstream::out|std::ofstream::trunc);
    std::ofstream valor_file("valorSPI.txt", std::ofstream::out|std::ofstream::trunc);
    for(int j=1;j<=10000;j++){
        for (int i = 0; i < 8; ++i) {
            unsigned char received_data;
            wiringPiSPIDataRW(CHANNEL, &received_data, 1);
            //std::cout << "Estado del pin " << i << ": " << static_cast<int>(received_data) << std::endl;
        
            auto t = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t.time_since_epoch()).count();

            //std::cout << i << std::endl;
	    tiempo_file.open("tiempoSPI.txt",std::ofstream::out|std::ofstream::app);
	    valor_file.open("valorSPI.txt",std::ofstream::out|std::ofstream::app);
            if (tiempo_file.is_open() && valor_file.is_open()) {
                tiempo_file << duration << std::endl;
                //valor_file <<static_cast<int>(received_data) << std::endl;
            }
	    
	    tiempo_file.close();
	    valor_file.close();
        }
    }

    return 0;
}

