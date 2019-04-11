#ifndef XMATH_H /* XDDDX */
#define XMATH_H /* XDDDX */

#ifdef __cplusplus
extern "C" {
#endif

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

float xm_sqrt(const float m);
float xm_pow( float x, float y );
int   xm_floor(double x);
float xm_fmod(float a, float b);
int   xm_ceil(float n);
float xm_sin(float d);
float xm_cos(float d);
float xm_acos(float x);
float xm_fabs(float f);
/* generates a number [min, max] */
int   xm_rand(int min, int max);

/*
###################################################
#         INICIO DA IMPLEMENTACAO                 #  
#                                                 #
#   O código abaixo apenas será inserido se       #
#   você incluir o #define XFULL antes de incluir #
#   essa biblioteca.                              #
###################################################
*/

#ifdef __cplusplus
}
#endif



#endif /* XMATH_H XDDDX */


