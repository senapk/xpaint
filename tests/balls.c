#include "../src/all.h"

int main(){
    open(1000, 600, "zz_balls");

    for(int i = 0; i < 26; i++){
        stroke_char('a' + i);
        stroke_rgba(x_math_rand(0, 256), x_math_rand(0, 256), x_math_rand(0, 256), 255);
        x_fill_circle(x_math_rand(0, 1000), x_math_rand(0, 600), x_math_rand(30, 60));
    }
    for(int i = 0; i < 26; i++){
        stroke_char('A' + i);
        x_fill_circle(x_math_rand(0, 1000), x_math_rand(0, 600), x_math_rand(30, 60));
    }

    save();
    close();
    return 0;
}

