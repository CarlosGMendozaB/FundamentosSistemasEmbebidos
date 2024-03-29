#!/bin/bash

# GPIO utilizados para generar numero
GPIO_0=27
GPIO_1=22
GPIO_2=17
GPIO_3=4
GPIO_4=18
GPIO_5=23
GPIO_6=24
GPIO_7=8



# En caso que no se pase algun valor
if [ $# -ne 1 ]; then   # si no hay argumento
  echo "No hay comando"
  echo "los comandos a utilizar es config, valor, cerrar"
  exit 2     # Numero invalido de argumentos
fi

# Configurar GPIO como entradas

if [ "$1" == "config" ]; then
        echo "Exportando GPIO numero $GPIO_0"
        echo $GPIO_0 >> "/sys/class/gpio/export"
        sleep 1  # para asegurar que se exporto correctamene
        echo "in" >> "/sys/class/gpio/gpio$GPIO_0/direction"
        echo "Exportando GPIO numero $GPIO_1"
        echo $GPIO_1 >> "/sys/class/gpio/export"
        sleep 1  # para asegurar que se exporto correctamene
        echo "in" >> "/sys/class/gpio/gpio$GPIO_1/direction"
        echo "Exportando GPIO numero $GPIO_2"
        echo $GPIO_2 >> "/sys/class/gpio/export"
        sleep 1  # para asegurar que se exporto correctamene
        echo "in" >> "/sys/class/gpio/gpio$GPIO_2/direction"
	echo "Exportando GPIO numero $GPIO_3"
        echo $GPIO_3 >> "/sys/class/gpio/export"
        sleep 1  # para asegurar que se exporto correctamene
        echo "in" >> "/sys/class/gpio/gpio$GPIO_3/direction"
	echo "Exportando GPIO numero $GPIO_4"
        echo $GPIO_4 >> "/sys/class/gpio/export"
        sleep 1  # para asegurar que se exporto correctamene
        echo "in" >> "/sys/class/gpio/gpio$GPIO_4/direction"
	echo "Exportando GPIO numero $GPIO_5"
        echo $GPIO_5 >> "/sys/class/gpio/export"
        sleep 1  # para asegurar que se exporto correctamene
        echo "in" >> "/sys/class/gpio/gpio$GPIO_5/direction"
	echo "Exportando GPIO numero $GPIO_6"
        echo $GPIO_6 >> "/sys/class/gpio/export"
        sleep 1  # para asegurar que se exporto correctamene
        echo "in" >> "/sys/class/gpio/gpio$GPIO_6/direction"
	echo "Exportando GPIO numero $GPIO_7"
        echo $GPIO_7 >> "/sys/class/gpio/export"
        sleep 1  # para asegurar que se exporto correctamene
        echo "in" >> "/sys/class/gpio/gpio$GPIO_7/direction"

fi
if [ "$1" == "cerrar" ]; then
        echo "cerrando el GPIO $GPIO_0"
        echo $GPIO_0 >> "/sys/class/gpio/unexport"
        echo "cerrando el GPIO $GPIO_1"
        echo $GPIO_1 >> "/sys/class/gpio/unexport"
	echo "cerrando el GPIO $GPIO_2"
        echo $GPIO_2 >> "/sys/class/gpio/unexport"
	echo "cerrando el GPIO $GPIO_3"
        echo $GPIO_3 >> "/sys/class/gpio/unexport"
	echo "cerrando el GPIO $GPIO_4"
        echo $GPIO_4 >> "/sys/class/gpio/unexport"
	echo "cerrando el GPIO $GPIO_5"
        echo $GPIO_5 >> "/sys/class/gpio/unexport"
	echo "cerrando el GPIO $GPIO_6"
        echo $GPIO_6 >> "/sys/class/gpio/unexport"
	echo "cerrando el GPIO $GPIO_7"
        echo $GPIO_7 >> "/sys/class/gpio/unexport"
fi


if [ "$1" == "valor" ]; then

        n=100 #Numeros de experimentos
        i=0
	#echo >tiempoShell.txt
	#echo >valorSShell.txt
	rm ./tiempoShell.txt
	rm ./valorShell.txt
	rm ./iteracion.txt
        while((i<n))
        do 
        	bit0=$(cat "/sys/class/gpio/gpio$GPIO_0/value")
        	bit1=$(cat "/sys/class/gpio/gpio$GPIO_1/value")
        	bit2=$(cat "/sys/class/gpio/gpio$GPIO_2/value")
        	bit3=$(cat "/sys/class/gpio/gpio$GPIO_3/value")
        	bit4=$(cat "/sys/class/gpio/gpio$GPIO_4/value")
       		bit5=$(cat "/sys/class/gpio/gpio$GPIO_5/value")
        	bit6=$(cat "/sys/class/gpio/gpio$GPIO_6/value")
        	bit7=$(cat "/sys/class/gpio/gpio$GPIO_7/value")
        	#bit1=3.3
        	let numero=bit0+bit1+bit2+bit3+bit4+bit5+bit6+bit7
                let i=i+1
                t=$(date +%s%N)
		#Visualizacion de cada valor individual	
                echo $bit0
                echo $bit1
                echo $bit2
                echo $bit3
                echo $bit4
                echo $bit5
                echo $bit6
                echo $bit7
        	echo $i
                echo $t>>tiempoShell.txt
        	echo $numero>>valorShell.txt 
		echo $i>>iteracion.txt
       done
fi
