#ifndef COLORS_H /*XDDDX*/
#define COLORS_H /*XDDDX*/


/*
###############################################
######## DEFINES e TIPOS BASICOS ##############
###############################################
*/

/* apelido para um char sem sinal */
typedef unsigned char uchar;

/* struct que representa uma cor RGB */
typedef struct{
    uchar r;
    uchar g;
    uchar b;
    uchar a;
} X_Color;


#define WHITE     (X_Color) {238, 232, 213, 255} // w
#define BLACK     (X_Color) {7  , 54 , 66 , 255} // k
#define GREEN     (X_Color) {133, 153, 0  , 255} // g
#define RED       (X_Color) {211, 1  , 2  , 255} // r
#define BLUE      (X_Color) {38 , 139, 210, 255} // b
#define YELLOW    (X_Color) {181, 137, 0  , 255} // y
#define CYAN      (X_Color) {42 , 161, 152, 255} // c
#define MAGENTA   (X_Color) {211, 54 , 130, 255} // m
#define ORANGE    (X_Color) {253, 106,   2, 255} // o
#define VIOLET    (X_Color) {108, 113, 196, 255} // v

/* cria e retorna uma struct X_Color passando rgb */
X_Color x_color_make(uchar r, uchar g, uchar b, uchar a);

/* define uma cor na paleta de caracteres */
void x_color_set_palette(char c, X_Color color);

/* retorna uma cor dado um char.
   os char default da paleta são rgbmcybk
   outros podem ser definidos ou redefinidor com palette_set
*/
X_Color x_color_get_palette(char c);


void __x_init_pallete();

#endif /*XDDDX*/
