#ifndef DRAW_H /*XDDDX*/
#define DRAW_H /*XDDDX*/

#include "color.h" /*XDDDX*/
#include "xmath.h" /*XDDDX*/

/* ############################################### */
/* ############ FUNÇÕES DE DESENHO DE LINHAS ##### */
/* ############################################### */



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
int draw_art(int x, int y, int zoom, const char * picture);

/* desenha uma linha com anti aliasing com espessura de 1 pixel entre os pontos (x0, y0) e (x1, y1) */
void draw_line(double x0, double y0, double x1, double y1);

/* linha sem anti aliasing */
void raw_sline(int x0, int y0, int x1, int y1);

/* desenha uma linha com espessura de thickness pixels entre os pontos (x0, y0) e (x1, y1) */
void fill_line(double x0, double y0, double x1, double y1, int thickness);

/* desenha um circulo com centro (centerx, centerx) e raio radius */
void draw_circle(int centerx, int centery, int radius);

/* desenha um circulo dado centro e raio */
void fill_circle(int centerx, int centery, int radius);

/* desenha uma elipse dentro do rect de ponto superior esquerdo(x0, y0), largura e altura */
void draw_ellipse(int x0, int y0, int width, int height);

/* desenha uma elipse dentro do rect de ponto superior esquerdo(x0, y0), largura e altura */
void fill_ellipse(double x0, double y0, double width, double height);

/* desenha uma curva de bezier entre os pontos (x0, y0) e (x2, y2) */
/* a curvatura eh dada pelo ponto (x1, y1) */
void draw_bezier(int x0, int y0, int x1, int y1, int x2, int y2);

/* desenha um arco dado o ponto de centro, raio, espessura */
/* o angulo de inicio e o comprimento do arco em graus */
/* ambos os valores de ângulo podem ser negativos */
void fill_arc(double centerx, double centery, int radius, int thickness, int degrees_begin, int degrees_lenght);

/* desenha um triangulo dados os 3 vertices */
void raw_fill_triangle(double v1x, double v1y, double v2x, double v2y, double v3x, double v3y);

/* desenha um retangulo dados os cantos superior esquerdo (x0, y0), largura e altura */
void fill_rect(double x0, double y0, double width, double height);


#endif /*XDDDX*/
