#define XPAINT_FULL
#include "xpaint.h"

void xgrid_matrix(int nl, int nc, char mat[nl][nc]){
    x_clear(xg_palette('w'));
    char * colors = "rgbymcov";
    int l, c;
    for(l = 0; l < nl; l++)
        for(c = 0; c < nc; c++){
            xs_color(xg_palette(mat[l][c]));
            xgrid_splot(l, c);
            xs_color(xg_palette(colors[(c + l) % strlen(colors)]));
            xgrid_cplot(l, c);
            xs_color(BLACK);
            if(rand() % 2 == 0)
                xgrid_nplot(l, c, rand() % 500 - 250);
            else{
                char str[] = "abcdef";
                str[rand() % 5 + 1] = '\0';
                xgrid_tplot(l, c, str);
            }
        }
}

int main(){
    int w = 902, h = 602, side = 100;
    x_open(w, h);
    xgrid_init(side, 2);
    int nl = h / side, nc = w / side;
    char mat[nl][nc];
    char * colors = "rgbymcov";
    int l, c;
    for(l = 0; l < nl; l++){
        for(c = 0; c < nc; c++){
            mat[l][c] = colors[rand() % strlen(colors)];
        }
    }
    xgrid_matrix(nl, nc, mat);
    x_save("figura_grid");
    x_close();
    return 0;
}