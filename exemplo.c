#define X_FULL
#include "xpaint.h"

int main(){
    int largura = 800, altura = 600;
    x_open(largura, altura);
    x_write(0, 30, "Pintarei um circulo vermelho em %d %d", largura/2, altura/2);
    xs_color(RED);
    xd_filled_circle(largura/2, altura/2, 200);
    x_save("exemplo");
    x_close();
    return 0;
}