#ifndef TEXT_H /*XDDDX*/
#define TEXT_H /*XDDDX*/

#include <stdarg.h>

// ---------------------------- TEXTO -----------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

// muda o tamanho da font
// OBS: a font só muda em múltiplos de 8, ex: 8, 16, 24, ...
void textSize(int size);

// escreve utilizando o formato printf
// retorna a posicao final em x
// pode utilizar \n para quebra de linha
int text(int x, int y, const char * format, ...);

// ---------------------------- FUNÇÕES INTERNAS ------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

//inicializa o módulo de escrita
void __x_init_font();

#endif /*XDDDX*/
