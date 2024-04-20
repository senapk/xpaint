#include "../src/all.h"

int main(){
    x_open(1000, 600, "zz_balls");

    for(int i = 0; i < 26; i++){
        x_color_load('a' + i);
        x_color_set(x_color_make(x_math_rand(0, 256), x_math_rand(0, 256), x_math_rand(0, 256), 255));
        x_fill_circle(x_math_rand(0, 1000), x_math_rand(0, 600), x_math_rand(30, 60));
    }
    for(int i = 0; i < 26; i++){
        x_color_load('A' + i);
        x_fill_circle(x_math_rand(0, 1000), x_math_rand(0, 600), x_math_rand(30, 60));
    }

    x_save();
    x_close();
    return 0;
}

