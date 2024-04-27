#include "xpaint.h"

int main() {
    open(100, 100, "imagem");
    background("black");
    stroke("blue");
    fill("yellow");
    save();
    close();
    return 0;
}