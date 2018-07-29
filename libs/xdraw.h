#ifndef XDRAW_H //XDDDX
#define XDRAW_H //XDDDX


//###############################################
//############ FUNÇÕES DE DESENHO DE LINHAS #####
//###############################################


//Desenha as seguintes formas sem preenchimento

//desenha uma linha com espessura de 1 pixel entre os pontos (x0, y0) e (x1, y1)
void xd_line(int x0, int y0, int x1, int y1);

//desenha uma linha com espessura de thickness pixels entre os pontos (x0, y0) e (x1, y1)
void xd_thick_line(float x0, float y0, float x1, float y1, int thickness);

//desenha um circulo com centro (centerx, centerx) e raio radius
void xd_circle(int centerx, int centery, int radius);

//desenha uma elipse dentro do rect de ponto superior esquerdo(x0, y0) 
//e ponto inferior direito (x1, y1)
void xd_ellipse(int x0, int y0, int x1, int y1);

//desenha uma curva de bezier entre os pontos (x0, y0) e (x2, y2)
//a curvatura eh dada pelo ponto (x1, y1)
void xd_bezier(int x0, int y0, int x1, int y1, int x2, int y2);


//###############################################
//### FUNÇÕES DE DESENHO FORMAS PREENCHIDAS #####
//###############################################

//desenha um arco dado o ponto de centro, raio, espessura
//o angulo de inicio e o angulo de fim
//o angulo de inicio deve ser sempre menor que o angulo de fim
//o desenho é feito no sentido anti horario
//o angulo pode superar 360
void xd_filled_arc(float centerx, float centery, int radius, int thickness, int degrees_begin, int degrees_end);

//desenha um triangulo dados os 3 vertices
void xd_filled_triangle(float v1x, float v1y, float v2x, float v2y, float v3x, float v3y);

//desenha um retangulo dados os cantos superior esquerdo (x0, y0) e inferior direito (x1, y1)
void xd_filled_rect(int x0, int y0, int x1, int y1);

//desenha um circulo dado centro e raio
void xd_filled_circle(int centerx, int centery, int radius);

//desenha uma elipse dentro do rect de ponto superior esquerdo(x0, y0) 
//e ponto inferior direito (x1, y1)
void xd_filled_ellipse(int x0, int y0, int x1, int y1);
#endif // XDRAW_H XDDDX
