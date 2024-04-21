#ifndef DRAW_H /*XDDDX*/
#define DRAW_H /*XDDDX*/

/* ############################################### */
/* ############ FUNÇÕES DE DESENHO DE LINHAS ##### */
/* ############################################### */

/* desenha uma forma utilizando uma string e o mapa de cores default */
int draw_art(int x, int y, int zoom, const char * picture);

/* desenha uma linha com anti aliasing com espessura de 1 pixel entre os pontos (x0, y0) e (x1, y1) */
void draw_line(int x0, int y0, int x1, int y1);

/* linha sem anti aliasing */
void draw_sline(int x0, int y0, int x1, int y1);

/* desenha uma linha com espessura de thickness pixels entre os pontos (x0, y0) e (x1, y1) */
void fill_line(float x0, float y0, float x1, float y1, int thickness);

/* desenha um circulo com centro (centerx, centerx) e raio radius */
void draw_circle(int centerx, int centery, int radius);

/* desenha um circulo dado centro e raio */
void fill_circle(int centerx, int centery, int radius);

/* desenha uma elipse dentro do rect de ponto superior esquerdo(x0, y0), largura e altura */
void draw_ellipse(int x0, int y0, int width, int height);

/* desenha uma elipse dentro do rect de ponto superior esquerdo(x0, y0), largura e altura */
void fill_ellipse(int x0, int y0, int width, int height);

/* desenha uma curva de bezier entre os pontos (x0, y0) e (x2, y2) */
/* a curvatura eh dada pelo ponto (x1, y1) */
void draw_bezier(int x0, int y0, int x1, int y1, int x2, int y2);

/* desenha um arco dado o ponto de centro, raio, espessura */
/* o angulo de inicio e o comprimento do arco em graus */
/* ambos os valores de ângulo podem ser negativos */
void fill_arc(float centerx, float centery, int radius, int thickness, int degrees_begin, int degrees_lenght);

/* desenha um triangulo dados os 3 vertices */
void fill_triangle(float v1x, float v1y, float v2x, float v2y, float v3x, float v3y);

/* desenha um retangulo dados os cantos superior esquerdo (x0, y0), largura e altura */
void fill_rect(int x0, int y0, int width, int height);


#endif /*XDDDX*/
