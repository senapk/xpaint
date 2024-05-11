#define XPAINT
#include <stdbool.h>
#include "xpaint.h"
#include <unistd.h> //sleep
#include <stdio.h>
#include <time.h>

int main(){
    create(200, 200, "main");

    while (true) {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        int hora = tm.tm_hour;
        int minuto = tm.tm_min;
        int segundo = tm.tm_sec;
        background("black");
        fill("white");
        stroke("white");
        for (int i = 0; i < 12; i++) {
            arc(100, 100, 100, 90, 85 - i * (360/12), 10);
        }
        for (int i = 0; i < 12; i++) {
            int x = 95 + 30 * xcos(90 - i * (360/12));
            int y = 95 - 30 * xsin(90 - i * (360/12));
            text(x, y, "%d", i);
        }
        arc(100, 100, 60, 10, 90 - hora * (360/12) - (360/12) * (minuto/60.0), 10);
        arc(100, 100, 75, 10, 90 - minuto * (360/60), 5);
        arc(100, 100, 90, 10, 90 - segundo * (360/60), 2);
        save(); // salva a imagem
        sleep(1); // dorme por 1 segundo
    }
    destroy();
    return 0;
}
