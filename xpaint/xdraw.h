#ifndef XDRAW_H //XDDDX
#define XDRAW_H //XDDDX
//Desenha as seguintes formas
void xd_line(int x0, int y0, int x1, int y1);
void xd_thick_line(float ax, float ay, float bx, float by, int thickness);
void xd_circle(int x0, int y0, int radius);
void xd_ellipse(int x0, int y0, int x1, int y1);
void xd_bezier(int x0, int y0, int x1, int y1, int x2, int y2);
void xd_arc(float centerx, float centery, int radius, int thickness, int degrees_begin, int degrees_end);

//Desenha formas preenchidas (filled)
void xd_filled_triangle(float v1x, float v1y, float v2x, float v2y, float v3x, float v3y);
void xd_filled_square(int x0, int y0, int x1, int y1);
void xd_filled_circle(int mx, int my, int radius);
void xd_filled_ellipse(int x0, int y0, int x1, int y1);
#endif // XDRAW_H XDDDX
