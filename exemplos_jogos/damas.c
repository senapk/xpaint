
#include "xpaint.h"
#include <stdio.h>

int larguraTotal = 650, alturaTotal = 650;
int largura = 600, altura = 600;
int qntCasas = 8;
int qntCadaTime = 12;
int qntViva = 12 * 2;
/*
Atividade 5 - Xadrez
Você e um amigo são viciados em CHESS.COM a 5 anos, um dia o site do jogo acabou
caindo. Como jovens do século XXI vocês não tem xadrez em casa, então para
compensar resolveram criar uma versão de xadrez no computador.

Nessa atividade você tem que gerar uma imagem xadrez
A imagem deve ter 8x8 casas conforme o exemplo
*/
typedef struct {
  int team;
  int x;
  int y;
} Peca;
typedef struct {
  int x;
  int y;
  int xVitima;
  int yVitima;
} Position;
// Color rgba(206, 171, 55, 255);
// Color rgba(49, 12, 3, 255);
// Color rgba(237, 216, 147, 255);
// Color rgba(38, 32, 28, 255);

void gerarMapa(Peca pecas[]) {
  // int qntCasas = 8;

  for (int x = 0; x < qntCasas; x++) {
    for (int y = 0; y < qntCasas; y++) {
      if ((x % 2 == 0 && y % 2 == 0) || (x % 2 != 0 && y % 2 != 0)) {
        setFill(rgba(209, 185, 107, 255));
      } else {
        setFill(rgba(97, 66, 48, 255));
      }

      rect(x * ((float)largura / qntCasas), y * ((float)altura / qntCasas),
           ((float)largura / qntCasas), ((float)altura / qntCasas));
    }
  }
  for (int i = 0; i < qntViva; i++) {
    if (pecas[i].team == 1) {
      setFill(rgba(242, 229, 184, 255));
    } else {
      setFill(rgba(51, 33, 20, 255));
    }
    circle(pecas[i].x * ((float)largura / qntCasas) +
               ((float)largura / qntCasas) / 2,
           pecas[i].y * ((float)altura / qntCasas) +
               ((float)largura / qntCasas) / 2,
           60);
  }
}

int getIndexByPosition(Peca pecas[], int x, int y) {
  for (int i = 0; i < qntViva; i++) {
    if (pecas[i].x == x && pecas[i].y == y) {
      return i;
    }
  }
  return -1;
}

void gerarJogadas(Peca pecas[], int indexEscolhido, Position jogadas[]) {
  Peca p = pecas[indexEscolhido];
  Position j1;
  j1.x = p.x - 1;
  j1.y = p.y - 1;
  j1.xVitima = -1;
  Position j2;
  j2.x = p.x - 1;
  j2.y = p.y + 1;
  j2.xVitima = -1;
  Position j3;
  j3.x = p.x + 1;
  j3.y = p.y + 1;
  j3.xVitima = -1;
  Position j4;
  j4.x = p.x + 1;
  j4.y = p.y - 1;
  j4.xVitima = -1;

  jogadas[0] = j1;
  jogadas[1] = j2;
  jogadas[2] = j3;
  jogadas[3] = j4;
  fill("green");
  if (pecas[indexEscolhido].team == 1) {
    if (j1.x >= 0 && j1.x < qntCasas && j1.y >= 0 && j1.y < qntCasas) {
      if (getIndexByPosition(pecas, j1.x, j1.y) == -1) {
        circle(j1.x * ((float)largura / qntCasas) +
                   ((float)largura / qntCasas) / 2,
               j1.y * ((float)altura / qntCasas) +
                   ((float)largura / qntCasas) / 2,
               60);
      } else if (pecas[getIndexByPosition(pecas, j1.x, j1.y)].team !=
                 pecas[indexEscolhido].team) {
        if (getIndexByPosition(pecas, j1.x - 1, j1.y - 1) == -1) {
          jogadas[0].x -= 1;
          jogadas[0].y -= 1;
          jogadas[0].xVitima = j1.x;
          jogadas[0].yVitima = j1.y;
          circle(jogadas[0].x * ((float)largura / qntCasas) +
                     ((float)largura / qntCasas) / 2,
                 jogadas[0].y * ((float)altura / qntCasas) +
                     ((float)largura / qntCasas) / 2,
                 60);
        }
      }
    }
    if (j4.x >= 0 && j4.x < qntCasas && j4.y >= 0 && j4.y < qntCasas) {
      if (getIndexByPosition(pecas, j4.x, j4.y) == -1) {
        circle(j4.x * ((float)largura / qntCasas) +
                   ((float)largura / qntCasas) / 2,
               j4.y * ((float)altura / qntCasas) +
                   ((float)largura / qntCasas) / 2,
               60);
      } else if (pecas[getIndexByPosition(pecas, j4.x, j4.y)].team !=
                 pecas[indexEscolhido].team) {

        if (getIndexByPosition(pecas, j4.x + 1, j4.y - 1) == -1) {
          jogadas[3].x += 1;
          jogadas[3].y -= 1;
          jogadas[3].xVitima = j4.x;
          jogadas[3].yVitima = j4.y;
          circle(jogadas[3].x * ((float)largura / qntCasas) +
                     ((float)largura / qntCasas) / 2,
                 jogadas[3].y * ((float)altura / qntCasas) +
                     ((float)largura / qntCasas) / 2,
                 60);
        }
      }
    }
  } else {
    if (j2.x >= 0 && j2.x < qntCasas && j2.y >= 0 && j2.y < qntCasas) {
      if (getIndexByPosition(pecas, j2.x, j2.y) == -1) {
        circle(j2.x * ((float)largura / qntCasas) +
                   ((float)largura / qntCasas) / 2,
               j2.y * ((float)altura / qntCasas) +
                   ((float)largura / qntCasas) / 2,
               60);
      } else if (pecas[getIndexByPosition(pecas, j2.x, j2.y)].team !=
                 pecas[indexEscolhido].team) {
        if (getIndexByPosition(pecas, j2.x - 1, j2.y + 1) == -1) {
          jogadas[1].x -= 1;
          jogadas[1].y += 1;
          jogadas[1].xVitima = j2.x;
          jogadas[1].yVitima = j2.y;
          circle(jogadas[1].x * ((float)largura / qntCasas) +
                     ((float)largura / qntCasas) / 2,
                 jogadas[1].y * ((float)altura / qntCasas) +
                     ((float)largura / qntCasas) / 2,
                 60);
        }
      }
    }
    if (j3.x >= 0 && j3.x < qntCasas && j3.y >= 0 && j3.y < qntCasas) {
      if (getIndexByPosition(pecas, j3.x, j3.y) == -1) {
        circle(j3.x * ((float)largura / qntCasas) +
                   ((float)largura / qntCasas) / 2,
               j3.y * ((float)altura / qntCasas) +
                   ((float)largura / qntCasas) / 2,
               60);
      } else if (pecas[getIndexByPosition(pecas, j3.x, j3.y)].team !=
                 pecas[indexEscolhido].team) {
        if (getIndexByPosition(pecas, j3.x + 1, j3.y + 1) == -1) {
          jogadas[2].x += 1;
          jogadas[2].y += 1;
          jogadas[2].xVitima = j3.x;
          jogadas[2].yVitima = j3.y;
          circle(jogadas[2].x * ((float)largura / qntCasas) +
                     ((float)largura / qntCasas) / 2,
                 jogadas[2].y * ((float)altura / qntCasas) +
                     ((float)largura / qntCasas) / 2,
                 60);
        }
      }
    }
  }
}

