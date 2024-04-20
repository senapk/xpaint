#include "color.h" /*XDDDX*/

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static X_Color __board_palette[256];

X_Color x_make_color(uchar r, uchar g, uchar b, uchar a){
    X_Color x = {r, g, b, a};
    return x;
}

void x_set_palette(char c, X_Color color){
    __board_palette[(int)c] = color;
}

X_Color x_get_palette(char c){
    return __board_palette[(int)c];
}

void __x_init_pallete(void){
    int i = 0;
    for(i = 0; i < 256; i++)
        __board_palette[i] = WHITE;

    __board_palette['r'] = RED;
    __board_palette['g'] = GREEN;
    __board_palette['b'] = BLUE;
    __board_palette['y'] = YELLOW;
    __board_palette['m'] = MAGENTA;
    __board_palette['c'] = CYAN;
    __board_palette['k'] = BLACK;
    __board_palette['w'] = WHITE;
    __board_palette['o'] = ORANGE;
    __board_palette['v'] = VIOLET;
}


//bool __x_validate_hex(const char * color){
//    for(int i = 1; i < 7; i++){
//        if(color[i] >= '0' && color[i] <= '9')
//            continue;
//        else if(color[i] >= 'a' && color[i] <= 'f')
//            continue;
//        else
//            return false;
//    }
//    return true;
//}

//bool __x_decode_hex(const char * _color, X_Color * xc){
//    if(strlen(_color) != 7 || _color[0] != '#')
//        return false;
//    char color[8];
//    strcpy(color, _color);
//    for(int i = 1; i < 7; i++)
//        color[i] = tolower(_color[i]);
//    if(!__x_validate_hex(color))
//        return false;
//    unsigned int r, g, b;
//    int readings = sscanf(color + 1, "%02x%02x%02x", &r, &g, &b);
//    if(readings != 3)
//        return false;
//    *xc = (X_Color){r, g, b, 255};
//    return true;
//}

//int __x_count_colon(const char * color){
//    int cont = 0;
//    int size = strlen(color);
//    for(int i = 0; i < size; i++)
//        if(color[i] == ',')
//            cont += 1;
//    return cont;
//}

//bool __x_decode_rgba(const char * color, X_Color * xc){
//    int number_of_colons = __x_count_colon(color);
//    if(number_of_colons != 2 && number_of_colons != 3)
//        return false;
//    char decode[4][4] = {"", "", "", ""};
//    int  idecode[4];
//    int ind = 0;
//    int size = strlen(color);
//    for(int i = 0; i < size; i++){
//        if(color[i] == ',')
//            ind += 1;
//        else if(color[i] == ' ')
//            continue;
//        else if((color[i] >= '0') && (color[i] <= '9')){
//            char str[2] = "x";
//            str[0] = color[i];
//            strcat(decode[ind], str);
//        }
//        else{
//            return false;
//        }
//    }
//    if(ind == 2)
//        strcpy(decode[3], "255");
//    for(int i = 0; i < 4; i++)
//        idecode[i] = atoi(decode[i]);
//    xc->r = idecode[0];
//    xc->g = idecode[1];
//    xc->b = idecode[2];
//    xc->a = idecode[3];
//    for(int i = 0; i < 4; i++){
//        if((idecode[i] < 0) || (idecode[i] > 255))
//            printf("warning: a rgb color should be inside the interval [0, 255]: %d\n", idecode[i]);
//    }
    
//    return true;
//}

//bool __x_color_load(const char * color, X_Color * xc){
//    if(strlen(color) == 1){
//        int pos = color[0];
//        *xc = __board_palette[pos];
//        return true;
//    }

//    for(int i = 0; i < x_arr_colors_size; i++){
//        if(strcmp(x_arr_colors[i].key, color) == 0){
//            *xc = x_arr_colors[i].color;
//            return true;
//        }
//    }
//    return false;
//}

//void x_color_store(char shortcut[2], const char * entry, X_Color color){
//    palette_set(shortcut[0], color);
//    x_color_add(entry, color);
//}

//void x_color_add(const char * entry, X_Color color){
//    if(x_arr_colors_size < X_MAX_ITENS){
//        strcpy(x_arr_colors[x_arr_colors_size].key, entry);
//        x_arr_colors[x_arr_colors_size].color = color;
//        x_arr_colors_size += 1;
//    }
//}

//void __x_init_colors(){
//    for(int i = 0; i < 256; i++)
//        __board_palette[i] = WHITE;

