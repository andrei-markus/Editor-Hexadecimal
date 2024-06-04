#ifndef UDF_HEADER
#define UDF_HEADER

#define COLS 16
#define ROWS 23
#define BUFFERSIZE 250

enum colors {
#if defined(_WIN32)

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
#else
    color_black = 30,
    color_dark_red = 31,
    color_dark_green = 32,
    color_orange = 33,
    color_dark_blue = 34,
    color_magenta = 35,
    color_cyan = 36,
    color_light_gray = 37,

    color_gray = 90,
    color_red = 91,
    color_green = 92,
    color_yellow = 93,
    color_blue = 94,
    color_pink = 95,
    color_light_blue = 96,
    color_white = 97

#endif
};

struct data_array {
    unsigned char* data;
    int lenght;
    int capacity;
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
void delay(int ms);

int get_input();
void show_data(const struct data_array* data, int pointer, int* first_line);
void show_menu(char* menu, int offset);
void show_editor();
void move_pointer_top(const struct data_array* file, int* pointer);
void move_pointer_left(const struct data_array* file, int* pointer);
void move_pointer_right(const struct data_array* file, int* pointer);
void move_pointer_down(const struct data_array* file, int* pointer);

void grow_file(struct data_array* file);
void delete_at(struct data_array* file, int* pointer);
void insert_at(struct data_array* file, int* pointer, unsigned char c);
void edit_hex_at(struct data_array* file, int* pointer);
void open_file(struct data_array* file, char* filename);
void save_file(const struct data_array* file, const char* filename);
void save_file_as(const struct data_array* file, char* filename);
int search_data(const struct data_array* file, const char* search_str,
                int start_pos);

#endif
