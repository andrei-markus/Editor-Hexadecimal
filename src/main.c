#include "udf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <conio.h>

int main() {
    char filename[BUFFERSIZE]; // nome do arquivo

    struct data_array file = {};
    int pointer = 0;
    int first_line = 0;
    int input = 0;

    // set_data(file, file_size);
    show_editor();
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
            case 'o':
            case 'O':
                open_file(&file, filename);
                break;
            case 'f':
            case 'F':
                save_file(&file, filename);
                break;
        }
        show_data(&file, pointer, &first_line);
    }

    free(file.data);
    clear();
    return 0;
}
