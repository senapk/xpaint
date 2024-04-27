

// ---------------------------- GRID ------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

#include <stdarg.h>
#include "base.h" /*XDDDX*/

// inicia o grid
// side é o tamanho da célula
// sep é o espaço em preto entre as células
void gridInit(int side, int sep);

// plota um quadrado na célula
void gridSquare(int x, int y);

// plota um círculo na célula
void gridCircle(int x, int y);

V2d gridPos(int x, int y);

// escreve o texto na posição da grid (x, y)
// texto pode ser ajustado usando dx e dy
void gridText(int x, int y, int dx, int dy, const char *format, ...);


// ---------------------------- VETORES ---------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


// inicia o vetor
// size é o tamanho do vetor
// max é o valor máximo do vetor
void barInit(int size, int max);

// plota um valor no vetor
// i é a posição do valor
// value é o valor a ser plotado
void barDrawOne(int i, int value);

// plota todos os valores do vetor
// colors é um vetor de cores para marcar elementos únicos ou NULL
// indices é um vetor com os índices únicos a serem marcados com as cores
void barDrawColors(int * vet, int size, const char * colors, int * indices);


#define barDrawAll(vet, size, colors, ...) do{\
    int __indices[] = {__VA_ARGS__};\
    barDrawColors(vet, size, colors, __indices);\
} while(0);


// ---------------------------- CANETA ---------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

void   penSetAngle(double degrees);
void   penSetThick(int thick);
void   penSetPos(double x, double y);
double penGetAngle();
int    penGetThick();
double penGetX();
double penGetY();
void   penUp(void);
void   penDown(void);
void   penWalk(double distance);
void   penRotate(int degrees);
void   penGoto(double x, double y);




