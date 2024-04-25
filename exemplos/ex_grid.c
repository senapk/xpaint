#define XPAINT
#include "xpaint.h"


void xgrid_matrix(int nl, int nc, char mat[nl][nc]){
    stroke("w");
    background("black");
    char * colors = "rgbymcov";
    int l, c;
    textSize(30);
    for(l = 0; l < nl; l++)
        for(c = 0; c < nc; c++){
            stroke("%c", mat[l][c]);
            gridSquare(l, c);
            fill("%c", colors[(c + l) % strlen(colors)]);
            gridCircle(l, c);
            stroke("k");
            if(rand() % 2 == 0)
                gridText(l, c, "%d", rand() % 500 - 250);
            else{
                char str[] = "abcdef";
                str[rand() % 5 + 1] = '\0';
                gridText(l, c, str);
            }
        }
}

int main(){
    int w = 902, h = 602, side = 100;
    open(w, h, "figura_grid");
    gridInit(side, 2);
    int nl = h / side, nc = w / side;
    char mat[nl][nc];
    char * colors = "rgbymcov";
    int l, c;
    for(l = 0; l < nl; l++){
        for(c = 0; c < nc; c++){
            mat[l][c] = colors[xrand(strlen(colors))];
        }
    }
    xgrid_matrix(nl, nc, mat);
    save();
    close();
    return 0;
}