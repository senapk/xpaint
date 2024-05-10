/*
You must use the following define in your code before #include the library
#define XPAINT
*/


/*
Autor:
    nome: David Sena Oliveira
    email: sena.ufc@gmail.com

Principais fontes:
    png: https://lodev.org/lodepng
    funções de desenho e matemáticas estão comentadas nas funções

Licença: GPLv3

Versão: 1.1

*/

/* Exemplo de uso */

#if 0
#define XPAINT
#include "xpaint.h"
int main(){
    int largura = 600, altura = 500;
    xopen(largura, altura, "figura_base"); 
    text(50, 30, "Pintarei um circulo vermelho em %d %d", largura/2, altura/2);
    background("white");
    stroke("black");
    fill("red")
    circle(largura/2, altura/2, 200);
    save();
    xclose();
    return 0;
}
#endif
