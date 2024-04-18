/** ==========================================
 Author______: Alexandre Stürmer Wolf
 Date________: 03/20/2024
 Utility_____: Many things
 Compiler cmd: gcc udf.c -o udf
 ========================================= **/

#include <windows.h>
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

void fillbox(x1, y1, x2, y2)
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

int achoice(int x, int y, int x1, int y1, int numopcoes, char opcoes[][MAX_SIZE]) {
   int i;
   int opcao = 0;
   int tecla = 0;

   while(tecla != 13) {
      textcolor(3); textbackground(4);
      for(i = 0; i< numopcoes; i++) {
         gotoxy(x, y + i); spaces(x1 - x);
         gotoxy(x, y + i); printf("%s", opcoes[i]);
      }
      textcolor(4); textbackground(5);
      gotoxy(x, y + opcao); spaces(x1 - x);
      gotoxy(x, y + opcao); printf("%s", opcoes[opcao]);

      tecla = getch();
      if(tecla == 'A' || tecla == 'a') {
        if(opcao > 0) {
           opcao --;
        }
      }
      if(tecla == 'Z' || tecla == 'z') {
        if(opcao < numopcoes - 1) {
           opcao ++;
        }
      }
   }

   return opcao;
}

