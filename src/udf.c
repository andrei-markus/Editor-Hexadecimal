#include "udf.h"
#include <corecrt_memory.h>
#include <stdlib.h>
#include <string.h>
#if defined(WIN32)
#include <Windows.h>
#endif
#include <stdio.h>
#include <conio.h>
#include <ctype.h>

#define DATA_TOP_OFFSET 2
#define DATA_LEFT_OFFSET 11

int max_pointer = 0;
int first_line = 0;

// struct data_array* root;

void clear() {
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("clear");
#endif

#if defined(_WIN32)
    system("cls");
#endif
}

void drawbox(int x1, int y1, int x2, int y2) {
    int i;
    gotoxy(x1, y1);
    printf("%c", 218);
    for (i = x1; i < x2 - 1; i++) {
        printf("%c", 196);
    }
    printf("%c", 191);

    for (i = y1 + 1; i <= y2; i++) {
        gotoxy(x1, i);
        printf("%c", 179);
        spaces(x2 - x1 - 2);
        printf("%c", 179);
    }
    gotoxy(0, y2);
    printf("%c", 192);
    for (i = x1; i < x2 - 1; i++) {
        printf("%c", 196);
    }
    printf("%c", 217);
}

void fillbox(int x1, int y1, int x2, int y2) {
    int i;
    for (i = y1 + 1; i < y2; i++) {
        gotoxy(x1 + 1, i);
        spaces(x2 - x1 - 2);
    }
}

void textcolor(int color) {
    HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
    bufferInfo.wAttributes &= 0x00F0;
    SetConsoleTextAttribute(hl, bufferInfo.wAttributes |= color);
}

void textbackground(int color) {
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, color * 16);
}

void color(int textColor, int backgroundColor) {
    textbackground(backgroundColor);
    textcolor(textColor);
}

