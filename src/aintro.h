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

Versão: 0.8

*/

/* Exemplo de uso */

#if 0
#define XPAINT
#include "xpaint.h"
int main(){
    int largura = 600, altura = 500;
    open(largura, altura, "figura_base"); 
    text(50, 30, "Pintarei um circulo vermelho em %d %d", largura/2, altura/2);
    background(WHITE);
    stroke(BLACK);
    fill(RED)
    circle(largura/2, altura/2, 200);
    save();
    close();
    return 0;
}
#endif
