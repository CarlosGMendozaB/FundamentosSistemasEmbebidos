import serial
import os
import time

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.reset_input_buffer()

    #while True:
    with open("tiempoUART.txt", 'w') as tiempo_file:
         tiempo_file.write("")
    with open("valorUART.txt", 'w') as valor_file:
          valor_file.write("")
    print("UART communication successfully set up")      
    count = 0  # Contador para el número de datos recibidos
    for i in range(10000):
        #print(i)
        for j in range (0,8):
          # if ser.in_waiting > 0:
             t = time.time_ns()
             try:
               line = ser.readline().rstrip()#decode('utf-8').rstrip()
               #data_str =line.decode('utf-8')
#               print(line)
             except UnicodeDecodeError as e:
                 pass

               #continue
        # Si ocurre un error al decodificar, imprime el error y los datos en formato hexadecimal
              # print("Error al decodificar:", e)
              # print("Datos en formato hexadecimal:",ser.hex())
             with open("tiempoUART.txt", 'a') as tiempo_file:
               tiempo_file.write(f"{t}\n")
             with open("valorUART.txt", 'a') as valor_file:
               valor_file.write(f"{line}\n")
          # else:    
             #print(count)

            # count+=1
