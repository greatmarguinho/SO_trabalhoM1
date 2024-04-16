#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
 

int main() {
    struct timeval start, end;
    double elapsed_time;
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
        // Abrir o arquivo FIFO em modo de leitura
        fd = open(myfifo, O_RDONLY);
        fd2 = open(myfifo2, O_RDONLY);
    while (1) {        
        // Ler os dados do arquivo FIFO
        read(fd, str, 80);
        contador++;
        read(fd2, str2, 80);
        contador++;
        if(comecar == 0){
            gettimeofday(&start, NULL); // começa o tempo
            comecar = 1;
        }
        // Imprimir os dados lidos e fechar o arquivo
        printf("Data1: %s\n", str);
        printf("Data2: %s\n", str2);

        esteira1 = atoi(str);
        esteira2 = atoi(str2);
        peso_total = esteira1 + esteira2 + peso_total;

        if(contador >= 500){
            peso = peso_total;
            printf("Total a cada 500: %d\n", peso);
            gettimeofday(&end, NULL);
            elapsed_time = (end.tv_sec - start.tv_sec) +
                   (end.tv_usec - start.tv_usec) / 1e6;
            printf("Tempo decorrido: %.6f segundos\n", elapsed_time);
            break; // somente para parar e vermos o tempo
            contador = 0;
        }
        printf("Total a cada 500: %d\n", peso);
        usleep(2000000);
    }
        close(fd);
        close(fd2);

    return 0;
}
