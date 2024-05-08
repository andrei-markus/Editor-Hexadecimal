#include "udf.h"
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#define clrscr() system("cls")
#define MAX_SIZE 20

void drawbox(int x1, int y1, int x2, int y2)
{
    int i;
    for(i = x1; i <= x2; i++)
    {
        gotoxy(i, y1);
        printf("%c", 196);
        gotoxy(i, y2);
        printf("%c", 196);
    }
    for(i = y1; i <= y2; i++)
    {
        gotoxy(x1, i);
        printf("%c", 179);
        gotoxy(x2, i);
        printf("%c", 179);
    }
    gotoxy(x1, y1);
    printf("%c", 218);
    gotoxy(x2, y1);
    printf("%c", 191);

    gotoxy(x1, y2);
    printf("%c", 192);
    gotoxy(x2, y2);
    printf("%c", 217);
}

void fillbox(int x1, int y1, int x2, int y2)
{
    int i;
    for(i=y1+1; i<y2; i++)
    {
        gotoxy(x1+1,i);
        spaces(x2-x1-2);
    }
}

void textcolor (int color)
{
    HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
    bufferInfo.wAttributes &= 0x00F0;
    SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= color);
}

void textbackground(int color)
{
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, color * 16);
}

void color(int tC, int bC)
{
    textbackground(bC);
    textcolor(tC);
}

void spaces(int s)
{
    int i;
    for(i=0; i<=s; i++)
    {
        printf(" ");
    }
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = (short)x;
    coord.Y = (short)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int stringlen(char text[]) {
   int c = 0;
   while(text[c] != 0) {
        c++;
   }
   return c;
}

void textcenter(int x1, int x2, int y1, char text[]){
    int midtext = stringlen(text) / 2;
    int midwindow = x1 + (x2 - x1) / 2 - midtext;
    gotoxy(midwindow, y1); printf(text);
}

void window(int x1, int y1, int x2, int y2, char text[])
{
    int i;

    color(15,4);

    gotoxy(x1, y1);
    spaces(x2-x1);
    textcenter(x1, x2, y1, text);

    color(15,1);
    drawbox(x1, y1+1, x2, y2);
    fillbox(x1, y1+1, x2, y2);
}

void delay(int t) {
    int i;
    for(i=0;i<10 * t; i++);
}

// Função para apresentar um menu interativo e realizar operações com os dados
void achoice(int x, int y, const char *filename) {
    int cursor_x = x;
    int cursor_y = y;
    char tecla;

    // Exibir os dados iniciais na tela
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 16; j++) {
            gotoxy(x + j * 3, y + i);
            printf("%02X ", getch()); // Ler e exibir os valores diretamente da tela
        }
    }

    while (1) {
        // Posicionar o cursor na tela
        gotoxy(cursor_x * 3, cursor_y);

        // Capturar a entrada do teclado
        tecla = getch();

        // Realizar ações com base na tecla pressionada
        switch (tecla) {
            case 'w':
            case 'W':
                if (cursor_y > y)
                    cursor_y--;
                break;
            case 'z':
            case 'Z':
                if (cursor_y < y + 20 - 1)
                    cursor_y++;
                break;
            case 'a':
            case 'A':
                if (cursor_x > x)
                    cursor_x--;
                break;
            case 'd':
            case 'D':
                if (cursor_x < x + 16 - 1)
                    cursor_x++;
                break;
            case 's':
            case 'S':{
                // Salvar as alterações no arquivo
                FILE *handle;
                handle = fopen(filename, "w");
                if (handle != NULL) {
                    clrscr(); // Limpar a tela antes de exibir a mensagem de salvamento
                    printf("Salvando dados...");
                    fclose(handle);
                    printf("Dados salvos com sucesso no arquivo %s!\n", filename);
                    getch(); // Esperar uma tecla antes de continuar
                    clrscr(); // Limpar a tela novamente
                    return; // Sair da função
                } else {
                    printf("Erro ao abrir o arquivo %s para escrita!\n", filename);
                }
                break;
            case 'q':
            case 'Q':
                // Sair da função ao pressionar 'Q'
                return;
            default:
                break;
        }
    }
}
}
