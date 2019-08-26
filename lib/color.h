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
} X_Color;

/* lista de cores default */
extern X_Color X_COLOR_RED;
extern X_Color X_COLOR_GREEN;
extern X_Color X_COLOR_BLUE;
extern X_Color X_COLOR_YELLOW;
extern X_Color X_COLOR_CYAN;
extern X_Color X_COLOR_MAGENTA;
extern X_Color X_COLOR_ORANGE;
extern X_Color X_COLOR_VIOLET;
extern X_Color X_COLOR_WHITE;
extern X_Color X_COLOR_BLACK;

/* cria e retorna uma struct X_Color passando rgb */
X_Color x_make_color(uchar r, uchar g, uchar b);

/*
###############################################
### FUNÇÕES SET: Cor, Fonte, Paleta de Cores ##
###############################################
*/

/* define uma cor na palheta de caracteres */
void x_set_palette(char c, X_Color color);

/* retorna uma cor dado um char.
   os char default da paleta são rgbmcybk
   outros podem ser definidos ou redefinidor com x_set_palette
*/
X_Color x_get_palette(char c);

/* inicializa as cores da paleta
*/
void __x_init_colors(void);

#endif /*XDDDX*/
