#include "xpaint.h"

int main(){
    int largura = 800, altura = 600;
    /* cria um bitmap de 800x600 */
    x_open(largura, altura); 
    /* escreve usando a font default na posicao x=50, y=30 */
    /* utilizando o mesmo formato do printf */
    x_write(50, 30, "Pintarei um circulo vermelho em %d %d", largura/2, altura/2);
    /* muda a cor do pincel para vermelho */
    xs_color(RED);
    /* desenha um circulo preenchido com centro no meio da tela e raio 200 */
    xd_filled_circle(largura/2, altura/2, 200);
    /* salva no arquivo exemplo.png */
    x_save("figura_base");
    /* libera os recursos alocados */
    x_close();
    return 0;
}