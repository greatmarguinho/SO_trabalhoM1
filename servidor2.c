#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
 
double time1, timedif;

int main() {
    int fd;
    int fd2;
    int esteira1;
    int esteira2;
    int contador = 0;
    int peso = 0;
    int peso_total = 0;
    int comecar = 0;
    char *myfifo = "/tmp/myfifo1";
    char *myfifo2 = "/tmp/myfifo2";

    // Criar o arquivo FIFO (pipe) se ele não existir
    mkfifo(myfifo, 0666);
    mkfifo(myfifo2, 0666);

    char str[80];
    char str2[80];
    while (1) {        
        // Abrir o arquivo FIFO em modo de leitura
        fd = open(myfifo, O_RDONLY);
        fd2 = open(myfifo2, O_RDONLY);
        if(comecar == 0){
            time1 = (double) clock();
            time1 = time1 / CLOCKS_PER_SEC;
            comecar = 1;
        }
        // Ler os dados do arquivo FIFO
        read(fd, str, 80);
        contador++;
        read(fd2, str2, 80);
        contador++;
        // Imprimir os dados lidos e fechar o arquivo
        printf("Data1: %s\n", str);
        printf("Data2: %s\n", str2);
        close(fd);
        close(fd2);

        esteira1 = atoi(str);
        esteira2 = atoi(str2);
        peso_total = esteira1 + esteira2 + peso_total;

        if(contador >= 500){
            peso = peso_total;
            printf("Total a cada 500: %d\n", peso);
            timedif = ( ((double) clock()) / CLOCKS_PER_SEC) - time1;
            printf("The elapsed time is %f seconds\n", timedif);
            break; // somente para parar e vermos o tempo
            contador = 0;
        }
        printf("Total a cada 500: %d\n", peso);
        usleep(2000000);
    }

    return 0;
}
