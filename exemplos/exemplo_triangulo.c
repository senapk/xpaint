#define XPAINT
#include "xpaint.h"

void fractal(float x, float y, float lado, float ang){
    if(lado < 5)
        return;
    int i;
    for(i = 0; i < 3; i++){
        fractal(x, y, lado / 2, ang);
        
        float x0 = x, y0 = y; /* salva x e y */
        x += lado * math_cos(ang); /* translada x e y */
        y -= lado * math_sin(ang);
        draw_line(x0, y0, x, y); /* desenha a linha */
        
        ang -= 120;
    }
}
int main(){
    open(800, 700, "figura_triangulo");
    set_font_size(30);
    write(140, 0, "Exemplo do fractal de Sierpinski");
    fractal(50, 650, 700, 60);
    save();
    close();
    return 0;
}

