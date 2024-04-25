#ifndef COLORS_H /*XDDDX*/
#define COLORS_H /*XDDDX*/
#include <stdarg.h>


// ---------------------------- CORES -----------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

// apelido para um char sem sinal
typedef unsigned char uchar;

// struct que representa uma cor RGBA
typedef struct{
    uchar r;
    uchar g;
    uchar b;
    uchar a;
} Color;

// cria e retorna uma struct Color passando rgba
// rgba(255, 0, 0, 0); // vermelho
Color rgba(uchar r, uchar g, uchar b, uchar a);


// Cria ou obtém uma cor da paleta, possui vários modos
// 1: uso de hexadecimal como : "#00ffbb"
// 2: uso de rgba entre virgulas "144,123,12,255"
// 3. tons de cinza entre 0 e 255: "100", "0", "150"
// 4: uso de palavras chave ou letras
//     "black" ou "k"
//     "white" ou "w"
//     "red", "blue", "yellow", "pink", "cyan", ...
// 5: pode ser construído com a sintexa do printf
//     ("%d, %d, %d", 10, 20 , 30)
Color color(const char * format, ...);

// define uma entrada na paleta de cores
// entry: chave para a cor, que pode ser uma letra ou palavra
// color: cor a ser registrada
void setPallete(const char * entry, Color color);

// Printa todas as cores nomeadas atualmente cadastradas
void colorShowAll();

// Mostra a cor no terminal
void colorShow(Color color);

// ---------------------------- FUNÇÕES INTERNAS ------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

// inicializa as cores da paleta e da base
void __init_colors(void);

#endif /*XDDDX*/
