#include <iostream>
#include <fstream>
#include <wiringPiI2C.h>

using namespace std; 

#define DEVICE_ID 0x08

int main (int argc, char **argv)
{
  //Setup I2C commbnication
  int fd_comm = wiringPiI2CSetup(DEVICE_ID);


  ofstream yfile;
  yfile.open("y.txt"); 

  ofstream timeFile;
  timeFile.open("timeFile.txt"); 

  if (fd_comm == -1) {
    std::cout << "Failed to init I2C communication \n";
    return -1;
  }
  std::cout << "I2C communication successfully setup \n";
 
  int received_data = wiringPiI2CRead(fd_comm);
  int N = 1000; //Numero de iteaciones

  
  for (int i=0; i<N; i++){
    received_data = wiringPiI2CRead(fd_comm);
    timespec ts;
  clock_gettime(CLOCK_REALTIME,&ts);
  double timestamp_seconds = static_cast<double>(ts.tv_sec) + static_cast<double>(ts.tv_nsec)/1000000000.0;
  timeFile << std::fixed << timestamp_seconds << std::endl;
    yfile << received_data << "\n";
  }
  yfile.close();
  timeFile.close();
  return 0;
}
