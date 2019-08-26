/*
You must use the following define in your code before #include the library
#define XPAINT_FULL
*/


/*
Autor:
    nome: David Sena Oliveira
    email: sena.ufc@gmail.com

Principais fontes:
    png: https://lodev.org/lodepng
    tff: https://github.com/nothings/stb
    funções de desenho e matemáticas estão comentadas nas funções

Licença: GPLv3

Versão: 0.7

*/

/* Exemplo de uso */

#if 0
#define XPAINT_FULL
#include "xpaint.h"
int main(){
    int largura = 600, altura = 500;
    x_open(largura, altura, "figura_base"); 
    x_write(50, 30, "Pintarei um circulo vermelho em %d %d", largura/2, altura/2);
    x_set_color(X_COLOR_RED);
    x_fill_circle(largura/2, altura/2, 200);
    x_save();
    x_close();
    return 0;
}
#endif

