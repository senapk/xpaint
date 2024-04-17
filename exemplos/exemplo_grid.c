#define XPAINT
#include "xpaint.h"

void xgrid_matrix(int nl, int nc, char mat[nl][nc]){
    x_color_load('w');
    x_clear();
    char * colors = "rgbymcov";
    int l, c;
    for(l = 0; l < nl; l++)
        for(c = 0; c < nc; c++){
            x_color_load(mat[l][c]);
            x_grid_square(l, c);
            x_color_load(colors[(c + l) % strlen(colors)]);
            x_grid_circle(l, c);
            x_color_load('k');
            if(rand() % 2 == 0)
                x_grid_write(l, c, "%d", rand() % 500 - 250);
            else{
                char str[] = "abcdef";
                str[rand() % 5 + 1] = '\0';
                x_write_set_size(30);
                x_grid_write(l, c, str);
            }
        }
}

int main(){
    int w = 902, h = 602, side = 100;
    x_open(w, h, "figura_grid");
    x_grid_init(side, 2);
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
    x_save();
    x_close();
    return 0;
}