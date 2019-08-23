#include <stdio.h>
#define XPAINT_FULL
#include "../xpaint.h"

#define vet_show(vet, size, colors, ...) do{\
    int __indices[] = {__VA_ARGS__};\
    x_bar_all(vet, size, colors, __indices);\
    if(x_control())\
        x_save();\
}while(0);

void insertion(int * vet, int size){
    int i;
    for(i = 1; i < size; i++){
        vet_show(vet, size, "y", i);
        int j;
        for(j = i - 1; j >= 0; j--){
            if(vet[j] > vet[j + 1]){
                X_SWAP(vet[j], vet[j + 1], int);
                vet_show(vet, size, "yg", i, j);
            }else
                break;
        }
    }
}

void verify(int * vet, int size){
    int i = 0;
    for(i = 0;i < size - 1; i++){  
        if(vet[i] <= vet[i + 1]){
            vet_show(vet, size, "gg", i, i + 1);
        }else{
            vet_show(vet, size, "rr", i, i + 1);
            break;
        }
    }
}

int main() {

    x_open(600, 300, "figura_insertion");
    
    int size = 30, max = 900;
    x_bar_init(size, max);
    srand(2); 

    int vet[size];
    int i;
    for(i = 0; i < size; i++)
        vet[i] = rand() % max + 1; 

    insertion(vet, size);
    x_set_step(1);
    x_save();
    verify(vet, size);
    vet_show(vet, size, NULL);
    x_close();

    return 0;
 }

