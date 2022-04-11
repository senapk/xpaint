#define XPAINT
#include "../xpaint.h"

int main() {
    x_open(700, 500, "figura_texto");
    //x_set_viewer("gthumb");
    x_set_font_size(20);
    x_set_color(WHITE);
    x_write(130, 30, "texto.png - Escrevendo em imagens");

    x_set_color(MAGENTA);
    x_write(10, 70, "Use o comando x_write(x, y, format, ...) para escrever.\nEle utiliza a mesma sintaxe do printf.");
   
    x_set_color(YELLOW);
    x_write(300, 150, "Você pode usar\\n para\nforçar a quebra de linha\ndentro do bloco.");

    x_set_color(CYAN);
    x_write(10, 200, "int qtd = 10;\nfloat preco = 5.4;\nchar * tipo = \"Kg\";");    
    x_set_color(GREEN);
    x_write(10, 270, "x_write(x, y, \"Comprei %%d uvas a %%.2f o %%s\", qtd, preco, tipo);");

    x_set_color(VIOLET);
    int qtd = 10;
    float preco = 5.4;
    char * tipo = "Kg";
    x_write(10, 300, "Comprei %d uvas a %.2f o %s", qtd, preco, tipo);

    x_set_color(MAGENTA);
    x_set_font_size(50);
    x_write(10, 350, "x_set_font_size(40);");

    x_save();
    x_close();
    return 0;
}


