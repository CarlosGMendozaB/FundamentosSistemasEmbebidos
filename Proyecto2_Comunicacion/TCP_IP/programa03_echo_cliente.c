#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <wiringPi.h>
#include <wiringSerial.h> // Para la comunicación UART
// using namespace std;

#define DEVICE_PORT "/dev/ttyACM0" // Puerto UART predeterminado en Raspberry Pi
#define BAUD_RATE 9600 // Velocidad de baudios para la comunicación UART
#define SOCK_PATH "echo_socket"

int main(void)
{
// Inicializa la biblioteca WiringPi
   if (wiringPiSetup() == -1) {
        fprintf(stderr, "Failed to initialize WiringPi library\n");
        return 1;
   }

    // Abre la comunicación UART
  int fd_comm = serialOpen(DEVICE_PORT, BAUD_RATE);
  if (fd_comm == -1) {
        fprintf(stderr, "Failed to open UART communication\n");
        return 1;
    }

  printf("UART communication successfully setup\n");
  int s, t, len;
  struct sockaddr_un remote;
  char str[100];

  if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
  {
    perror("socket");
    exit(1);
  }

  printf("Trying to connect...\n");
  remote.sun_family = AF_UNIX;
  strcpy(remote.sun_path, SOCK_PATH);
  len = strlen(remote.sun_path) + sizeof(remote.sun_family);

  if (connect(s, (struct sockaddr *)&remote, len) == -1)
  {
    perror("connect");
    exit(1);
  }

  printf("Connected.\n");
  for(int i=0;i<10000;i++){
   int n = read(fd_comm, str, sizeof(str) - 1);
        if (n > 0)
        {
            str[n] = '\0';  // Asegura que el buffer está terminado en nulo

  while(printf("> "), fgets(str, 100, stdin), !feof(stdin))
  {
    if (send(s, str, strlen(str), 0) == -1)
    {
      perror("send");
      exit(1);
    }

    if ((t=recv(s, str, 100, 0)) > 0)
    {
      str[t] = '\0';
      printf("%s", str);
    }
    else
    {
      if (t < 0)
        perror("recv");
      else
        printf("Server closed connection\n");
      exit(1);
    }
  }
  close(s);
  return 0;
 }
}
}
