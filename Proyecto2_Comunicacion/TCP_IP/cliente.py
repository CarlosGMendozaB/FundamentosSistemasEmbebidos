import socket
import serial
import sys
import time

# Definimos el tamaño del búfer
BLEN = 128

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout = 1)
    print(ser)
    ser.reset_input_buffer()

  #  s = socket.socket()
  #  host ='192.168.100.130' #192.168.100.27Introducir la IP de raspberry
  #  port = 4897#12345
   # s.sbind((host, port))
    host = sys.argv[1]
    port = int(sys.argv[2])

# Creamos el socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    #s.listen(5)

 #   while True:
       # if ser.in_waiting > 0:
   # line = ser.readline().rstrip()#.decode('utf-8').rstrip()
    sock.connect((host, port))
#    print(sock.connect((host, port)))

# Enviamos un mensaje al servidor
    #mensaje = "Mendoza Bolaños Carlos Gabriel"
   # for i in range(10000):
        #print(i)
    #    for j in range (0,8):
          # if ser.in_waiting > 0:
     #        t = time.time_ns()
      #       try:
    count=0
    while True:
         line = ser.readline().rstrip()#decode('utf-8').rstrip()
         if line:
            # count+=1
             print("La variable line tiene: ",line)
            # print(count)
             sock.send(line)
               #data_str =line.decode('utf-8')
#               print(line)
     #        except UnicodeDecodeError as e:
      #           pass

# Recibimos la respuesta del servidor
             data = sock.recv(BLEN)
             while data:
                print("Hola") 
                sys.stdout.write(data.decode())
                data = sock.recv(BLEN)
         else:
             print("no")

# Cerramos el socket
    sock.close()    #    print(line)oo
   # data_to_send = "Hola, servidor"
   # s.send(data_to_send)
   # print("Datos enviados al servidor:", data_to_send)
           # s.recv(1024)
   # s.close

   #         c,addr = s.accept()
    #        print('Got conetion from', addr)
     #       c.send(line)
      #      c.close()
    
