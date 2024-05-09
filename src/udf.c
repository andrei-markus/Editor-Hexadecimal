#include "udf.h"
#include <corecrt_memory.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>

#define COLS 16
#define ROWS 20
#define DATA_TOP_OFFSET 2
#define DATA_LEFT_OFFSET 11

int pointer = 0;
int max_pointer = 0;
int first_line = 0;
struct chunk* root;

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

void set_data(char* data, int size) {
    root = calloc(1, sizeof(struct chunk));
    root->data = data;
    root->size = size;
    root->lenght = size;
    max_pointer = size;
}

// retorna a quantidade de caracteres escritos no out
int get_data_slice(struct chunk* data, int offset, int size, char* out) {
    memset(out, 0, size);
    if (data->size - offset >= size) {
        memcpy(out, &(data->data[offset]), size);
    } else {
        memcpy(out, &(data->data[offset]), data->size - offset);
    }
}

void show_data() {

    int l;
    int c;
    char data[ROWS * COLS];

    get_data_slice(root, first_line * COLS, ROWS * COLS, data);

    // Desenha numero linha
    for (l = 0; l < ROWS; l++) {
        gotoxy(1, l + DATA_TOP_OFFSET);
        printf("%6d   ", (first_line + l) * COLS);
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
        /*printf("\n%5d  ", (l + 1) * COLS);*/
    }
    gotoxy(DATA_LEFT_OFFSET + (pointer % COLS) * 3,
           DATA_TOP_OFFSET + (pointer / COLS) - first_line);
}

void show_menu(char* menu, int offset) {
    gotoxy(2, DATA_TOP_OFFSET + ROWS + offset);
    printf("%s", menu);
}

void delay(int t) {
    int i;
    for (i = 0; i < 10 * t; i++)
        ;
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

void reset_pointer();

void move_pointer_top() {
    if (pointer >= COLS) {
        pointer -= COLS;
    }
    move_view();
}

void move_pointer_left() {
    if (pointer > 0) {
        pointer--;
    }
    move_view();
}

void move_pointer_right() {
    if (pointer < max_pointer) {
        pointer++;
    }
    move_view();
}

void move_pointer_down() {
    if ((pointer + COLS) <= max_pointer) {
        pointer += COLS;
    }
    move_view();
}

void move_view() {
    if ((pointer / COLS) >= (first_line + ROWS)) {
        first_line = pointer / COLS - ROWS + 1;
    }
    if (pointer / COLS < first_line) {
        first_line = pointer / COLS;
    }
}
