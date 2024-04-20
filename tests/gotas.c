#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../src/all.h"
#include <string.h>
#include <wchar.h>


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
    }
    x_save();
    //x_video_make("img", 20);
    x_close();
}

int main(){
    gotas();
    return 0;
}

