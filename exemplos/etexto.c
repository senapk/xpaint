#include <stdio.h>

#if 0
#include "libs/ximage.h"
#else
#define   X_FULL
#include "../xpaint.h"
#endif


int main() {
    //teste de cores
    x_open(600, 600);
    xs_font_size(18);
    xs_color(WHITE);
    x_write(130, 30, "texto.png - Escrevendo em imagens");

    xs_color(MAGENTA);
    x_write(10, 70, "Use o comando x_write(x, y, format, ...) para escrever. Ele uti- liza a mesma sintaxe do printf. Se seu texto passar da margem,   ele automaticamente vai quebrar a linha.");
   
    xs_color(YELLOW);
    x_write(300, 150, "Voce pode usar\\n para\nforcar a quebra de linha\ndentro do bloco.");

    xs_color(CYAN);
    x_write(10, 200, "int qtd = 10;\nfloat preco = 5.4;\nchar * tipo = \"Kg\";");    
    xs_color(GREEN);
    x_write(10, 270, "x_write(x, y, \"Comprei %%d uvas a %%.2f o %%s\", qtd, preco, tipo);");

    xs_color(VIOLET);
    int qtd = 10;
    float preco = 5.4;
    char * tipo = "Kg";
    x_write(10, 300, "Comprei %d uvas a %.2f o %s", qtd, preco, tipo);

    xs_color(MAGENTA);
    xs_font_size(40);
    x_write(10, 350, "xs_font_size(40);");

    xs_color(BLUE);
    xs_font_size(18);
    x_write(10, 400, "xs_font(\"filename.ttf\") para trocar de fonte");
    xs_font("script12.ttf");
    xs_font_size(25);
    xs_color(MAGENTA);
    x_write(10, 420, "E entao o texto fica assim!");
    
    xs_color(RED);
    xs_font(NULL);
    x_write(10, 450, "xs_font(NULL) para voltar a font default");
    x_save("figuras/etexto");
    x_close();
    return 0;
}


