#include <stdio.h>
#define XPAINT
#include "../xpaint.h"

void insertion(int * vet, int size){
    int i;
    for(i = 1; i < size; i++){
        x_bar_save(vet, size, "y", i);
        int j;
        for(j = i - 1; j >= 0; j--){
            if(vet[j] > vet[j + 1]){
                X_SWAP(vet[j], vet[j + 1], int);
                x_bar_save(vet, size, "yg", i, j);
            }else
                break;
        }
    }
}

void verify(int * vet, int size){
    int i = 0;
    for(i = 0;i < size - 1; i++){  
        if(vet[i] <= vet[i + 1]){
            x_bar_save(vet, size, "gg", i, i + 1);
        }else{
            x_bar_save(vet, size, "rr", i, i + 1);
            break;
        }
    }
}

int main() {

    x_open(600, 300, "figura_insertion");
    x_set_viewer("code");
    x_set_lock();
    x_set_log("imgs");
    int size = 30, max = 900;
    x_bar_init(size, max);
    srand(2); 

    int vet[size];
    int i;
    for(i = 0; i < size; i++)
        vet[i] = rand() % max + 1; 

    insertion(vet, size);
    x_save();
    verify(vet, size);
    x_bar_save(vet, size, NULL);
    x_make_video(3);
    x_close();

    return 0;
 }

