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

/* cria e retorna uma struct Color passando rgb */
Color make_color(uchar r, uchar g, uchar b, uchar a);

/* define uma cor na paleta de caracteres */
void x_set_palette(char c, Color color);

/* retorna uma cor dado um char.
   os char default da paleta são rgbmcybk
   outros podem ser definidos ou redefinidor com palette_set
*/
Color x_get_palette(char c);


void __x_init_pallete();

#endif /*XDDDX*/
