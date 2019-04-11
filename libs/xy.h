#ifndef VEC2D_H /* XDDDX */
#define VEC2D_H /* XDDDX */

#ifdef __cplusplus
extern "C" {
#endif

/*
###############################################
####### ALGEBRA DE VETORES BIDIMENSIONAIS #####
###############################################
*/

/* Define um vetor bidimensional com x e y */
typedef struct{
    float x;
    float y;
} XY;

/* cria e retorna um vetor */
XY make_xy(float x, float y);

/* retorna o tamanho de um vetor da origem */
float xy_lenght(float x, float y);

/* retorna a distancia entre dois pontos */
float xy_distance(float ax, float ay, float bx, float by);

/* retorna a + b */
XY xy_sum(XY a, XY b);

/* retorna a - b */
XY xy_sub(XY a, XY b);

/* retorna (a.x * value, a.y * value) */
XY xy_dot(XY a, float value);

/* retorna o vetor normalizado */
XY xy_normalize(XY v);

/* retorna o vetor orthogonal */
XY xy_ortho(XY v);

#ifdef __cplusplus
}
#endif

#endif /* VEC2D_H XDDDX */
