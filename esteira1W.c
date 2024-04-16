#include <windows.h>
#include <stdio.h>
#include <string.h>

int main()
{
    HANDLE hPipe;
    char buffer[80] = "2";
    DWORD dwWritten;

    // Nome do pipe
    LPCTSTR pipeName = TEXT("\\\\.\\pipe\\myPipe1");

    // Loop principal do cliente
    while (1)
    {
        // Conectar ao pipe
        hPipe = CreateFile(
            pipeName,              // Nome do pipe
            GENERIC_WRITE,         // Apenas escrita
            0,                     // Nenhum compartilhamento
            NULL,                  // Segurança padrão
            OPEN_EXISTING,         // Abrir pipe existente
            0,                     // Atributos padrão
            NULL                   // Sem sobreposição
        );

        if (hPipe != INVALID_HANDLE_VALUE)
        {
            // Escrever no pipe
            if (!WriteFile(
                    hPipe,          // Handle do pipe
                    buffer,         // Dados a serem escritos
                    strlen(buffer), // Tamanho dos dados
                    &dwWritten,     // Número de bytes escritos
                    NULL            // Sem sobreposição
                ))
            {
                printf("Erro ao escrever no pipe. Código de erro: %d\n", GetLastError());
                CloseHandle(hPipe);
                return 1;
            }

            // Fechar a conexão com o pipe
            CloseHandle(hPipe);
        }
        else
        {
            printf("Erro ao conectar ao pipe. Código de erro: %d\n", GetLastError());
            return 1;
        }

        // Esperar antes de escrever novamente
        Sleep(1000);
    }

    return 0;
}
