
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

void gridSquare(int l, int c){
    int size = __X_GRID_SIZE, sep = __X_GRID_SEP;
    rect(c * size + sep, l * size + sep, size - sep, size - sep);
}

void gridCircle(int l, int c){
    circle(c * __X_GRID_SIZE + __X_GRID_SIZE / 2, l * __X_GRID_SIZE + __X_GRID_SIZE / 2,
                  __X_GRID_SIZE / 2 - __X_GRID_SEP + 1);
}


void gridText(int l, int c, const char *format, ...){
    char text[1000];
    va_list args;
    va_start( args, format );
    vsprintf(text, format, args);
    va_end( args );
    float xdelta = 0.13, ydelta = 0.35;
    text((c + xdelta) * __X_GRID_SIZE, (l + ydelta) * __X_GRID_SIZE, "%s", text);

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

void barOne(int i, int value){
    if((i < 0)||(i >= __X_BAR_SIZE))
        return;
    int x = __X_BAR_WIDTH * (i + 1);
    int ybase = height() - __X_BAR_WIDTH;
    int j;
    for(j = 0; j < ((int) __X_BAR_WIDTH - 2) ; j++)
        line(x + j, ybase, x + j, ybase - __X_BAR_YFACTOR * value);
}

void barAll(int * vet, int size, const char * colors, int * indices){
    background(BLACK);
    int i = 0;
    stroke(WHITE);
    for(i = 0; i < size; i++)
        barOne(i, vet[i]);
    if(colors != NULL && (strcmp(colors, "") != 0)){
        int qtd = strlen(colors);
        for(i = 0; i < qtd; i++){
            stroke_char(colors[i]);
            barOne(indices[i], vet[indices[i]]);
        }
    }
    static int atual = 0;
    stroke(WHITE); /* desenhando estado */
    text(0, 0, "%d", atual++);
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
    double x = __X_PEN_X + distance * math_cos(__X_PEN_ANGLE);
    double y = __X_PEN_Y - distance * math_sin(__X_PEN_ANGLE);
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

