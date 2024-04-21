#define XPAINT
#include "xpaint.h"

int main() {
    open(700, 500, "figura_texto");
    set_font_size(20);
    stroke(WHITE);
    write(130, 30, "texto.png - Escrevendo em imagens");

    stroke(MAGENTA);
    write(10, 70, "Use o comando write(x, y, format, ...) para escrever.\nEle utiliza a mesma sintaxe do printf.");
   
    stroke(YELLOW);
    write(300, 150, "Você pode usar\\n para\nforçar a quebra de linha\ndentro do bloco.");

    stroke(CYAN);
    write(10, 200, "int qtd = 10;\nfloat preco = 5.4;\nchar * tipo = \"Kg\";");    
    stroke(GREEN);
    write(10, 270, "write(x, y, \"Comprei %%d uvas a %%.2f o %%s\", qtd, preco, tipo);");

    stroke(VIOLET);
    int qtd = 10;
    float preco = 5.4;
    char * tipo = "Kg";
    write(10, 300, "Comprei %d uvas a %.2f o %s", qtd, preco, tipo);

    stroke(MAGENTA);
    set_font_size(50);
    write(10, 350, "x_write_set_size(40);");

    save();
    close();
    return 0;
}


