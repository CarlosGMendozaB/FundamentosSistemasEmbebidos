import matplotlib.pyplot as plt

# Nombre de los archivos de texto
archivo_x = 'PYx.txt'
archivo_y = 'PYy.txt'

# Listas para almacenar los valores de los ejes x e y
valores_x = []
valores_y = []

# Leer los valores de los archivos
with open(archivo_x, 'r') as file_x, open(archivo_y, 'r') as file_y:
    valores_x = [float(linea.strip()) for linea in file_x]
    valores_y = [float(linea.strip()) for linea in file_y]

# Graficar los valores con un estilo personalizado
plt.bar(valores_x, valores_y, color='teal')
plt.xlabel('Eje X')
plt.ylabel('Eje Y')
plt.title('Grafico de Barras Personalizado')
plt.grid(True)

# Mostrar el grafico
plt.show()
print("PRueba",valores_x)
print(valores_y)
