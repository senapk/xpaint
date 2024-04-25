#include <stdio.h>
#define XPAINT
#include "xpaint.h"

void insertion(int * vet, int size) {
    int i;
    for(i = 1; i < size; i++){
        barDrawAll(vet, size, "y", i);
        save();
        int j;
        for(j = i - 1; j >= 0; j--) {
            if(vet[j] > vet[j + 1]) {
                X_SWAP(vet[j], vet[j + 1], int);
                barDrawAll(vet, size, "yg", i, j);
                save();
            } else {
                break;
            }
        }
    }
}

void verify(int * vet, int size){
    int i = 0;
    for(i = 0;i < size - 1; i++){  
        if(vet[i] <= vet[i + 1]){
            barDrawAll(vet, size, "gg", i, i + 1);
            save();
        }else{
            barDrawAll(vet, size, "rr", i, i + 1);
            save();
            break;
        }
    }
}

int main() {

    open(600, 300, "figura_insertion");
    // setLock();
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
    barDrawAll(vet, size, NULL);
    save();
    makeVideo(5, "video_insertion");
    close();

    return 0;
 }

