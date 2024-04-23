#ifndef XPAINT_H
#define XPAINT_H
#ifdef __cplusplus
extern "C" {
#endif
/*
You must use the following define in your code before #include the library
#define XPAINT
*/


/*
Autor:
    nome: David Sena Oliveira
    email: sena.ufc@gmail.com

Principais fontes:
    png: https://lodev.org/lodepng
    funções de desenho e matemáticas estão comentadas nas funções

Licença: GPLv3

Versão: 1.0

*/

/* Exemplo de uso */

#if 0
#define XPAINT
#include "xpaint.h"
int main(){
    int largura = 600, altura = 500;
    open(largura, altura, "figura_base"); 
    text(50, 30, "Pintarei um circulo vermelho em %d %d", largura/2, altura/2);
    background(WHITE);
    stroke(BLACK);
    fill(RED)
    circle(largura/2, altura/2, 200);
    save();
    close();
    return 0;
}
#endif
#include <stdarg.h>

/*
###############################################
######## DEFINES e TIPOS BASICOS ##############
###############################################
*/

/* apelido para um char sem sinal */
typedef unsigned char uchar;

// #define X_BYTES_PER_PIXEL 4

/* struct que representa uma cor RGB */
typedef struct{
    uchar r;
    uchar g;
    uchar b;
    uchar a;
} Color;

#define WHITE     (Color) {238, 232, 213, 255} // w
#define BLACK     (Color) {7  , 54 , 66 , 255} // k
#define GREEN     (Color) {133, 153, 0  , 255} // g
#define RED       (Color) {211, 1  , 2  , 255} // r
#define BLUE      (Color) {38 , 139, 210, 255} // b
#define YELLOW    (Color) {181, 137, 0  , 255} // y
#define CYAN      (Color) {42 , 161, 152, 255} // c
#define MAGENTA   (Color) {211, 54 , 130, 255} // m
#define ORANGE    (Color) {253, 106,   2, 255} // o
#define VIOLET    (Color) {108, 113, 196, 255} // v

/* cria e retorna uma struct Color passando rgba */
Color rgba(uchar r, uchar g, uchar b, uchar a);


/* obtém uma cor da paleta, possui vários modos
1: uso de hexadecimal como : "#00ffbb"
2: uso de rgba entre virgulas "144,123,12,255"
3. tons de cinza entre 0 e 255: "100", "0", "150"
4: uso de palavras chave ou letras
    "black" ou "k"
    "white" ou "w"
    "red", "blue", "yellow", "pink", "cyan", ...
5: pode ser construído com a sintexa do printf
    ("%d, %d, %d", 10, 20 , 30)
*/
Color color(const char * format, ...);

/*
###############################################
### FUNÇÕES SET: Cor, Fonte, Paleta de Cores ##
###############################################
*/


/* define uma entrada na paleta de cores
index: pode ser utilizado para registrar uma cor na paleta
entry: chave para a cor, que pode ser uma letra ou palavra
color: cor a ser registrada
*/
void setPallete(const char * entry, Color color);

/* inicializa as cores da paleta e da base
*/
void __init_colors(void);

void color_print_all();
void color_show(Color color);



#include <stdarg.h>

/* @brief Open the board to draw */
/* @param filename path to save the png */
void open(unsigned int width, unsigned int height, const char * filename);

/* retorna altura, largura, filename and bitmap */
int          height(void);
int          width(void);
const char * getFilename(void);
uchar      * getBitmap(void);


/* @brief Clear all resources */
void close(void);

/* @brief Changes the the default filename to save the image */
/* @param filename path */
void setFilename(const char * filename);

void __plot(int x, int y,  Color color);

/* retorna a cor do pixel dessa posicao do bitmap */
Color getPixel(int x, int y);

/* limpa a tela inteira com a mesma cor */
void background(Color color);

/* save the bitmap in filename.png */
void save(void);

/* Enable interactive save and lock control */
void setLock();

/*
    define folder to saves the file with a numeric sufix at the end
    if the filename is img, sequencial calls of this function
    will save the following files
    img_00000.png img_00001.png img_00002.png img_00003.png
*/
void setLog(const char * folder);

/* creates a .mp4 video using all .png stored in folder using ffmpeg */
void makeVideo(int framerate, const char * mp4_filename);

typedef struct {
    double dx;
    double dy;
    double s;
    double angle;
} Transform;

/* Define um vetor bidimensional com x e y */
typedef struct{
    double x;
    double y;
} V2d;

void push();
void pop();
void translate(double dx, double dy);
void scale(double s);
void rotate(double angle);

V2d __transform(double x, double y);
double __get_transform_scale();



/* ############################################### */
/* ############ FUNÇÕES DE DESENHO DE LINHAS ##### */
/* ############################################### */

void strokeWeight(int thickness);

/* a funcao __plot pinta o pixel transformado */
void point(double x, double y, Color color);

/* muda a cor do pincel*/
void stroke(Color color);

// /* muda a cor do pincel*/
// void stroke_rgba(uchar r, uchar g, uchar b, uchar a);

// /* muda a cor do pincel usando a paleta de cores*/
// void stroke_char(char c);

/* muda a cor do pincel*/
void fill(Color color);

// /* muda a cor do pincel*/
// void fill_rgba(uchar r, uchar g, uchar b, uchar a);

// /* muda a cor do pincel usando a paleta de cores*/
// void fill_char(char c);

/* desabilita o pincel */
void noStroke();

/* desabilita o preenchimento */
void noFill();

/* return the current color for brush */
Color getStroke(void);

/* return the current color for brush */
Color getFill(void);


/* desenha uma forma utilizando uma string e o mapa de cores default */
int ascArt(int x, int y, int zoom, const char * picture);
void line(double x0, double y0, double x1, double y1);
void ellipse(double x0, double y0, double width, double height);

/* desenha um arco dado o ponto de centro, raio, espessura */
/* o angulo de inicio e o comprimento do arco em graus */
/* ambos os valores de ângulo podem ser negativos */
void arc(double centerx, double centery, int radius, int thickness, int degrees_begin, int degrees_lenght);
void circle(int centerx, int centery, int diameter);
void rect(double x, double y, double witdh, double height);
void square(double x, double y, double size);
void bezier(double xa, double ya, double xb, double yb, double xc, double yc, double xd, double yd);
void triangle(double x0, double y0, double x1, double y1, double x2, double y2);


#include <stdarg.h>
//inicializa o módulo de escrita
void __x_init_font();

// muda o tamanho da font
void textSize(int size);

// escreve utilizando o formato printf
// retorna a posicao final em x
int text(int x, int y, const char * format, ...);

/* Faz o SWAP entre dois tipos */
#define X_SWAP(x, y, T) do { T X_SWAP = x; x = y; y = X_SWAP; } while (0)

/*
###############################################
####### ALGEBRA DE VETORES BIDIMENSIONAIS #####
###############################################
*/

/* cria e retorna um vetor */
V2d v2d(double x, double y);

/* retorna o tamanho de um vetor da origem */
double v2d_length(double x, double y);

/* retorna a distancia entre dois pontos */
double dist(double ax, double ay, double bx, double by);

/* retorna a + b */
V2d v2d_sum(V2d a, V2d b);

/* retorna a - b */
V2d v2d_sub(V2d a, V2d b);

/* retorna (a.x * value, a.y * value) */
V2d v2d_dot(V2d a, double value);

/* retorna o vetor normalizado */
V2d v2d_normalize(V2d v);

/* retorna o vetor orthogonal */
V2d v2d_ortho(V2d v);

// ####### FUNÇÕES MATEMATICAS ##############

double xsqrt(const double m);
double xpow( double x, double y );
int    xfloor(double x);
int    xround(double x);
double xfmod(double a, double b);
int    xceil(double n);
/* degrees */
double xsin(double d);
double xcos(double d);
double xacos(double x);
double xfabs(double f);
/* Generates a int number in interval [min, max[ */
int    xrand(int min, int max);


/*
###############################################
############ FUNÇÕES DE GRID ##################
###############################################
*/
#include <stdarg.h>
/*Init the grid*/
/*side is the size of the cell */
/*sep the space in black between cells */
void gridInit(int side, int sep);

/*plots a square in cell*/
void gridSquare(int l, int c);

/*plots a circle in cell*/
void gridCircle(int l, int c);

/*writes a text until 5 char in cell*/
void gridText(int l, int c, const char *format, ...);


/*
###############################################
####### FUNÇÕES PARA VISUALIZAR VETORES #######
###############################################
*/


/**
 * @brief initialize the module to print bars for show sort
 * 
 * @param size the size of the array
 * @param max the max value of the array
 */
void barInit(int size, int max);

/**
 * @brief print a single bar
 * 
 * @param i the index
 * @param value the value of the bar size
 */
void barOne(int i, int value);

/**
 * @brief show the entire array
 * 
 * @param vet the vector with the values
 * @param size of the vector
 * @param colors the array of color to mark unique elements or NULL
 * @param indices the array with the unique indices to be marked with the colors
 */
void barAll(int * vet, int size, const char * colors, int * indices);


#define barSave(vet, size, colors, ...) do{\
    int __indices[] = {__VA_ARGS__};\
    barAll(vet, size, colors, __indices);\
    save();\
} while(0);

/*
###############################################
####### FUNÇÕES PARA DESENHAR COM A CANETA ####
###############################################
*/

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




#ifdef __cplusplus
}
#endif
#endif /* XPAINT_H */
