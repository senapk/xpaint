#include "../src/all.h"

int main() {
    x_open(1200, 600, "zz_texto"); //init_asc_map();
    //show_asc_map();
    //char texto[256];
    //for(int i = ' '; i <= '~'; i++)
    //    texto[i - ' '] = (char) i;
    //texto['~' - ' ' + 1] = '\0';

    x_color_set(WHITE);
    //x_write(10, 10, texto);

    x_color_set(RED);
    x_write_set_size(30);
    x_write(10, 50, "Aabcdefghijklmnopqrstuvwxyz");
    x_write(10, 100, "aeioubcdpgqyjmnwx");
    x_write(10, 250, "ãõÃÕçÇáéíóúÁÉÍÓÚàèìòùÀÈÌÒÙâêîôûÂÊÎÔÛ");

    //x_write(10, 70, "Jesus, queremos te ver, o teu rosto brilhara em nós");
    x_save();
    x_close();
    return 0;
}
