#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define GPIO_0 27
#define GPIO_1 22
#define GPIO_2 17
#define GPIO_3 4
#define GPIO_4 18
#define GPIO_5 23
#define GPIO_6 24
#define GPIO_7 8

void export_gpio(int gpio_num) {
    FILE *export_file;
    export_file = fopen("/sys/class/gpio/export", "w");
    if (export_file == NULL) {
        perror("Error al abrir el archivo de exportación");
        exit(EXIT_FAILURE);
    }
    fprintf(export_file, "%d\n", gpio_num);
    fclose(export_file);

    char direction_path[100];
    sprintf(direction_path, "/sys/class/gpio/gpio%d/direction", gpio_num);
    FILE *direction_file = fopen(direction_path, "w");
    if (direction_file == NULL) {
        perror("Error al abrir el archivo de dirección");
        exit(EXIT_FAILURE);
    }
    fprintf(direction_file, "in\n");
    fclose(direction_file);
}

void unexport_gpio(int gpio_num) {
    FILE *unexport_file;
    unexport_file = fopen("/sys/class/gpio/unexport", "w");
    if (unexport_file == NULL) {
        perror("Error al abrir el archivo de unexport");
        exit(EXIT_FAILURE);
    }
    fprintf(unexport_file, "%d\n", gpio_num);
    fclose(unexport_file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("No hay comando\n");
        printf("Los comandos a utilizar son: config, valor, cerrar\n");
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "config") == 0) {
        export_gpio(GPIO_0);
        export_gpio(GPIO_1);
        export_gpio(GPIO_2);
        export_gpio(GPIO_3);
        export_gpio(GPIO_4);
        export_gpio(GPIO_5);
        export_gpio(GPIO_6);
        export_gpio(GPIO_7);
    } else if (strcmp(argv[1], "cerrar") == 0) {
        unexport_gpio(GPIO_0);
        unexport_gpio(GPIO_1);
        unexport_gpio(GPIO_2);
        unexport_gpio(GPIO_3);
        unexport_gpio(GPIO_4);
        unexport_gpio(GPIO_5);
        unexport_gpio(GPIO_6);
        unexport_gpio(GPIO_7);
    } else if (strcmp(argv[1], "valor") == 0) {
        int n = 100;
        int i;
	int GPIO[8]={27,22,17,4,18,23,24,8};
        FILE *tiempo_file = fopen("tiempoC.txt", "w");
        fclose(tiempo_file);
        FILE *valor_file = fopen("valorC.txt", "w");
        fclose(valor_file);

        for (i = 0; i < n; i++) {
            FILE *gpio_files[8];
            int bit_values[8];
            char gpio_value_path[100];
            int j;

            for (j = 0; j < 8; j++) {
                sprintf(gpio_value_path, "/sys/class/gpio/gpio%d/value", GPIO[j]);
		//printf("%s\n",gpio_value_path);
                gpio_files[j] = fopen(gpio_value_path, "r");
                if (gpio_files[j] == NULL) {
                    perror("Error al abrir el archivo GPIO value");
                    exit(EXIT_FAILURE);
                }
                fscanf(gpio_files[j], "%d", &bit_values[j]);
                fclose(gpio_files[j]);
            }

            // Supongamos que bit1 siempre tiene el valor 3.3
            //bit_values[1] = 3.3;

            int numero = 0;
            for (j = 0; j < 8; j++) {
                numero += bit_values[j];
            }

            // Visualización de cada valor individual
            for (j = 0; j < 8; j++) {
                printf("%d\n", bit_values[j]);
            }
            printf("%d\n", i);

	    struct timeval tv;
	    gettimeofday(&tv,NULL);

            // Guardar tiempo actual en tiempo.txt
            long long int t = tv.tv_sec*(long long int) 1000000+tv.tv_usec;
            FILE *tiempo_file = fopen("tiempoC.txt", "a");
            if (tiempo_file == NULL) {
                perror("Error al abrir el archivo tiempo.txt");
                exit(EXIT_FAILURE);
            }
            fprintf(tiempo_file, "%lld\n", t);
            fclose(tiempo_file);

            // Guardar el número en valor.txt
            FILE *valor_file = fopen("valorC.txt", "a");
            if (valor_file == NULL) {
                perror("Error al abrir el archivo valor.txt");
                exit(EXIT_FAILURE);
            }
            fprintf(valor_file, "%d\n", numero);
            fclose(valor_file);
        }
    } else {
        printf("Comando no reconocido\n");
        printf("Los comandos a utilizar son: config, valor, cerrar\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}

