
#include "modules.h" /*XDDDX*/
#include "xmath.h" /*XDDDX*/
#include "color.h" /*XDDDX*/
#include "draw.h" /*XDDDX*/
#include "text.h" /*XDDDX*/
#include "base.h" /*XDDDX*/
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

static int __X_GRID_SIZE = 50;
static int __X_GRID_SEP = 1;

void grid_init(int side, int sep){
    __X_GRID_SIZE = side;
    __X_GRID_SEP = sep;
}

void grid_square(int l, int c){
    int size = __X_GRID_SIZE, sep = __X_GRID_SEP;
    rect(c * size + sep, l * size + sep, size - sep, size - sep);
}

void grid_circle(int l, int c){
    circle(c * __X_GRID_SIZE + __X_GRID_SIZE / 2, l * __X_GRID_SIZE + __X_GRID_SIZE / 2,
                  __X_GRID_SIZE / 2 - __X_GRID_SEP + 1);
}


void grid_write(int l, int c, const char *format, ...){
    char text[1000];
    va_list args;
    va_start( args, format );
    vsprintf(text, format, args);
    va_end( args );
    float xdelta = 0.13, ydelta = 0.35;
    write((c + xdelta) * __X_GRID_SIZE, (l + ydelta) * __X_GRID_SIZE, "%s", text);

}

/*########################*/
/*###### X_BAR MODULE ####*/
/*########################*/


static float __X_BAR_WIDTH = 20; /* bar width */
static float __X_BAR_YFACTOR = 1; /* multiplicative factor of bar height  */
static int __X_BAR_SIZE = 0;
static int __X_BAR_MAX = 0;

void bar_init(int size, int max){
    __X_BAR_SIZE = size;
    __X_BAR_MAX = max;
    __X_BAR_WIDTH = get_width() / (size + 2);
    __X_BAR_YFACTOR = (get_height() - 4.0 * __X_BAR_WIDTH);
    __X_BAR_YFACTOR = __X_BAR_YFACTOR < 0 ? -__X_BAR_YFACTOR : __X_BAR_YFACTOR;
    __X_BAR_YFACTOR /= max;
    if(__X_BAR_YFACTOR < 0.2)
        __X_BAR_YFACTOR = 0.2;
}

void bar_one(int i, int value){
    if((i < 0)||(i >= __X_BAR_SIZE))
        return;
    int x = __X_BAR_WIDTH * (i + 1);
    int ybase = get_height() - __X_BAR_WIDTH;
    int j;
    for(j = 0; j < ((int) __X_BAR_WIDTH - 2) ; j++)
        line(x + j, ybase, x + j, ybase - __X_BAR_YFACTOR * value);
}

void bar_all(int * vet, int size, const char * colors, int * indices){
    background(BLACK);
    int i = 0;
    stroke(WHITE);
    for(i = 0; i < size; i++)
        bar_one(i, vet[i]);
    if(colors != NULL && (strcmp(colors, "") != 0)){
        int qtd = strlen(colors);
        for(i = 0; i < qtd; i++){
            stroke_char(colors[i]);
            bar_one(indices[i], vet[indices[i]]);
        }
    }
    static int atual = 0;
    stroke(WHITE); /* desenhando estado */
    write(0, 0, "%d", atual++);
}

/*########################*/
/*###### X_PEN MODULE ####*/
/*########################*/

static double  __X_PEN_ANGLE = 0;
static double  __X_PEN_X = 200;
static double  __X_PEN_Y = 200;
static double  __X_PEN_THICK = 1;
static int     __X_PEN_DOWN = 1;

void   pen_set_angle(double degrees){
    __X_PEN_ANGLE = degrees;
}
void   pen_set_thick(int thick){
    if(thick > 0)
        __X_PEN_THICK = thick;
}
void   pen_set_pos(double x, double y){
    __X_PEN_X = x;
    __X_PEN_Y = y;
}
double pen_get_angle(){
    return __X_PEN_ANGLE;
}
int    pen_get_thick(){
    return __X_PEN_THICK;
}
double    pen_get_x(){
    return __X_PEN_X;
}
double    pen_get_y(){
    return __X_PEN_Y;
}
void   pen_up(void){
    __X_PEN_DOWN = 0;
}
void   pen_down(void){
    __X_PEN_DOWN = 1;
}
void   pen_walk(double distance){
    double x = __X_PEN_X + distance * math_cos(__X_PEN_ANGLE);
    double y = __X_PEN_Y - distance * math_sin(__X_PEN_ANGLE);
    if(__X_PEN_DOWN) {
        stroke_weight(__X_PEN_THICK);
        line(__X_PEN_X, __X_PEN_Y, x, y);
    }
    __X_PEN_X = x;
    __X_PEN_Y = y;
}
void   pen_rotate(int degrees){
    __X_PEN_ANGLE += degrees;
}
void   pen_goto(double x, double y){
    if(__X_PEN_DOWN) {
        stroke_weight(__X_PEN_THICK);
        line(__X_PEN_X, __X_PEN_Y, x, y);
    }
    __X_PEN_X = x;
    __X_PEN_Y = y;
}

