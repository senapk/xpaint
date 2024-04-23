#ifndef COLORS_H /*XDDDX*/
#define COLORS_H /*XDDDX*/
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

#endif /*XDDDX*/
