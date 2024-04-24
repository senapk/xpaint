#ifndef XMATH_H /*XDDDX*/
#define XMATH_H /*XDDDX*/

#include "base.h" /*XDDDX*/

/* Faz o SWAP entre dois tipos */
#define X_SWAP(x, y, T) do { T X_SWAP = x; x = y; y = X_SWAP; } while (0)

// ---------------------------- ALGEBRA DE VETORES ----------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

// retorna a distancia entre dois pontos
double dist(double ax, double ay, double bx, double by);

// cria e retorna um vetor
V2d v2d(double x, double y);

// retorna o tamanho de um vetor da origem
double v2d_length(double x, double y);

// retorna a + b
V2d v2d_sum(V2d a, V2d b);

// retorna a - b
V2d v2d_sub(V2d a, V2d b);

// retorna (a.x * value, a.y * value)
V2d v2d_dot(V2d a, double value);

// retorna o vetor normalizado
V2d v2d_normalize(V2d v);

// retorna o vetor orthogonal
V2d v2d_ortho(V2d v);

// ---------------------------- FUNÇÕES MATEMÁTICAS ---------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

// raiz quadrada
double xsqrt(const double m);

// função potência
double xpow( double x, double y );

// função piso
int    xfloor(double x);

// função de arredondamento
int    xround(double x);

// o módulo de um número, mas com o divisor sendo um double
double xfmod(double a, double b);

// função teto
int    xceil(double n);

// calcula o seno de um angulo em graus
double xsin(double d);

// calcula o cosseno de um angulo em graus
double xcos(double d);

// calcula o arco cosseno de x em graus
double xacos(double x);

// calcula o arco seno de x em graus
double xfabs(double f);

// gera um valor inteiro aleatório entre min e max
// não incluindo o max
int xrand(int min, int max);

#endif /*XDDDX*/

