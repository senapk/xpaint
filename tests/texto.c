#include "xpaint.h"

int main() {
    open(1200, 400, "zz_texto"); //init_asc_map();
    stroke("white");

    stroke("white");
    textSize(40);
    text(10, 10, "!\"#$'()*+,-./0123456789:;<=>?@()[]{}");
    text(10, 50, "{[(Aabcdefghijklmnop<>qrstuvwxyzA)]}");
    text(10, 100, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    text(10, 140, "Jesus, queremos te ver, o teu rosto brilhará em nós!");
    text(10, 190, "if (a > b) {\n    printf(eh_maior);\n}");
    text(10, 320, "ãõÃÕçÇáéíóúÁÉÍÓÚàèìòùÀÈÌÒÙâêîôûÂÊÎÔÛ");
    textSize(10);
    text(400, 220, "Esse é um texto pequenininho");
    save();
    close();
    return 0;
}
