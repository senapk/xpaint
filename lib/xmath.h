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
} X_V2d;

/* cria e retorna um vetor */
X_V2d x_make_v2d(double x, double y);

/* retorna o tamanho de um vetor da origem */
double x_v2d_length(double x, double y);

/* retorna a distancia entre dois pontos */
double x_v2d_distance(double ax, double ay, double bx, double by);

/* retorna a + b */
X_V2d x_v2d_sum(X_V2d a, X_V2d b);

/* retorna a - b */
X_V2d x_v2d_sub(X_V2d a, X_V2d b);

/* retorna (a.x * value, a.y * value) */
X_V2d x_v2d_dot(X_V2d a, double value);

/* retorna o vetor normalizado */
X_V2d x_v2d_normalize(X_V2d v);

/* retorna o vetor orthogonal */
X_V2d x_v2d_ortho(X_V2d v);

/*
###############################################
############ FUNÇÕES MATEMATICAS ##############
###############################################
*/

/*
Essas funções foram adicionadas para que a biblioteca
xpaint não dependesse de incluir a biblioteca math.h
nos parametros de compilação com o -lm
*/

double xm_sqrt(const double m);
double xm_pow( double x, double y );
int   xm_floor(double x);
double xm_fmod(double a, double b);
int   xm_ceil(double n);
/* degrees */
double xm_sin(double d);
double xm_cos(double d);
double xm_acos(double x);
double xm_fabs(double f);
/* Generates a int number in interval [min, max] */
int   xm_rand(int min, int max);

#endif /*XDDDX*/

