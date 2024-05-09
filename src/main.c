#include "udf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <conio.h>

#define BUFFERSIZE 250

int main() {
    FILE* handle;              // handle do arquivo
    char filename[BUFFERSIZE]; // nome do arquivo

    int file_size;
    char* file;
    unsigned int x1, x2, y1, y2;
    int input = 0;

    x1 = 0;
    x2 = 80;
    y1 = 0;
    y2 = 25;

    printf("File to open__: ");
    fgets(filename, BUFFERSIZE, stdin);
    filename[strcspn(filename, "\r\n")] = 0;

    if ((handle = fopen(filename, "rb")) == NULL) { // conseguiu abrir ?
        printf("Não foi possivel abrir o arquivo %s", filename);
        return -1;
    }

    // Carregar o arquivo
    fseek(handle, 0L, SEEK_END);
    file_size = ftell(handle);
    file = malloc(file_size);
    rewind(handle);
    fread(file, 1, file_size, handle);
    rewind(handle); // TODO: Remover e fechar arquivo

    clear();
    // Desenha janela
    window(x1, y1, x2, y2, "EDITOR HEXADECIMAL");
    show_menu("Q - Sair\tWASD - Move", 1);

    set_data(file, file_size);
    show_data();
    // TODO: Logica de navegação e direção
    while (input != 'Q' && input != 'q') {
        input = get_input();
        switch (input) {
            case 'w':
            case 'W':
                move_pointer_top();
                break;
            case 'a':
            case 'A':
                move_pointer_left();
                break;
            case 's':
            case 'S':
                move_pointer_down();
                break;
            case 'd':
            case 'D':
                move_pointer_right();
                break;
        }
        show_data();
    }

    free(file);
    return 0;
}
