#ifndef XDRAW_H //XDDDX
#define XDRAW_H //XDDDX


//###############################################
//############ FUNÇÕES DE DESENHO ###############
//###############################################


//Desenha as seguintes formas sem preenchimento
void xd_line(int x0, int y0, int x1, int y1);
void xd_thick_line(float ax, float ay, float bx, float by, int thickness);
void xd_circle(int centerx, int centery, int radius);
void xd_ellipse(int x0, int y0, int x1, int y1);
void xd_bezier(int x0, int y0, int x1, int y1, int x2, int y2);

//Desenha formas preenchidas (filled)
void xd_filled_arc(float centerx, float centery, int radius, int thickness, int degrees_begin, int degrees_end);
void xd_filled_triangle(float v1x, float v1y, float v2x, float v2y, float v3x, float v3y);
void xd_filled_rect(int x0, int y0, int x1, int y1);
void xd_filled_circle(int mx, int my, int radius);
void xd_filled_ellipse(int x0, int y0, int x1, int y1);
#endif // XDRAW_H XDDDX
