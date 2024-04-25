#define XPAINT
#include "xpaint.h"
#include <stdlib.h>

int main() {
    open(600, 600, "figura_insertion");
    int size = 40;
    int max = 100;
    int vet[size];
    srand(3);
    for (int i = 0; i < size; i++) {
        vet[i] = xrand(max);
    }
    barInit(size, max);
    //mostra o 1 de red
    //o 5 de green
    //o 9 de blue
    //gera e salvar a imagem
    barDrawAll(vet, size, "rgb", 0, 2, 9);
    save();
    close();
    return 0;
}