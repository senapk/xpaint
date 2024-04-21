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
    stroke_char('w');
    fill_circle(x, y, size);
    stroke_char('b');
    fill_circle(x, y, size - 1);
}

int main(){
    open(500, 500, "zz_gotas");
    int ngotas = 30;
    Gota gotas[ngotas];
    for(int i = 0; i < ngotas; i++){
        gotas[i].x = rand() % 500;
        gotas[i].y = rand() % 500;
        gotas[i].v = 0;
    }

    int qtd = 100;
    while(qtd--){
        stroke(BLACK);
        //background();

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
    save();
    //x_video_make("img", 20);
    close();
    return 0;
}

