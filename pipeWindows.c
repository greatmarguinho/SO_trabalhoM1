#include <stdio.h>
#include <windows.h>
#include <time.h>

double time1, timedif;


int main() {
    HANDLE hPipe1;
    HANDLE hPipe2;
    char buffer1[80] = "0";
    char buffer2[80] = "0";
    DWORD dwRead;

    int esteira1;
    int esteira2;
    int contador = 0;
    int peso_total = 0;
    int comecar = 0;
    int peso = 0;


    // Nome dos pipes
    LPCTSTR pipeName1 = TEXT("\\\\.\\pipe\\myPipe1");
    LPCTSTR pipeName2 = TEXT("\\\\.\\pipe\\myPipe2");

        // Criar os pipes
        hPipe1 = CreateNamedPipe(pipeName1, PIPE_ACCESS_INBOUND, PIPE_TYPE_BYTE | PIPE_WAIT, 1, 0, 0, 0, NULL);
        hPipe2 = CreateNamedPipe(pipeName2, PIPE_ACCESS_INBOUND, PIPE_TYPE_BYTE | PIPE_WAIT, 1, 0, 0, 0, NULL);

        // Conectar aos pipes
        ConnectNamedPipe(hPipe1, NULL);
        ConnectNamedPipe(hPipe2, NULL);

        // Obter o tempo de início

        while (1) {
            // Ler dados dos pipes
            ReadFile(hPipe1, buffer1, sizeof(buffer1), &dwRead, NULL);
            contador++;
            ReadFile(hPipe2, buffer2, sizeof(buffer2), &dwRead, NULL);
            contador++;
        if (comecar == 0) {
            // Obter o tempo de início do processamento
            time1 = (double) clock();            /* get initial time */
            time1 = time1 / CLOCKS_PER_SEC; 
            comecar = 1;
        }
            // Imprimir os dados lidos
            printf("Data1: %s\n", buffer1);
            printf("Data2: %s\n", buffer2);

            esteira1 = atoi(buffer1);
            esteira2 = atoi(buffer2);
            peso_total = esteira1 + esteira2 + peso_total;
            printf("Total a cada 500: %d\n", peso);

            // Se atingir o limite de contador, calcular o peso e tempo decorrido
            if (contador == 500) {
                printf("Total a cada 500: %d\n", peso_total);
                timedif = ( ((double) clock()) / CLOCKS_PER_SEC) - time1;
                printf("The elapsed time is %f seconds\n", timedif);
                peso = peso_total;
                break;
            }

            // Esperar por um tempo antes de continuar
            Sleep(2000);
        }

        // Fechar os pipes
        CloseHandle(hPipe1);
        CloseHandle(hPipe2);

        // Reiniciar contador e peso_total para próxima iteração
        contador = 0;
        peso_total = 0;

    return 0;
}
