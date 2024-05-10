#define XPAINT
#include "xpaint.h"
#include <stdio.h>

void draw(int inf, int sup) {
  background("blue");
  stroke("white");
  textSize(20); // tamanho da fonte
  text(50, 70, "Digite um valor entre ]%d e %d[", inf, sup);
  for (int i = 0; i < 101; i++) {
    int size = 10;
    int x = i * 7 + 20;
    int y = 100;
    if (i == inf || i == sup) {
      size = 30;
      if (i == inf)
        text(x - 20, y + 30, "%d", i);
      else
        text(x + 10, y + 30, "%d", i);
    }
    line(x, y, x, y + size);
  }
  save(); // salva a imagem
}

int main() {
  puts("Abra a tela.png para começar a jogar");
  xopen(800, 250, "tela");
  strokeWeight(2);
  int escolha = xrandi(1, 101);
  int inf = 0;
  int sup = 100;
  int chute;
  while (1) {
    draw(inf, sup);
    printf("input: ");
    if (scanf("%d", &chute)) {
    }
    if (chute > escolha) {
      sup = chute;
    } else if (chute < escolha) {
      inf = chute;
    } else if (chute == escolha) {
      puts("voce acertou");
      textSize(30);
      stroke("red");
      text(30, 240, "VOCÊ ACERTOU, PARABÉNS");
      save();
      break;
    }
  }
  xclose(); // libera recursos alocados
  return 0;
}
