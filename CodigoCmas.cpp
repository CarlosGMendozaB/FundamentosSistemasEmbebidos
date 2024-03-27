#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>

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
    const std::vector<int> gpios = {27, 22, 17, 4, 18, 23, 24, 25};

    if (command == "cerrar") {
        for (int gpio : gpios) {
            std::cout << "Cerrando el GPIO " << gpio << std::endl;
            unexportGPIO(gpio);
        }
    } else if (command == "valor") {
        const int n = 100; // Número de experimentos
        std::ofstream tiempo_file("tiempo.txt", std::ios::app);
        std::ofstream valor_file("valor.txt", std::ios::app);

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
            if (tiempo_file.is_open() && valor_file.is_open()) {
                tiempo_file << duration << std::endl;
                valor_file << numero << std::endl;
            }
        }
    }

    return 0;
}

