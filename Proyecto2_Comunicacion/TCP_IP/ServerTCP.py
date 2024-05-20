import socket
import time
import os

# Definimos el puerto y el número máximo de conexiones pendientes
PORT = 4897
QLEN = 200

# Creamos el socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Asociamos el socket a la dirección y puerto
servidor = ('', PORT)
sock.bind(servidor)

# Escuchamos conexiones
sock.listen(QLEN)

# Contador de alumnos
num_alumnos = 0

# Bucle principal
while True:
    # Aceptamos una conexión
    conn, addr = sock.accept()

    # Obtenemos la dirección IP del cliente
    ip_cliente = addr[0]
    print(ip_cliente)

    # Incrementamos el contador de alumnos
   # num_alumnos += 1

    #Abrimos archivo para leer tiempo
    with open("tiempoPy.txt", 'w') as tiempo_file:
         tiempo_file.write("")
    with open("alumnos.txt", 'w') as alumno_file:
         alumno_file.write("")
    count=0     
    # Recibimos los datos del cliente
    for i in range (10000):
        for j in range(0,8):
            
             data = conn.recv(528)
             t = time.time_ns()
            # print("El valor reciobido es: ",data)
             #Cargamos el tiempo al erchivo
             count+=1
             with open("tiempoPy.txt", 'a') as tiempo_file:

                tiempo_file.write(f"{t}\n")
                 # Obtenemos la fecha y hora actuales
                t = time.localtime()
                fecha_hora = f"{num_alumnos} : {ip_cliente} - {t.tm_mday}/{t.tm_mon + 1}/{t.tm_year} {t.tm_hour}:{t.tm_min}:{t.tm_sec}-"
               # print(fecha_hora)

             # Abrimos el archivo para escribir
             with open("alumnos.txt", "a") as f:
             # Escribimos la fecha y hora en el archivo
                 f.write(fecha_hora)
                 #f.write(str(data))
             # Escribimos el nombre del alumno en el archivo
                # print("El valor de f.write es: ",f.write(data.decode("ascii",errors="replace")))#,errors="ignore"))
             #f.write(data)#,errors="ignore"))
             # Saltamos una línea
                 f.write("\n")
             print(count)    

    # Enviamos una respuesta al cliente
             respuesta = "Alumno/Alumna registrado/registrada"
             conn.send(respuesta.encode())
             conn.send(respuesta.encode())

    # Cerramos la conexión
    conn.close()

    # Dormimos 60 segundos
    time.sleep(60)

    # Si se han registrado 50 alumnos, cerramos el socket
   # if num_alumnos >= 50:
    #    sock.close()
     #   break

# Cerramos el socket
sock.close()

