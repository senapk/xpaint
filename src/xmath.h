#ifndef XMATH_H /*XDDDX*/
#define XMATH_H /*XDDDX*/

#include "base.h" /*XDDDX*/
/* Faz o SWAP entre dois tipos */
#define X_SWAP(x, y, T) do { T X_SWAP = x; x = y; y = X_SWAP; } while (0)

/*
###############################################
####### ALGEBRA DE VETORES BIDIMENSIONAIS #####
###############################################
*/

/* cria e retorna um vetor */
V2d v2d(double x, double y);

/* retorna o tamanho de um vetor da origem */
double v2d_length(double x, double y);

/* retorna a distancia entre dois pontos */
double dist(double ax, double ay, double bx, double by);

/* retorna a + b */
V2d v2d_sum(V2d a, V2d b);

/* retorna a - b */
V2d v2d_sub(V2d a, V2d b);

/* retorna (a.x * value, a.y * value) */
V2d v2d_dot(V2d a, double value);

/* retorna o vetor normalizado */
V2d v2d_normalize(V2d v);

/* retorna o vetor orthogonal */
V2d v2d_ortho(V2d v);

// ####### FUNÇÕES MATEMATICAS ##############

double xsqrt(const double m);
double xpow( double x, double y );
int    xfloor(double x);
int    xround(double x);
double xfmod(double a, double b);
int    xceil(double n);
/* degrees */
double xsin(double d);
double xcos(double d);
double xacos(double x);
double xfabs(double f);
/* Generates a int number in interval [min, max[ */
int    xrand(int min, int max);

#endif /*XDDDX*/

