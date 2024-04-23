#ifndef TEXT_H /*XDDDX*/
#define TEXT_H /*XDDDX*/

#include <stdarg.h>
//inicializa o módulo de escrita
void __x_init_font();

// muda o tamanho da font
void textSize(int size);

// escreve utilizando o formato printf
// retorna a posicao final em x
int text(int x, int y, const char * format, ...);
#endif /*XDDDX*/
