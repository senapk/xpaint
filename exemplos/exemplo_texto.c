#define XPAINT_FULL
#include "../xpaint.h"

int main() {
    x_open(600, 500, "figura_texto");
    x_set_font_size(18);
    x_set_color(X_COLOR_WHITE);
    x_write(130, 30, "texto.png - Escrevendo em imagens");

    x_set_color(X_COLOR_MAGENTA);
    x_write(10, 70, "Use o comando x_write(x, y, format, ...) para escrever. Ele uti- liza a mesma sintaxe do printf. Se seu texto passar da margem,   ele automaticamente vai quebrar a linha.");
   
    x_set_color(X_COLOR_YELLOW);
    x_write(300, 150, "Voce pode usar\\n para\nforcar a quebra de linha\ndentro do bloco.");

    x_set_color(X_COLOR_CYAN);
    x_write(10, 200, "int qtd = 10;\nfloat preco = 5.4;\nchar * tipo = \"Kg\";");    
    x_set_color(X_COLOR_GREEN);
    x_write(10, 270, "x_write(x, y, \"Comprei %%d uvas a %%.2f o %%s\", qtd, preco, tipo);");

    x_set_color(X_COLOR_VIOLET);
    int qtd = 10;
    float preco = 5.4;
    char * tipo = "Kg";
    x_write(10, 300, "Comprei %d uvas a %.2f o %s", qtd, preco, tipo);

    x_set_color(X_COLOR_MAGENTA);
    x_set_font_size(40);
    x_write(10, 350, "x_set_font_size(40);");

/*     x_set_pcolor('b');
    x_set_font_size(18);
    x_write(10, 400, "x_set_font(\"filename.ttf\") para trocar de fonte");
    x_set_font("script12.ttf");
    x_set_font_size(25);
    x_set_pcolor('m');
    x_write(10, 420, "E entao o texto fica assim!");
    
    x_set_pcolor('r');
    x_set_font(NULL);
    x_write(10, 450, "x_set_font(NULL) para voltar a font default");
 */    
    x_save();
    x_close();
    return 0;
}


