#ifndef DRAW_H /*XDDDX*/
#define DRAW_H /*XDDDX*/

#include "color.h" /*XDDDX*/
#include "xmath.h" /*XDDDX*/

// ---------------------------- DESENHO -----------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

// muda a espessura do traço
void strokeWeight(int thickness);

// plota um pixel utilizando a função stroke
void point(double x, double y);

// muda a cor do pincel para pontos, linhas e bordas
void stroke(Color color);

// muda a cor do pincel para preenchimento
void fill(Color color);

// desabilita pontos, linhas e bordas
void noStroke();

// desabilita o preenchimento
void noFill();

// devolve a cor atual do stroke
Color getStroke(void);

// devolve a cor atual do fill
Color getFill(void);

// desenha uma forma utilizando uma string e o mapa de cores default
int  ascArt(int x, int y, int zoom, const char * picture);

// desenha uma linha entre dois pontos
void line(double x0, double y0, double x1, double y1);

// desenha uma elipse dado o ponto de centro, largura e altura
void ellipse(double x0, double y0, double width, double height);

// desenha um arco dado o ponto de centro, raio, espessura
// o angulo de inicio e o comprimento do arco em graus
// ambos os valores de ângulo podem ser negativos
void arc(double centerx, double centery, int radius, int thickness, int degrees_begin, int degrees_lenght);

// desenha um círculo dado o ponto de centro e o diâmetro
void circle(int centerx, int centery, int diameter);

// desenha um retângulo dado o ponto de canto superior esquerdo, largura e altura
void rect(double x, double y, double witdh, double height);

// desenha um quadrado dado o ponto de canto superior esquerdo e o tamanho
void square(double x, double y, double size);

// desenha uma curva de bezier dado os pontos
// inicial A, final B e os pontos de controle C e D
void bezier(double xa, double ya, double xb, double yb, double xc, double yc, double xd, double yd);

// desenha um triângulo dado os pontos
void triangle(double x0, double y0, double x1, double y1, double x2, double y2);

#endif /*XDDDX*/
