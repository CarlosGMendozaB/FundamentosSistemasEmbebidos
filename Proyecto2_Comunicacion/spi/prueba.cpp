#include <iostream>
#include <fstream>
#include <wiringPiSPI.h>

using namespace std;

#define CHANNEL 0 // Canal SPI (puedes ajustarlo según tus conexiones)

int main(int argc, char **argv) {
  // Inicializar la comunicación SPI
  if (wiringPiSPISetup(CHANNEL, 500000) == -1) {
    cerr << "Failed to initialize SPI communication." << endl;
    return -1;
  }
  cout << "SPI communication successfully set up." << endl;

  ofstream yfile;
  yfile.open("y.txt");

  ofstream timeFile;
  timeFile.open("timeFile.txt");

  int N = 1000; // Número de iteraciones

  for (int i = 0; i < N; i++) {
    unsigned char txData[1] = {0x00}; // Datos a enviar (1 byte)
    unsigned char rxData[1] = {0x00}; // Datos recibidos (1 byte)

    // Realizar la transferencia SPI
    wiringPiSPIDataRW(CHANNEL, txData, 1);

    timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    double timestamp_seconds = static_cast<double>(ts.tv_sec) + static_cast<double>(ts.tv_nsec) / 1000000000.0;
    timeFile << std::fixed << timestamp_seconds << std::endl;

    yfile << static_cast<int>(rxData[0]) << "\n";
  }

  yfile.close();
  timeFile.close();

  return 0;
}
