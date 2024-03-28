import os
import time

# GPIO utilizados para generar numero
GPIO_0 = 27
GPIO_1 = 22
GPIO_2 = 17
GPIO_3 = 4
GPIO_4 = 18
GPIO_5 = 23
GPIO_6 = 24
GPIO_7 = 8

# Función para exportar un GPIO
def export_gpio(gpio):
    with open(f"/sys/class/gpio/export", 'w') as file:
        file.write(str(gpio))

# Función para configurar la dirección de un GPIO
def set_direction(gpio, direction):
    with open(f"/sys/class/gpio/gpio{gpio}/direction", 'w') as file:
        file.write(direction)

# Función para desexportar un GPIO
def unexport_gpio(gpio):
    with open(f"/sys/class/gpio/unexport", 'w') as file:
        file.write(str(gpio))

# Función para leer el valor de un GPIO
def read_gpio(gpio):
    with open(f"/sys/class/gpio/gpio{gpio}/value", 'r') as file:
        return file.read().strip()

# Verificar si se pasó algún valor
if len(os.sys.argv) != 2:
    print("No hay comando")
    print("Los comandos a utilizar son config, valor, cerrar")
    os.sys.exit(2)  # Número inválido de argumentos

# Configurar GPIO como entradas
if os.sys.argv[1] == "config":
    for gpio in [GPIO_0, GPIO_1, GPIO_2, GPIO_3, GPIO_4, GPIO_5, GPIO_6, GPIO_7]:
        print(f"Exportando GPIO número {gpio}")
        export_gpio(gpio)
        time.sleep(1)  # para asegurar que se exportó correctamente
        print(f"Configurando GPIO número {gpio} como entrada")
        set_direction(gpio, "in")

# Cerrar GPIO
elif os.sys.argv[1] == "cerrar":
    for gpio in [GPIO_0, GPIO_1, GPIO_2, GPIO_3, GPIO_4, GPIO_5, GPIO_6, GPIO_7]:
        print(f"Cerrando el GPIO {gpio}")
        unexport_gpio(gpio)

# Leer valor de los GPIO
elif os.sys.argv[1] == "valor":
    n = 100  # Números de experimentos
    with open("tiempoPy.txt", 'w') as tiempo_file:
         tiempo_file.write("")
    with open("valorPy.txt", 'w') as valor_file:
          valor_file.write("")
    for i in range(n):
        bits = [read_gpio(gpio) for gpio in [GPIO_0, GPIO_1, GPIO_2, GPIO_3, GPIO_4, GPIO_5, GPIO_6, GPIO_7]]
        numero = sum(int(bit) for bit in bits)
        t = time.time_ns()
        # Visualización de cada valor individual
        for bit in bits:
            print(bit)
        print(i)
        with open("tiempoPy.txt", 'a') as tiempo_file:
            tiempo_file.write(f"{t}\n")
        with open("valorPy.txt", 'a') as valor_file:
            valor_file.write(f"{numero}\n")

