import socket
import sys

# Definimos el tamaño del búfer
BLEN = 128

# Obtenemos la dirección IP y el puerto del servidor de los argumentos de la línea de comandos
host = sys.argv[1]
port = int(sys.argv[2])

# Creamos el socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Conectamos al servidor
sock.connect((host, port))

# Enviamos un mensaje al servidor
mensaje = "Mendoza Bolaños Carlos Gabriel"
sock.send(mensaje.encode())

# Recibimos la respuesta del servidor
data = sock.recv(BLEN)
while data:
    sys.stdout.write(data.decode())
    data = sock.recv(BLEN)

# Cerramos el socket
sock.close()
