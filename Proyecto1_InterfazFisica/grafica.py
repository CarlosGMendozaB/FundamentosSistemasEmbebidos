import turtle

# Inicializar la pantalla de dibujo
screen = turtle.Screen()
screen.setup(width=600, height=600)
screen.title("Gráfico de dispersión con Turtle")

# Crear un objeto Turtle
t = turtle.Turtle()

# Cargar datos del archivo1 (eje X)
with open('delta.txt') as file1:
    x_data = [float(line.strip()) for line in file1.readlines()]

# Cargar datos del archivo2 (eje Y)
with open('valor.txt') as file2:
    y_data = [float(line.strip()) for line in file2.readlines()]

# Escalar los datos para que quepan en la pantalla
max_x = max(x_data)
max_y = max(y_data)
scale_factor = min(500 / max_x, 500 / max_y)

# Dibujar los puntos en el gráfico
t.penup()
for x, y in zip(x_data, y_data):
    t.goto(x * scale_factor, y * scale_factor)
    t.dot(5)  # Dibujar un punto
    t.write(f'({x}, {y})', align='left')  # Mostrar las coordenadas de cada punto
t.hideturtle()

# Mantener la ventana abierta
screen.mainloop()
