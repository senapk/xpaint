#include "../src/all.h"



int main(){
    open(1200, 1200, "zz_roda");
    stroke_char('w');
    fill_char('w');
    background(BLACK);
    strokeWeight(5);
    bezier(0, 0, 0, 1200, 1200, 0, 1200, 1200);
    
    save();
    close();
    return 0;
}