//    x_color_store("a", "aqua",    x_color_make(0, 255, 255, 255));
//    x_color_store("A", "amber",    x_color_make(255,191,0, 255));

//    x_color_store("b", "blue",    x_color_make(38 , 139, 210, 255));
//    x_color_store("B", "brown",    x_color_make(150,75,0, 255));

//    x_color_store("c", "cyan",    x_color_make(42 , 161, 152, 255));
//    x_color_store("C", "corn",    x_color_make(251,236,93, 255));
//    x_color_store("0", "coral",  x_color_make(255, 127, 80  , 255));

//    x_color_store("d", "dark",    x_color_make(7  , 54 , 66 , 255));
//    x_color_store("D", "desert",    x_color_make(193, 154, 107, 255));

//    x_color_store("e", "error",   x_color_make(255,   0,   0, 255));
//    x_color_store("E", "emerald", x_color_make(80,200,120, 255));

//    x_color_store("f", "flax",    x_color_make(238, 220, 130, 255));
//    x_color_store("F", "forest",  x_color_make(34,139,34, 255));

//    x_color_store("g", "green",   x_color_make(133, 153, 0  , 255));
//    x_color_store("G", "gold",    x_color_make(255, 215, 0, 255));
//    x_color_store("1", "gray",  x_color_make(128, 128, 128  , 255));

//    x_color_store("h", "heaven",  x_color_make(180, 176, 236, 255));
//    x_color_store("H", "han",     x_color_make(68, 108, 207, 255));

//    x_color_store("i", "indigo",  x_color_make(0  ,  65, 106, 255));
//    x_color_store("I", "iceberg",  x_color_make(113, 166, 210, 255));

//    x_color_store("j", "jade",    x_color_make(0  , 168, 107, 255));
//    x_color_store("J", "jasmine",    x_color_make(248, 222, 126, 255));

//    x_color_store("k", "black",   x_color_make(7  , 54 , 66 , 255));
//    x_color_store("K", "khaki",   x_color_make(195, 176, 145, 255));

//    x_color_store("l", "lavender",x_color_make(240, 230, 140, 255));
//    x_color_store("L", "lime",    x_color_make(191, 255, 0, 255));

//    x_color_store("m", "magenta", x_color_make(211, 54 , 130, 255));
//    x_color_store("M", "maroon", x_color_make(128,0,0, 255));
//    x_color_store("2", "midnight",x_color_make(25, 25, 112, 255));

//    x_color_store("n", "navy", x_color_make(0,0,128, 255));

//    x_color_store("o", "orange",  x_color_make(253, 106, 2, 255));
//    x_color_store("O", "olive",  x_color_make(128, 128, 0, 255));

//    x_color_store("p", "pink",    x_color_make(255, 20, 147, 255));
//    x_color_store("P", "purple",  x_color_make(128,0,128, 255));

//    x_color_store("r", "red",     x_color_make(211, 1  , 2  , 255));
//    x_color_store("R", "ruby",    x_color_make(224, 17, 95, 255));

//    x_color_store("s", "silver",  x_color_make(192, 192, 192, 255));
//    x_color_store("S", "sepia",  x_color_make(112, 66, 20, 255));
//    x_color_store("3", "salmon",  x_color_make(250, 128, 114  , 255));

//    x_color_store("t", "tan",  x_color_make(210, 180, 140, 255));
//    x_color_store("T", "turquoise",  x_color_make(62, 224, 208, 255));
//    x_color_store("4", "teal",  x_color_make(0, 128, 128 , 255));

//    x_color_store("u", "umber",  x_color_make(99, 81, 71, 255));
//    x_color_store("U", "ultramarine",  x_color_make(18, 10, 143, 255));

//    x_color_store("v", "violet",  x_color_make(108, 113, 196, 255));
//    x_color_store("V", "vanilla",  x_color_make(243, 229, 171, 255));

//    x_color_store("w", "white",   x_color_make(238, 232, 213, 255));
//    x_color_store("W", "wheat",   x_color_make(254, 222, 179, 255));

//    x_color_store("y", "yellow",  x_color_make(181, 137, 0  , 255));

////    __x_init_pallete();
//}

//void x_color_show(X_Color color){
//    printf("{%3d, %3d, %3d, %3d}\n", color.r, color.g, color.b, color.a);
//}

//X_Color x_color_decode(const char * color){
//    X_Color xc;
//    if(__x_decode_rgba(color, &xc) || __x_decode_hex(color, &xc) || __x_color_load(color, &xc))
//        return xc;
//    printf("fail: X_Color \"%s\" could not be decoded\n", color);
//    return xc;
//}
