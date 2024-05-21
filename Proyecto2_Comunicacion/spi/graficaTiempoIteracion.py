import matplotlib.pyplot as plt

# Nombre del archivo de texto
nombre_archivo = 'tiempoSPI.txt'

# Lista para almacenar los valores
valores_y = []

# Leer los valores del archivo
with open(nombre_archivo, 'r') as archivo:
    for linea in archivo:
        valor = float(linea.strip())
        valores_y.append(valor)

# Crear una lista de números de iteración para el eje x
valores_x = list(range(1, len(valores_y) + 1))

# Crear el gráfico
plt.plot(valores_x, valores_y, marker='o', linestyle='-')
plt.xlabel('Número de Iteración')
plt.ylabel('Tiempo de Lectura')
plt.title('Gráfico de Tiempo vs. Número de Iteración. i2c.')
plt.grid(True)

# Mostrar el gráfico
plt.show()