void spaces(int s) {
    int i;
    for (i = 0; i <= s; i++) {
        printf(" ");
    }
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = (short)x;
    coord.Y = (short)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int stringlen(char text[]) {
    int c = 0;
    while (text[c] != 0) {
        c++;
    }
    return c;
}

void textcenter(int x1, int x2, int y1, char text[]) {
    int midtext = stringlen(text) / 2;
    int midwindow = x1 + (x2 - x1) / 2 - midtext;
    gotoxy(midwindow, y1);
    printf(text);
}

void window(int x1, int y1, int x2, int y2, char text[]) {
    int i;

    color(color_white, color_dark_blue);

    gotoxy(x1, y1);
    spaces(x2 - x1);
    textcenter(x1, x2, y1, text);

    color(color_white, color_black);
    drawbox(x1, y1 + 1, x2, y2);
    fillbox(x1, y1 + 1, x2, y2);
    color(color_white, color_black);
}

// void set_data(char* data, int size) {
//     root = calloc(1, sizeof(struct data_array));
//     root->data = data;
//     root->lenght = size;
//     max_pointer = size;
// }

// retorna a quantidade de caracteres escritos no out
void get_data_slice(const struct data_array* data, int offset, int size,
                    char* out) {
    int i = 0;

    memset(out, 0, size);

    // while (i < size && (i + offset) < data->lenght) {

    //     out[i] = data->data[offset + i];
    // }

    memset(out, 0, size);
    if (data->lenght - offset >= size) {
        memcpy(out, &(data->data[offset]), size);
    } else {
        memcpy(out, &(data->data[offset]), data->lenght - offset);
    }
}

void show_data(const struct data_array* file, int pointer, int* first_line) {

    int l;
    int c;
    int b;
    char data[ROWS * COLS];

    if ((pointer / COLS) >= (*first_line + ROWS)) {
        *first_line = pointer / COLS - ROWS + 1;
    }
    if (pointer / COLS < *first_line) {
        *first_line = pointer / COLS;
    }
    get_data_slice(file, *first_line * COLS, ROWS * COLS, data);

    // Desenha numero linha
    for (l = 0; l < ROWS; l++) {
        gotoxy(1, l + DATA_TOP_OFFSET);
        printf("%6d   ", (*first_line + l) * COLS);
    }

    for (l = 0; l < ROWS; l++) {
        gotoxy(DATA_LEFT_OFFSET, l + DATA_TOP_OFFSET);
        for (c = 0; c < COLS; c++) {
            printf("%02X ", data[l * COLS + c]);
        }
        printf("   ");
        for (c = 0; c < COLS; c++) {
            if (data[l * COLS + c] < 32 || data[l * COLS + c] > 126) {
                printf(".");
            } else {
                printf("%c", data[l * COLS + c]);
            }
        }
    }
    gotoxy(DATA_LEFT_OFFSET + (pointer % COLS) * 3,
           DATA_TOP_OFFSET + (pointer / COLS) - *first_line);
}

void show_menu(char* menu, int offset) {
    gotoxy(2, DATA_TOP_OFFSET + ROWS + offset);
    printf("%s", menu);
}

void show_editor() {
    clear();
    unsigned int x1, x2, y1, y2;
    x1 = 0;
    x2 = COLS * 4 + 16;
    y1 = 0;
    y2 = ROWS + 5;

    window(x1, y1, x2, y2, "EDITOR HEXADECIMAL");
    show_menu("Q - Sair\tWASD - Move\tX - Apagar", 1);
    show_menu("F - Salvar", 2);
}

void delay(int ms) {
#if defined(WIN32)
    Sleep(ms);
#endif
}

int achoice(int x, int y, int x1, int y1, int numopcoes, char opcoes[][20]) {
    int i;
    int opcao = 0;
    int tecla = 0;

    while (tecla != 13) {
        textcolor(3);
        textbackground(4);
        for (i = 0; i < numopcoes; i++) {
            gotoxy(x, y + i);
            spaces(x1 - x);
            gotoxy(x, y + i);
            printf("%s", opcoes[i]);
        }
        textcolor(4);
        textbackground(5);
        gotoxy(x, y + opcao);
        spaces(x1 - x);
        gotoxy(x, y + opcao);
        printf("%s", opcoes[opcao]);

        tecla = getch();
        if (tecla == 'A' || tecla == 'a') {
            if (opcao > 0) {
                opcao--;
            }
        }
        if (tecla == 'Z' || tecla == 'z') {
            if (opcao < numopcoes - 1) {
                opcao++;
            }
        }
    }

    return opcao;
}

int get_input() { return getch(); }

void move_pointer_top(const struct data_array* file, int* pointer) {
    if (*pointer >= COLS) {
        (*pointer) -= COLS;
    }
}

void move_pointer_left(const struct data_array* file, int* pointer) {
    if (*pointer > 0) {
        (*pointer)--;
    }
}

void move_pointer_right(const struct data_array* file, int* pointer) {
    if (*pointer < file->lenght) {
        (*pointer)++;
    }
}

void move_pointer_down(const struct data_array* file, int* pointer) {
    if ((*pointer + COLS) <= file->lenght) {
        (*pointer) += COLS;
    }
}

void delete_at(struct data_array* file, int* pointer) {
    int i;
    struct data_array* c;
    if (*pointer > file->lenght) {
        return;
    }
    for (i = *pointer; i < file->lenght; i++) {
        file->data[i] = file->data[i + 1];
    }
    file->lenght--;
    move_pointer_left(file, pointer);
}

void open_file(struct data_array* file, char* filename) {
    FILE* handle; // handle do arquivo

    clear();
    printf("Abrir arquivo:");
    fgets(filename, BUFFERSIZE, stdin);
    filename[strcspn(filename, "\r\n")] = 0;

    if ((handle = fopen(filename, "rb")) == NULL) { // conseguiu abrir ?
        printf("Não foi possivel abrir o arquivo %s", filename);
        delay(1000);
        return;
    }

    // Carregar o arquivo
    fseek(handle, 0L, SEEK_END);
    file->lenght = ftell(handle);
    file->capacity = file->lenght * 1.5;
    file->data = malloc(file->capacity);
    rewind(handle);
    fread(file->data, 1, file->lenght, handle);
    fclose(handle);
    show_editor();
}

void save_file(const struct data_array* file, const char* filename) {
    FILE* handle;
    if ((handle = fopen(filename, "wb")) == NULL) { // conseguiu abrir ?
        printf("Não foi possivel salvar o arquivo %s", filename);
    }
    fwrite(file->data, 1, file->lenght, handle);
    fclose(handle);
}
