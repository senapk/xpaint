#include <stdio.h>
#define XPAINT
#include "xpaint.h"

void insertion(int * vet, int size){
    int i;
    for(i = 1; i < size; i++){
        barSave(vet, size, "y", i);
        int j;
        for(j = i - 1; j >= 0; j--){
            if(vet[j] > vet[j + 1]){
                X_SWAP(vet[j], vet[j + 1], int);
                barSave(vet, size, "yg", i, j);
            }else
                break;
        }
    }
}

void verify(int * vet, int size){
    int i = 0;
    for(i = 0;i < size - 1; i++){  
        if(vet[i] <= vet[i + 1]){
            barSave(vet, size, "gg", i, i + 1);
        }else{
            barSave(vet, size, "rr", i, i + 1);
            break;
        }
    }
}

int main() {

    open(600, 300, "figura_insertion");
    set_viewer("code");
    setLock();
    setLog("imgs");
    int size = 30, max = 900;
    barInit(size, max);
    srand(2); 

    int vet[size];
    int i;
    for(i = 0; i < size; i++)
        vet[i] = rand() % max + 1; 

    insertion(vet, size);
    save();
    verify(vet, size);
    barSave(vet, size, NULL);
    makeVideo(3);
    close();

    return 0;
 }

