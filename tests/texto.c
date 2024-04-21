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
    x_set_font_size(30);
    x_write(10, 50, "Aabcdefghijklmnopqrstuvwxyz");
    x_write(10, 100, "aeioubcdpgqyjmnwx");
    x_write(10, 250, "ãõÃÕçÇáéíóúÁÉÍÓÚàèìòùÀÈÌÒÙâêîôûÂÊÎÔÛ");

    x_write(10, 70, "Jesus, queremos te ver, o teu rosto brilhara em nós");
    save();
    close();
    return 0;
}
