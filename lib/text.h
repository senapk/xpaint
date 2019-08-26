#ifndef TEXT_H
#define TEXT_H


void x_font_init();
void x_set_font_size(int size);
int x_write(int x, int y, const char * format, ...);

#endif