void deletePeca(Peca pecas[], int pos) {
  for (int i = pos; i < qntViva - 1; i++) {
    pecas[i] = pecas[i + 1];
  }
  qntViva--;
}

void gerarMarcacoes() {
  int tamanhoCelula = largura / qntCasas;
  stroke("black");
  textSize(20);
  for (int i = 0; i < qntCasas; i++) {
    text(tamanhoCelula * i + 35, 615, "%c", 'A' + i);
  }
  for (int i = 0; i < qntCasas; i++) {
    text(607, tamanhoCelula * i + 20, "%d", i);
  }

  for (int i = 0; i < qntCasas; i++) {
    for (int j = 0; j < qntCasas; i++) {
      stroke("red");
      text(tamanhoCelula * i, tamanhoCelula * j, "%c%d", 'a' + i, i);
    }
  }
}

int main() {
  open(larguraTotal, alturaTotal, "Damas");
  background("156, 121, 75");
  gerarMarcacoes();
  Peca pecas[qntViva];
  int vez = 1;
  for (int i = 0; i < qntCadaTime; i++) {
    Peca p;
    p.y = (i * 2) / qntCasas;
    if (p.y % 2 == 0) {
      p.x = (i * 2 + 1) % qntCasas;
    } else {
      p.x = (i * 2) % qntCasas;
    }
    p.team = 0;
    pecas[i] = p;
  }

  for (int i = 0; i < qntCadaTime; i++) {
    Peca p;
    p.y = qntCasas - 1 - (i * 2) / qntCasas;
    if (p.y % 2 == 0) {
      p.x = (i * 2 + 1) % qntCasas;
    } else {
      p.x = (i * 2) % qntCasas;
    }
    p.team = 1;
    pecas[i + qntCadaTime] = p;
  }

  printf("\n\n\n\n\nVai comecar o jogo de dama\n\n");
  gerarMapa(pecas);
  gerarMarcacoes();
  save();
  while (1) {
    if (vez == 1) {
      printf("Vez das pretas\n");
    } else {
      printf("Vez das brancas\n");
    }
    printf("Escolha a peca que quer mover: \n");
    int x = 0;
    int y = 0;
    printf("x = ");
    scanf("%d", &x);
    printf("y = ");
    scanf("%d", &y);
    int pecaEscolhida = getIndexByPosition(pecas, x, y);
    if (pecas[pecaEscolhida].team == vez - 1) {
      gerarMapa(pecas);
     gerarMarcacoes();

      Position jogadas[4];
      gerarJogadas(pecas, pecaEscolhida, jogadas);
      gerarMarcacoes();
      save();
      printf("Pra onde ira se mover? : \n");
      int beforeX = x;
      int beforeY = y;
      printf("x = ");
      scanf("%d", &x);
      printf("y = ");
      scanf("%d", &y);

      for (int i = 0; i < 4; i++) {
        if (x == jogadas[i].x && y == jogadas[i].y &&
            getIndexByPosition(pecas, x, y) == -1) {
          pecas[pecaEscolhida].x = x;
          pecas[pecaEscolhida].y = y;
          if (jogadas[i].xVitima != -1) {
            deletePeca(pecas, getIndexByPosition(pecas, jogadas[i].xVitima,
                                                 jogadas[i].yVitima));
          }
          break;
        }
      }
      gerarMapa(pecas);

        gerarMarcacoes();
      save();
      if (vez == 1 && (pecas[pecaEscolhida].x != beforeX ||
                       pecas[pecaEscolhida].y != beforeY)) {
        vez = 2;
      } else {
        vez = 1;
      }
      if (qntViva <= 1) {
        break;
      }
    } else {
      printf("jogada invalida\n");
    }
  }
  printf("Acabou o jogo\n");
  close();
  return 0;
}
