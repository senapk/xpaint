// #ifndef COLORS_H /*XDDDX*/
// #define COLORS_H /*XDDDX*/
// #include <stdarg.h>

// /*
// ###############################################
// ######## DEFINES e TIPOS BASICOS ##############
// ###############################################
// */

// /* apelido para um char sem sinal */
// typedef unsigned char uchar;

// #define X_BYTES_PER_PIXEL 4

// /* struct que representa uma cor RGB */
// typedef struct{
//     uchar r;
//     uchar g;
//     uchar b;
//     uchar a;
// } X_Color;

// extern const char * WHITE     ;
// extern const char * BLACK     ;
// extern const char * GREEN     ;
// extern const char * RED       ;
// extern const char * BLUE      ;
// extern const char * YELLOW    ;
// extern const char * CYAN      ;
// extern const char * MAGENTA   ;
// extern const char * VIOLET    ;
// extern const char * ORANGE    ;

// /* cria e retorna uma struct X_Color passando rgb */
// X_Color x_color_make(uchar r, uchar g, uchar b, uchar a);

// /*
// ###############################################
// ### FUNÇÕES SET: Cor, Fonte, Paleta de Cores ##
// ###############################################
// */


// /* define uma entrada na paleta de cores
// index: pode ser utilizado para registrar chaves ou ' ' se nao quiser
// entry: eh o nome da cor
// */
// void x_color_add(const char * entry, X_Color color);

// /* obtém uma cor da paleta, possui vários modos
// 1: uso de hexadecimal como : "#00ffbb"
// 2: uso de rgba entre virgulas "144,123,12,255"
// 3: uso de palavras chave ou letras
//     "black" ou "k"
//     "white" ou "w"
//     "red", "blue", "yellow", "pink", "cyan", ...
//     ("%d, %d, %d", 10, 20 , 30)
// */
// X_Color x_color_decode(const char * format, ...);

// /* inicializa as cores da paleta e da base
// */
// void __x_init_colors(void);

// #endif /*XDDDX*/
