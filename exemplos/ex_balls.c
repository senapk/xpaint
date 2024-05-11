#define XPAINT
#include "xpaint.h"
#include <stdlib.h> //srand
#include <stdbool.h>

const int raio = 30;

bool collide(int x, int y, V2d balls[], int balls_size) {
    for (int i = 0; i < balls_size; i++) {
        if (dist(x, y, balls[i].x, balls[i].y) < 2 * raio) {
            return true;
        }
    }
    return false;
}

int main(){
    create(500, 300, "figura_balls");
    textSize(24);
    srand(0);
    stroke("black");
    V2d balls[26]; //guarda as bolas
    int balls_size = 0;

    for(int i = 0; i < 26; i++){
        fill("%d,%d,%d", xrandi(150, 256), xrandi(150, 256), xrandi(150, 256));
        while (true) {
            int x = xrandi(raio, width() - raio); //dentro da tela
            int y = xrandi(raio, height() - raio);//dentro da tela
            if (!collide(x, y, balls, balls_size)) {
                balls[balls_size++] = v2d(x, y);
                circle(x, y, 2 * raio);
                text(x - 10, y - 10, "%c", 'A' + i);
                break;
            }
        }
    }
    save();
    destroy();
    return 0;
}