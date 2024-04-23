#define XPAINT
#include "xpaint.h"

int main(){
    int largura = 600, altura = 500;
    /* cria um bitmap de 600x500 que irá salvar como figura_base.png*/
    open(largura, altura, "figura_base"); 
    /* escreve usando a font default na posicao x=50, y=30 */
    /* utilizando o mesmo formato do printf */
    stroke(WHITE);
    text(50, 30, "Pintarei um circulo vermelho em %d %d", largura/2, altura/2);
    /* muda a cor do preenchimento para vermelho */
    /* muda a cor de fundo para amarelo */
    fill(RED);
    /* muda a espessura do pincel para 5 */
    strokeWeight(5);
    /* desenha um circulo preenchido com centro no meio da tela e raio 200 */
    circle(largura/2, altura/2, 200);
    /* salva no arquivo exemplo.png */
    save();
    /* libera os recursos alocados */
    close();
    return 0;
}
