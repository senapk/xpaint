#define XPAINT
#include "xpaint.h"

int main(){
    open(600, 400, "main"); // cria uma tela de 600x400 com o nome main.png
    background("0, 0, 0"); // limpa a tela com a cor preta usando rgb
    stroke("white"); // muda a cor do pincel para branco usando nome da cor
    textSize(20); // tamanho da fonte
    // escreve usando a sintaxe do printf
    text(50, 30, "Pintarei um circulo vermelho em %d %d", width() / 2, height()/ 2);
    fill("red"); // muda a cor de preenchimento para vermelho
    strokeWeight(5); // muda a espessura do pincel para 5
    circle(width()/2, height()/2, 200); // desenha um circulo no centro da tela com largura 200
    save(); // salva a imagem
    close(); // libera recursos alocados
    return 0;
}
