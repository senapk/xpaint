
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

void gridInit(int side, int sep){
    __X_GRID_SIZE = side;
    __X_GRID_SEP = sep;
}

void gridSquare(int x, int y){
    int size = __X_GRID_SIZE, sep = __X_GRID_SEP;
    rect(x * size + sep, y * size + sep, size - sep, size - sep);
}


void gridCircle(int x, int y){
    circle(x * __X_GRID_SIZE + __X_GRID_SIZE / 2,
           y * __X_GRID_SIZE + __X_GRID_SIZE / 2,
               __X_GRID_SIZE - __X_GRID_SEP + 1);
}

V2d gridPos(int x, int y){
    return v2d(x * __X_GRID_SIZE + __X_GRID_SIZE / 2,
               y * __X_GRID_SIZE + __X_GRID_SIZE / 2);
}


void gridText(int x, int y, int dx, int dy, const char *format, ...){
    char _text[1000];
    va_list args;
    va_start( args, format );
    vsprintf(_text, format, args);
    va_end( args );
    text(x * __X_GRID_SIZE + dx, 
         y * __X_GRID_SIZE + dy, "%s", _text);

}

/*########################*/
/*###### X_BAR MODULE ####*/
/*########################*/


static float __X_BAR_WIDTH = 20; /* bar width */
static float __X_BAR_YFACTOR = 1; /* multiplicative factor of bar height  */
static int __X_BAR_SIZE = 0;
static int __X_BAR_MAX = 0;

void barInit(int size, int max){
    __X_BAR_SIZE = size;
    __X_BAR_MAX = max;
    __X_BAR_WIDTH = width() / (size + 2);
    __X_BAR_YFACTOR = (height() - 4.0 * __X_BAR_WIDTH);
    __X_BAR_YFACTOR = __X_BAR_YFACTOR < 0 ? -__X_BAR_YFACTOR : __X_BAR_YFACTOR;
    __X_BAR_YFACTOR /= max;
    if(__X_BAR_YFACTOR < 0.2)
        __X_BAR_YFACTOR = 0.2;
}

void barDrawOne(int i, int value){
    if((i < 0)||(i >= __X_BAR_SIZE))
        return;
    int x = __X_BAR_WIDTH * (i + 1);
    int ybase = height() - __X_BAR_WIDTH;
    int j;
    for(j = 0; j < ((int) __X_BAR_WIDTH - 2) ; j++)
        line(x + j, ybase, x + j, ybase - __X_BAR_YFACTOR * value);
}

void barDrawColors(int * vet, int size, const char * colors, int * indices){
    background("black");
    int i = 0;
    stroke("white");
    for(i = 0; i < size; i++)
        barDrawOne(i, vet[i]);
    if(colors != NULL && (strcmp(colors, "") != 0)){
        int qtd = strlen(colors);
        for(i = 0; i < qtd; i++){
            stroke("%c", colors[i]);
            barDrawOne(indices[i], vet[indices[i]]);
        }
    }
    static int atual = 0;
    stroke("white"); /* desenhando estado */
    text(10, 10, "%d", atual++);
}

/*########################*/
/*###### X_PEN MODULE ####*/
/*########################*/

static double  __X_PEN_ANGLE = 0;
static double  __X_PEN_X = 200;
static double  __X_PEN_Y = 200;
static double  __X_PEN_THICK = 1;
static int     __X_PEN_DOWN = 1;

void   penSetAngle(double degrees){
    __X_PEN_ANGLE = degrees;
}
void   penSetThick(int thick){
    if(thick > 0)
        __X_PEN_THICK = thick;
}
void   penSetPos(double x, double y){
    __X_PEN_X = x;
    __X_PEN_Y = y;
}
double penGetAngle(){
    return __X_PEN_ANGLE;
}
int    penGetThick(){
    return __X_PEN_THICK;
}
double    penGetX(){
    return __X_PEN_X;
}
double    penGetY(){
    return __X_PEN_Y;
}
void   penUp(void){
    __X_PEN_DOWN = 0;
}
void   penDown(void){
    __X_PEN_DOWN = 1;
}
void   penWalk(double distance){
    double x = __X_PEN_X + distance * xcos(__X_PEN_ANGLE);
    double y = __X_PEN_Y - distance * xsin(__X_PEN_ANGLE);
    if(__X_PEN_DOWN) {
        strokeWeight(__X_PEN_THICK);
        line(__X_PEN_X, __X_PEN_Y, x, y);
    }
    __X_PEN_X = x;
    __X_PEN_Y = y;
}
void   penRotate(int degrees){
    __X_PEN_ANGLE += degrees;
}
void   penGoto(double x, double y){
    if(__X_PEN_DOWN) {
        strokeWeight(__X_PEN_THICK);
        line(__X_PEN_X, __X_PEN_Y, x, y);
    }
    __X_PEN_X = x;
    __X_PEN_Y = y;
}

