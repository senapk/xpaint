#include "../src/all.h"

int main() {
    open(1200, 600, "zz_texto"); //init_asc_map();
    //show_asc_map();
    //char texto[256];
    //for(int i = ' '; i <= '~'; i++)
    //    texto[i - ' '] = (char) i;
    //texto['~' - ' ' + 1] = '\0';

    stroke(WHITE);
    //x_write(10, 10, texto);

    stroke(RED);
    textSize(40);
    text(10, 50, "abcdefghijklmnopqrstuvwxyz");
    text(10, 100, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    text(10, 250, "ãõÃÕçÇáéíóúÁÉÍÓÚàèìòùÀÈÌÒÙâêîôûÂÊÎÔÛ");

    text(10, 140, "Jesus, queremos te ver, o teu rosto brilhará em nós");
    save();
    close();
    return 0;
}
