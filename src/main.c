#include "udf.h"
#include <stdio.h>
#include <conio.h>
#define COLS 16
#define ROWS 20


int main() {
    FILE *handle;                     // handle do arquivo
    char filename[50];                // nome do arquivo
    unsigned char aux;                // variavel auxiliar para leitura dos dados
    unsigned char matriz[ROWS][COLS];
    unsigned char l = 0;              // 1 byte de 0 a 255
    unsigned char c = 0;              // 1 byte de 0 a 255
    int i;
    unsigned int x1, x2, y1, y2;
    int continuar = 1; // Variável para controlar se o programa deve continuar executando

    x1 = 0;
    x2 = 80;
    y1 = 5;
    y2 = 34;

    printf("\n\n\n\nFile to open__: ");
    scanf("%s", filename); // poderia usar o gets(filename);

    if ((handle = fopen(filename, "r")) == NULL) { // conseguiu abrir ?
        printf("Não foi possivel abrir o arquivo %s", filename);
        continuar = 0;
    } else {
        window(x1, y1, x2, y2, "EDITOR HEXADECIMAL");
        drawbox(x1, y1, x2, y2);
        textcenter(x1, x2, 6, "EDITOR HEXADECIMAL");

        for (l = 0; l < ROWS; l++) {
            for (c = 0; c < COLS; c++) {
                matriz[l][c] = 0; // zerar toda a matriz
            }
        }

        l = 0;
        c = 0;

        do {
            size_t bytes_read = fread(&aux, 1, 1, handle); // um byte por vez
            if (bytes_read == 0) {
                break; // não leu nenhum byte, fim do arquivo alcançado
            }
            matriz[l][c] = aux;
            c++;
            if (c >= COLS) { // observar que neste programa somente
                c = 0;         // suporta arquivos até 80 X 24 bytes ...
                l++;
                if (l >= ROWS) {
                    printf("\nExcesso de informacoes, programa nao suporta muitos dados");
                    break;
                }
            }
        } while (1); // Loop infinito, termina quando chega ao fim do arquivo

        fseek(handle, 0, SEEK_SET); // volta ao início do arquivo para escrever a matriz modificada
        for (l = 0; l < ROWS; l++) {
            for (c = 0; c < COLS; c++) {
                fwrite(&matriz[l][c], 1, 1, handle); // escreve um byte por vez
            }
        }
        fclose(handle);

        for (aux = 0; aux < 1; aux++) {
            printf("\n\n"); // limpar a tela com linhas em branco
        }

        printf("\n00000  ");
        for (l = 0; l < ROWS; l++) {
            for (c = 0; c < COLS; c++) {
                if (matriz[l][c] < 16)
                    printf("0");
                printf("%x ", matriz[l][c]);
            }
            printf("   ");
            for (c = 0; c < COLS; c++) {
                if (matriz[l][c] < 32 || matriz[l][c] > 126) {
                    printf(".");
                } else {
                    printf("%c", matriz[l][c]);
                }
            }

            printf("\n%5d  ", (l + 1) * COLS);
        }
    }

    return 0;
}

