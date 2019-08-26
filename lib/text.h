#ifndef TEXT_H /*XDDDX*/
#define TEXT_H /*XDDDX*/

//inicializa o módulo de escrita
void __x_init_font();

// muda o tamanho da font
void x_set_font_size(int size);

// escreve utilizando o formato printf
int  x_write(int x, int y, const char * format, ...);

#endif /*XDDDX*/

