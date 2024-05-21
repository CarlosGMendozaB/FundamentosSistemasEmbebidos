import matplotlib.pyplot as plt

# Nombre de los archivos de texto
archivo_x = 'iteracion.txt'
archivo_y = 'deltaTCP-IP.txt'

# Listas para almacenar los valores de los ejes x e y
valores_x = []
valores_y = []

# Leer los valores de los archivos
with open(archivo_x, 'r') as file_x, open(archivo_y, 'r') as file_y:
    for linea_x, linea_y in zip(file_x, file_y):
        valor_x = float(linea_x.strip())
        valor_y = float(linea_y.strip())
        valores_x.append(valor_x)
        valores_y.append(valor_y)

# Graficar los valores
plt.plot(valores_x, valores_y, marker='o', linestyle='-')
plt.xlabel('Iteracion')
plt.ylabel('Delta time')
plt.title('Ejecucion Iteracion - Delta  (TCP/IP)')
plt.grid(True)

# Mostrar el grafico
plt.show()
