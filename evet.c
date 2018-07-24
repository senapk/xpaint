#include <stdio.h>

#if 1
#include "ximage.h"
#include "xdraw.h"
#include "xvet.h"
#include "stdlib.h"
#else
#define   X_FULL
#include "xdraw.h"
#endif


#define SWAP(x, y) do {x = x ^ y; y = y ^ x; x = x ^ y;} while(0)
int main() {

    x_init(600, 600);
    int vet[34];
    int size = sizeof(vet)/sizeof(int);
    int i, j;

    for(i = 0; i < size; i++)
        vet[i] = rand() % 500;
    {
        int indices[] = {0, 2, 4, size - 1};
        xc_vet_show(vet, size, indices, "rgbv");
    }

    //selection sort
    for(i = 1; i < size; i++){
        for(j = i; j > 0; j--){
            if(vet[j] < vet[j - 1])
                SWAP(vet[j], vet[j - 1]);
            else
                break;
        }
    }
    {
        x_clear(BLACK);
        xc_vet_show(vet, size, NULL, "");
        x_save("vet.png");
        getchar();
        //printf("%d, ", cont++);
    }
    x_close();


    return 0;
}


