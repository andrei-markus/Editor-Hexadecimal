#include "udf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <conio.h>

#define BUFFERSIZE 250

int main() {
    FILE* handle;              // handle do arquivo
    char filename[BUFFERSIZE]; // nome do arquivo

    struct data_array file;
    int pointer = 0;
    int first_line = 0;

    unsigned int x1, x2, y1, y2;
    int input = 0;

    x1 = 0;
    x2 = COLS * 4 + 16;
    y1 = 0;
    y2 = ROWS + 5;

    printf("File to open__: ");
    fgets(filename, BUFFERSIZE, stdin);
    filename[strcspn(filename, "\r\n")] = 0;

    if ((handle = fopen(filename, "rb")) == NULL) { // conseguiu abrir ?
        printf("Não foi possivel abrir o arquivo %s", filename);
        return -1;
    }

    // Carregar o arquivo
    fseek(handle, 0L, SEEK_END);
    file.lenght = ftell(handle);
    file.capacity = file.lenght * 1.5;
    file.data = malloc(file.capacity);
    rewind(handle);
    fread(file.data, 1, file.lenght, handle);
    rewind(handle); // TODO: Remover e fechar arquivo

    clear();
    // Desenha janela
    window(x1, y1, x2, y2, "EDITOR HEXADECIMAL");
    show_menu("Q - Sair\tWASD - Move\tX - Apagar", 1);

    // set_data(file, file_size);
    show_data(&file, pointer, &first_line);
    // TODO: Logica de navegação e direção
    while (input != 'Q' && input != 'q') {
        input = get_input();
        switch (input) {
            case 'w':
            case 'W':
                move_pointer_top(&file, &pointer);
                break;
            case 'a':
            case 'A':
                move_pointer_left(&file, &pointer);
                break;
            case 's':
            case 'S':
                move_pointer_down(&file, &pointer);
                break;
            case 'd':
            case 'D':
                move_pointer_right(&file, &pointer);
                break;
            case 'x':
            case 'X':
                delete_at(&file, &pointer);
                break;
        }
        show_data(&file, pointer, &first_line);
    }

    free(file.data);
    clear();
    return 0;
}
