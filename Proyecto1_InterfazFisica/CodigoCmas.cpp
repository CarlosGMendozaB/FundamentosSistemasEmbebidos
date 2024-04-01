#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <unistd.h> // Para la función sleep

// Función para exportar un GPIO y configurarlo como entrada
void exportAndConfigureGPIO(int gpio) {
    std::ofstream file;
    file.open("/sys/class/gpio/export");
    if (file.is_open()) {
        file << gpio;
        file.close();
        sleep(1); // Esperar 1 segundo para asegurar que se exportó correctamente
        file.open("/sys/class/gpio/gpio" + std::to_string(gpio) + "/direction");
        if (file.is_open()) {
            file << "in";
            file.close();
        } else {
            std::cerr << "No se pudo configurar la dirección del GPIO número " << gpio << std::endl;
        }
    } else {
        std::cerr << "No se pudo exportar el GPIO número " << gpio << std::endl;
    }
}
// Función para desexportar un GPIO
void unexportGPIO(int gpio) {
    std::ofstream file;
    file.open("/sys/class/gpio/unexport");
    if (file.is_open()) {
        file << gpio;
        file.close();
    } else {
        std::cerr << "No se pudo cerrar el GPIO número " << gpio << std::endl;
    }
}

// Función para leer el valor de un GPIO
int readGPIO(int gpio) {
    std::ifstream file;
    file.open("/sys/class/gpio/gpio" + std::to_string(gpio) + "/value");
    if (file.is_open()) {
        int value;
        file >> value;
        file.close();
        return value;
    } else {
        std::cerr << "No se pudo leer el valor del GPIO número " << gpio << std::endl;
        return -1;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " [config|cerrar|valor]" << std::endl;
        return 1;
    }

    std::string command = argv[1];
    const std::vector<int> gpios = {27, 22, 17, 4, 18, 23, 24,8};

    
    if (command == "config") {
        //const int gpios[] = {27, 22, 17, 4, 18, 23, 24, 25};
        for (int gpio : gpios) {
            std::cout << "Exportando GPIO número " << gpio << std::endl;
            exportAndConfigureGPIO(gpio);
        }
    }
    if (command == "cerrar") {
        for (int gpio : gpios) {
            std::cout << "Cerrando el GPIO " << gpio << std::endl;
            unexportGPIO(gpio);
        }
    } else if (command == "valor") {
        const int n = 101; // Número de experimentos
        std::ofstream tiempo_file("tiempoCm.txt", std::ofstream::out|std::ofstream::trunc);
        std::ofstream valor_file("valorCm.txt", std::ofstream::out|std::ofstream::trunc);

        for (int i = 0; i < n; ++i) {
            int numero = 0;
            for (int gpio : gpios) {
                int bit = readGPIO(gpio);
                std::cout << bit << std::endl;
                numero += bit;
            }

            auto t = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t.time_since_epoch()).count();

            std::cout << i << std::endl;
	    tiempo_file.open("tiempoCm.txt",std::ofstream::out|std::ofstream::app);
	    valor_file.open("valorCm.txt",std::ofstream::out|std::ofstream::app);
            if (tiempo_file.is_open() && valor_file.is_open()) {
                tiempo_file << duration << std::endl;
                valor_file << numero << std::endl;
            }
	    
	    tiempo_file.close();
	    valor_file.close();
        }
    }

    return 0;
}


