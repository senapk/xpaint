#define XPAINT
#include "xpaint.h"

int main() {
    open(700, 500, "figura_texto");
    textSize(20);
    stroke(WHITE);
    text(130, 30, "texto.png - Escrevendo em imagens");

    stroke(MAGENTA);
    text(10, 70, "Use o comando text(x, y, format, ...) para escrever.\nEle utiliza a mesma sintaxe do printf.");
   
    stroke(YELLOW);
    text(300, 150, "Você pode usar\\n para\nforçar a quebra de linha\ndentro do bloco.");

    stroke(CYAN);
    text(10, 200, "int qtd = 10;\nfloat preco = 5.4;\nchar * tipo = \"Kg\";");    
    stroke(GREEN);
    text(10, 270, "text(x, y, \"Comprei %%d uvas a %%.2f o %%s\", qtd, preco, tipo);");

    stroke(VIOLET);
    int qtd = 10;
    float preco = 5.4;
    char * tipo = "Kg";
    text(10, 300, "Comprei %d uvas a %.2f o %s", qtd, preco, tipo);

    stroke(MAGENTA);
    textSize(50);
    text(10, 350, "textSize(40);");

    save();
    close();
    return 0;
}


