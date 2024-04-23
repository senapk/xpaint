#include "../src/all.h"

int main(){
    open(1000, 600, "zz_balls");
    textSize(20);
    stroke(WHITE);
    for(int i = 0; i < 26; i++){
        fill(color("%c", 'a' + i));
        int x = xrand(0, 1000);
        int y = xrand(0, 600);
        circle(x, y, xrand(30, 60));
        text(x, y, "%c", 'a' + i);
    }
    for(int i = 0; i < 26; i++){
        fill(color("%c", 'A' + i));
        int x = xrand(0, 1000);
        int y = xrand(0, 600);
        circle(x, y, xrand(30, 60));
        text(x, y, "%c", 'A' + i);
    }

    save();
    close();
    return 0;
}

