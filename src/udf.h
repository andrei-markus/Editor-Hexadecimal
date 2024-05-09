#ifndef UDF_HEADER
#define UDF_HEADER

void drawbox(int x1, int y1, int x2, int y2);
void textcolor (int color);
void fillbox(int x1, int y1, int x2, int y2);
void textbackground(int color);
void color(int tC, int bC);
void spaces(int s);
void gotoxy(int x, int y);
int stringlen(char text[]);
void textcenter(int x1, int x2, int y1, char text[]);
void window(int x1, int y1, int x2, int y2, char text[]);
void delay(int t);
int achoice(int x, int y, int x1, int y1, int numopcoes, char opcoes[][MAX_SIZE])

#endif
