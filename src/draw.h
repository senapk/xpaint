#ifndef DRAW_H /*XDDDX*/
#define DRAW_H /*XDDDX*/

#include "color.h" /*XDDDX*/
#include "xmath.h" /*XDDDX*/

/* ############################################### */
/* ############ FUNÇÕES DE DESENHO DE LINHAS ##### */
/* ############################################### */

void stroke_weight(int thickness);

/* a funcao plot pinta o pixel transformado */
void point(double x, double y, Color color);

/* muda a cor do pincel*/
void stroke(Color color);

/* muda a cor do pincel*/
void stroke_rgba(uchar r, uchar g, uchar b, uchar a);

/* muda a cor do pincel usando a paleta de cores*/
void stroke_char(char c);

/* muda a cor do pincel*/
void fill(Color color);

/* muda a cor do pincel*/
void fill_rgba(uchar r, uchar g, uchar b, uchar a);

/* muda a cor do pincel usando a paleta de cores*/
void fill_char(char c);

/* desabilita o pincel */
void no_stroke();

/* desabilita o preenchimento */
void no_fill();

/* return the current color for brush */
Color get_stroke(void);

/* return the current color for brush */
Color get_fill(void);


/* desenha uma forma utilizando uma string e o mapa de cores default */
int asc_art(int x, int y, int zoom, const char * picture);
void line(double x0, double y0, double x1, double y1);
void ellipse(double x0, double y0, double width, double height);

/* desenha um arco dado o ponto de centro, raio, espessura */
/* o angulo de inicio e o comprimento do arco em graus */
/* ambos os valores de ângulo podem ser negativos */
void arc(double centerx, double centery, int radius, int thickness, int degrees_begin, int degrees_lenght);
void circle(int centerx, int centery, int radius);
void rect(double x, double y, double witdh, double height);
void square(double x, double y, double size);
void bezier(double xa, double ya, double xb, double yb, double xc, double yc, double xd, double yd);
void triangle(double x0, double y0, double x1, double y1, double x2, double y2);

#endif /*XDDDX*/
