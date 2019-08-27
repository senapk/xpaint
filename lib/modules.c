
#include "modules.h" /*XDDDX*/
#include "xmath.h" /*XDDDX*/
#include "color.h" /*XDDDX*/
#include "draw.h" /*XDDDX*/
#include "text.h" /*XDDDX*/
#include "base.h" /*XDDDX*/
#include <stdio.h>
#include <string.h>


static int __X_GRID_SIZE = 50;
static int __X_GRID_SEP = 1;

void x_grid_init(int side, int sep){
    __X_GRID_SIZE = side;
    __X_GRID_SEP = sep;
}

void x_grid_square(int l, int c){
    int size = __X_GRID_SIZE, sep = __X_GRID_SEP;
    x_fill_rect(c * size + sep, l * size + sep, size - sep, size - sep);
}

void x_grid_circle(int l, int c){
    x_fill_circle(c * __X_GRID_SIZE + __X_GRID_SIZE / 2, l * __X_GRID_SIZE + __X_GRID_SIZE / 2,
                  __X_GRID_SIZE / 2 - __X_GRID_SEP + 1);
}


void x_grid_text(int l, int c, const char *text){
    float font_factor = 1.0;
    float fsize = 0, xdelta = 0, ydelta = 0;
    static char text2[1000];
    strcpy(text2, text);
    int value = strlen(text);
    if(value == 1){
        fsize = 0.9; xdelta = 0.3; ydelta = 0.1;
    }else if(value == 2){
        fsize = 0.7; xdelta = 0.2; ydelta = 0.2;
    }else if(value == 3){
        fsize = 0.5; xdelta = 0.18; ydelta = 0.3;
    }else if(value == 4){
        fsize = 0.4; xdelta = 0.13; ydelta = 0.35;
    }else if(value == 5){
        fsize = 0.35; xdelta = 0.1; ydelta = 0.35;
    }else {
        fsize = 0.35; xdelta = 0.1; ydelta = 0.35;
        text2[5] = '\0';
    }
    x_set_font_size(__X_GRID_SIZE * fsize * font_factor);
    x_write((c + xdelta) * __X_GRID_SIZE, (l + ydelta) * __X_GRID_SIZE, "%s", text2);

}

void x_grid_number(int l, int c, int value){
    char data[50];
    sprintf(data, "%d", value);
    x_grid_text(l, c, data);
}

/*########################*/
/*###### X_BAR MODULE ####*/
/*########################*/


static float __X_BAR_WIDTH = 20; /* bar width */
static float __X_BAR_YFACTOR = 1; /* multiplicative factor of bar height  */
static int __X_BAR_SIZE = 0;
static int __X_BAR_MAX = 0;

void x_bar_init(int size, int max){
    __X_BAR_SIZE = size;
    __X_BAR_MAX = max;
    __X_BAR_WIDTH = x_get_width() / (size + 2);
    __X_BAR_YFACTOR = (x_get_height() - 4.0 * __X_BAR_WIDTH);
    __X_BAR_YFACTOR = __X_BAR_YFACTOR < 0 ? -__X_BAR_YFACTOR : __X_BAR_YFACTOR;
    __X_BAR_YFACTOR /= max;
    if(__X_BAR_YFACTOR < 0.2)
        __X_BAR_YFACTOR = 0.2;
}

void x_bar_one(int i, int value){
    if((i < 0)||(i >= __X_BAR_SIZE))
        return;
    int x = __X_BAR_WIDTH * (i + 1);
    int ybase = x_get_height() - __X_BAR_WIDTH;
    int j;
    for(j = 0; j < ((int) __X_BAR_WIDTH - 2) ; j++)
        x_draw_line(x + j, ybase, x + j, ybase - __X_BAR_YFACTOR * value);
}

void x_bar_all(int * vet, int size, const char * colors, int * indices){
    x_set_color(X_COLOR_BLACK);
    x_clear();
    int i = 0;
    x_set_color(X_COLOR_WHITE);
    for(i = 0; i < size; i++)
        x_bar_one(i, vet[i]);
    if(colors != NULL && (strcmp(colors, "") != 0)){
        int qtd = strlen(colors);
        for(i = 0; i < qtd; i++){
            x_set_color(x_get_palette(colors[i]));
            x_bar_one(indices[i], vet[indices[i]]);
        }
    }
    static int atual = 0;
    x_set_color(X_COLOR_WHITE); /* desenhando estado */
    x_write(0, 0, "%d", atual++);
}

/*########################*/
/*###### X_PEN MODULE ####*/
/*########################*/

static double  __X_PEN_ANGLE = 0;
static double  __X_PEN_X = 200;
static double  __X_PEN_Y = 200;
static double  __X_PEN_THICK = 1;
static int     __X_PEN_DOWN = 1;

void   x_pen_set_angle(double degrees){
    __X_PEN_ANGLE = degrees;
}
void   x_pen_set_thick(int thick){
    if(thick > 0)
        __X_PEN_THICK = thick;
}
void   x_pen_set_pos(double x, double y){
    __X_PEN_X = x;
    __X_PEN_Y = y;
}
double x_pen_get_angle(){
    return __X_PEN_ANGLE;
}
int    x_pen_get_thick(){
    return __X_PEN_THICK;
}
double    x_pen_get_x(){
    return __X_PEN_X;
}
double    x_pen_get_y(){
    return __X_PEN_Y;
}
void   x_pen_up(void){
    __X_PEN_DOWN = 0;
}
void   x_pen_down(void){
    __X_PEN_DOWN = 1;
}
void   x_pen_walk(double distance){
    double x = __X_PEN_X + distance * xm_cos(__X_PEN_ANGLE);
    double y = __X_PEN_Y - distance * xm_sin(__X_PEN_ANGLE);
    if(__X_PEN_DOWN)
        x_fill_line(__X_PEN_X, __X_PEN_Y, x, y, __X_PEN_THICK);
    __X_PEN_X = x;
    __X_PEN_Y = y;
}
void   x_pen_rotate(int degrees){
    __X_PEN_ANGLE += degrees;
}
void   x_pen_goto(double x, double y){
    if(__X_PEN_DOWN)
        x_fill_line(__X_PEN_X, __X_PEN_Y, x, y, __X_PEN_THICK);
    __X_PEN_X = x;
    __X_PEN_Y = y;
}

