# Importamos las librerías que vamos a necesitar
import time
import os

# Definimos los pines GPIO que vamos a utilizar
GPIO_PINS = [27, 22, 23, 24, 5, 6, 13, 25]

# Función para exportar un pin GPIO
def export_pin(pin):
    with open("/sys/class/gpio/export", "w") as f:
        f.write(str(pin))

# Función para desexportar un pin GPIO
def unexport_pin(pin):
    with open("/sys/class/gpio/unexport", "w") as f:
        f.write(str(pin))

# Función para configurar un pin GPIO como entrada
def set_pin_direction_in(pin):
    path = "/sys/class/gpio/gpio{}/direction".format(pin)
    with open(path, "w") as f:
        f.write("in")

# Función para leer el valor de un pin GPIO
def read_pin_value(pin):
    path = "/sys/class/gpio/gpio{}/value".format(pin)
    with open(path, "r") as f:
        return int(f.read().strip())

# Función para obtener el valor binario de los pines GPIO
def obtener_valor():
    valor = 0
    for pin in GPIO_PINS:
        valor += read_pin_value(pin)
    return valor

# Función principal
def main():
    comando = input("Introduzca el comando (config, valor, cerrar): ")

    # Configuración de los pines GPIO
    if comando == "config":
        for pin in GPIO_PINS:
            export_pin(pin)
            set_pin_direction_in(pin)
        print("Pines GPIO configurados correctamente.")

    # Obtención del valor binario de los pines GPIO
    elif comando == "valor":
        numero_iteraciones = 10000
        with open("valor.txt", "w") as f_valor:
            with open("tiempo.txt", "w") as f_tiempo:
                for i in range(numero_iteraciones):
                    valor = obtener_valor()
                    f_valor.write(str(valor) + "\n")
                    tiempo = time.time_ns()
                    f_tiempo.write(str(tiempo) + "\n")

    # Cierre de los pines GPIO
    elif comando == "cerrar":
        for pin in GPIO_PINS:
            unexport_pin(pin)
        print("Pines GPIO cerrados correctamente.")

    else:
        print("Comando no válido.")

# Ejecución de la función principal
if __name__ == "__main__":
    main()

