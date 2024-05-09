#ifndef UDF_HEADER
#define UDF_HEADER

enum colors {
    color_black = 0,
    color_dark_blue = 1,
    color_dark_green = 2,
    color_light_blue = 3,
    color_dark_red = 4,
    color_magenta = 5,
    color_orange = 6,
    color_light_gray = 7,
    color_gray = 8,
    color_blue = 9,
    color_green = 10,
    color_cyan = 11,
    color_red = 12,
    color_pink = 13,
    color_yellow = 14,
    color_white = 15
};

struct chunk {
    char* data;
    int lenght;
    int size;
    struct chunck* right;
    struct chunck* left;
};

void clear();
void drawbox(int x1, int y1, int x2, int y2);
void textcolor(int color);
void fillbox(int x1, int y1, int x2, int y2);
void textbackground(int color);
void color(int tC, int bC);
void spaces(int s);
void gotoxy(int x, int y);
int stringlen(char text[]);
void textcenter(int x1, int x2, int y1, char text[]);
void window(int x1, int y1, int x2, int y2, char text[]);
void delay(int t);
int achoice(int x, int y, int x1, int y1, int numopcoes, char opcoes[][20]);

int get_input();
void set_data(char* data, int size);
void show_data();
void show_menu(char* menu, int offset);
void reset_pointer();
void move_pointer_top();
void move_pointer_left();
void move_pointer_right();
void move_pointer_down();
void move_view();
#endif
