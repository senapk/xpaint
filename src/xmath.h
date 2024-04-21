#ifndef XMATH_H /*XDDDX*/
#define XMATH_H /*XDDDX*/

/* Faz o SWAP entre dois tipos */
#define X_SWAP(x, y, T) do { T X_SWAP = x; x = y; y = X_SWAP; } while (0)

/*
###############################################
####### ALGEBRA DE VETORES BIDIMENSIONAIS #####
###############################################
*/

/* Define um vetor bidimensional com x e y */
typedef struct{
    double x;
    double y;
} V2d;

/* cria e retorna um vetor */
V2d make_v2d(double x, double y);

/* retorna o tamanho de um vetor da origem */
double v2d_length(double x, double y);

/* retorna a distancia entre dois pontos */
double v2d_distance(double ax, double ay, double bx, double by);

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

double math_sqrt(const double m);
double math_pow( double x, double y );
int    math_floor(double x);
int    math_round(double x);
double math_fmod(double a, double b);
int    math_ceil(double n);
/* degrees */
double math_sin(double d);
double math_cos(double d);
double math_acos(double x);
double math_fabs(double f);
/* Generates a int number in interval [min, max[ */
int    math_rand(int min, int max);

#endif /*XDDDX*/

