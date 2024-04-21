#include "../src/all.h"

int main(){
    open(1000, 600, "zz_balls");

    for(int i = 0; i < 26; i++){
        stroke_char('a' + i);
        stroke_rgba(math_rand(0, 256), math_rand(0, 256), math_rand(0, 256), 255);
        fill_circle(math_rand(0, 1000), math_rand(0, 600), math_rand(30, 60));
    }
    for(int i = 0; i < 26; i++){
        stroke_char('A' + i);
        fill_circle(math_rand(0, 1000), math_rand(0, 600), math_rand(30, 60));
    }

    save();
    close();
    return 0;
}

