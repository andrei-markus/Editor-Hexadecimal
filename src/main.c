#include "udf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <conio.h>

int main() {
    char filename[BUFFERSIZE] = "file.txt"; // nome do arquivo

    struct data_array file = {};
    int pointer = 0;
    int first_line = 0;
    int input = 0;
    char search_str[BUFFERSIZE];
    int search_result;

    show_editor();
    show_data(&file, pointer, &first_line);
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
            case 'g':
            case 'G':
                save_file_as(&file, filename);
                break;
            case 'e':
            case 'E':
                input = get_input();
                while (input != 27 && pointer < file.lenght) {
                    file.data[pointer] = input;
                    show_data(&file, pointer, &first_line);
                    move_pointer_right(&file, &pointer);
                    input = get_input();
                }
                break;
            case 'i':
            case 'I':
                input = get_input();
                while (input != 27) {
                    insert_at(&file, &pointer, input);
                    show_data(&file, pointer, &first_line);
                    input = get_input();
                }
                break;
            case 'b':
            case 'B':
                clear();
                printf("Digite o texto para pesquisa: ");
                fgets(search_str, BUFFERSIZE, stdin);
                search_str[strcspn(search_str, "\r\n")] = 0; // Remove newline character
                search_result = search_data(&file, search_str);
                if (search_result >= 0) {
                    pointer = search_result;
                    printf("Encontrado na posicao: %d\n", search_result);
                } else {
                    printf("Nao encontrado\n");
                }
                delay(2000);
                show_editor();
                break;
        }
        show_data(&file, pointer, &first_line);
    }

    free(file.data);
    clear();
    return 0;
}
