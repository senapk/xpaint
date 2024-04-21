#define XPAINT
#include "xpaint.h"

int main(){
    int largura = 600, altura = 500;
    /* cria um bitmap de 600x500 que irá salvar como figura_base.png*/
    open(largura, altura, "figura_base"); 
    /* escreve usando a font default na posicao x=50, y=30 */
    /* utilizando o mesmo formato do printf */
    write(50, 30, "Pintarei um circulo vermelho em %d %d", largura/2, altura/2);
    /* muda a cor do pincel para vermelho */
    stroke(RED);
    /* desenha um circulo preenchido com centro no meio da tela e raio 200 */
    fill_circle(largura/2, altura/2, 200);
    /* salva no arquivo exemplo.png */
    save();
    /* libera os recursos alocados */
    close();
    return 0;
}