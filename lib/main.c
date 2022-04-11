//#define XPAINT
//#define XPPM
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "base.h"
#include "draw.h"
#include "text.h"
#include "modules.h"
#include "xmath.h"
#include "text.h"
#include <string.h>
#include <wchar.h>
void test1(){
    srand(time(NULL));
    x_open(1000, 600, "figura_draw");
    x_set_viewer("gthumb");
    x_color_set(x_color_make(0, 0, 0, 150));
    x_clear();
    x_color_load('g');

    x_fill_circle(200, 200, 300);
    x_color_set(WHITE);
    x_fill_arc(200, 200, 150, 50, 190, 100);

    x_pen_set_thick(30);
    x_pen_set_pos(150, 100);
    x_pen_set_angle(-20);
    for(int i = 0; i < 5; i++){
        x_pen_walk(500);
        x_color_set(x_color_make(rand() % 256, rand() % 256, rand() % 256, 255));
        x_pen_rotate(-144);
    }
    x_save();
    x_close();
}

void many_balls(){
    x_open(1000, 600, "figura_draw");
    x_set_viewer("gthumb");

    for(int i = 0; i < 26; i++){
        x_color_load('a' + i);
        x_fill_circle(x_math_rand(0, 1000), x_math_rand(0, 600), x_math_rand(30, 60));
    }
    for(int i = 0; i < 26; i++){
        x_color_load('A' + i);
        x_fill_circle(x_math_rand(0, 1000), x_math_rand(0, 600), x_math_rand(30, 60));
    }

    x_save();
    x_close();
}

void test_texto(){
    x_open(1200, 600, "test");
    x_set_viewer("gthumb");
    //init_asc_map();
    //show_asc_map();
    char texto[256];
    for(int i = ' '; i <= '~'; i++)
        texto[i - ' '] = (char) i;
    texto['~' - ' ' + 1] = '\0';

    x_color_set(WHITE);
    x_write(10, 10, texto);

    x_color_set(RED);
    x_write_set_size(30);
    x_write(10, 50, "Aabcdefghijklmnopqrstuvwxyz");
    x_write(10, 100, "aeioubcdpgqyjmnwx");
    x_write(10, 250, "ãõÃÕçÇáéíóúÁÉÍÓÚàèìòùÀÈÌÒÙâêîôûÂÊÎÔÛ");

    //x_write(10, 70, "Jesus, queremos te ver, o teu rosto brilhara em nós");
    x_save();
    x_close();
}


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct{
    int x;
    int y;
    float v;
} Gota;

void draw_gota(int x, int y, int size){
    x_color_load('w');
    x_fill_circle(x, y, size);
    x_color_load('b');
    x_fill_circle(x, y, size - 1);
}

void gotas(){
    x_open(500, 500, "img");
    x_set_viewer("gthumb");
    int ngotas = 30;
    Gota gotas[ngotas];
    for(int i = 0; i < ngotas; i++){
        gotas[i].x = rand() % 500;
        gotas[i].y = rand() % 500;
        gotas[i].v = 0;
    }

    int qtd = 2000;
    while(qtd--){
        x_color_set(BLACK);
        x_clear();

        for(int i = 0; i < ngotas; i++){
            gotas[i].v += 1;
            gotas[i].x += 2;
            gotas[i].y += gotas[i].v;
            if(gotas[i].y > 500){
                gotas[i].y = 0;
                gotas[i].v = 3;
            }
            if(gotas[i].x > 500)
                gotas[i].x = 0;
            draw_gota(gotas[i].x, gotas[i].y, 10);
        }
        x_log("img");
    }
    x_save();
    //x_video_make("img", 20);
    x_close();
}

int main2(){
    test_texto();
}

