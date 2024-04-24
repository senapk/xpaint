#include "color.h" /*XDDDX*/

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#define X_MAX_ITENS 1000

typedef struct ColorEntry{
    char key[20];
    Color color;
} ColorEntry;

static Color __board_palette[256];
ColorEntry __arr_colors[X_MAX_ITENS];
int __arr_colors_size = 0;

Color rgba(uchar r, uchar g, uchar b, uchar a) {
    Color x = {r, g, b, a};
    return x;
}

bool __x_validate_hex(const char * color) {
    for(int i = 1; i < 7; i++) {
        if(color[i] >= '0' && color[i] <= '9')
            continue;
        else if(color[i] >= 'a' && color[i] <= 'f')
            continue;
        else
            return false;
    }
    return true;
}

bool __decode_hex(const char * _color, Color * xc) {
    if(_color[0] != '#' || strlen(_color) != 7)
        return false;
    char color[8];
    strcpy(color, _color);
    for(int i = 1; i < 7; i++)
        color[i] = tolower(_color[i]);
    if(!__x_validate_hex(color))
        return false;
    unsigned int r, g, b;
    int readings = sscanf(color + 1, "%02x%02x%02x", &r, &g, &b);
    if(readings != 3)
        return false;
    *xc = (Color) {(unsigned char) r, (unsigned char)g, (unsigned char)b, 255};
    return true;
}

int __x_count_colon(const char * color) {
    int cont = 0;
    for(int i = 0; color[i] != '\0' ; i++)
        if(color[i] == ',')
            cont += 1;
    return cont;
}

bool __x_decode_rgba(const char * color, Color * xc) {
    int number_of_colons = __x_count_colon(color);
    if(number_of_colons != 2 && number_of_colons != 3)
        return false;
    char decode[4][4] = {"", "", "", ""};
    int  idecode[4];
    int ind = 0;
    int size = strlen(color);
    for(int i = 0; i < size; i++) {
        if(color[i] == ',') {
            ind += 1;
        }
        else if(color[i] == ' ') {
            continue;
        } 
        else if((color[i] >= '0') && (color[i] <= '9')) {
            char str[2] = "x";
            str[0] = color[i];
            strcat(decode[ind], str);
        }
        else {
            return false;
        }
    }
    if(ind == 2)
        strcpy(decode[3], "255");
    for(int i = 0; i < 4; i++)
        idecode[i] = atoi(decode[i]);
    xc->r = idecode[0];
    xc->g = idecode[1];
    xc->b = idecode[2];
    xc->a = idecode[3];
    for(int i = 0; i < 4; i++) {
        if((idecode[i] < 0) || (idecode[i] > 255))
            printf("warning: a rgb color should be inside the interval [0, 255]: %d\n", idecode[i]);
    }
    
    return true;
}

bool __decode_single_char(const char * color, Color * xc) {
    if(strlen(color) != 1)
        return false;
    if(isdigit(color[0]))
        return false;
    *xc = __board_palette[(int) color[0]];
    return true;
}

//receive a number and interpret a gray scale color
//100 -> 100, 100, 100, 255
//255 -> 255, 255, 255, 255
//0   -> 0, 0, 0, 255
bool __decode_gray(const char * color, Color * xc) {
    //convert to integer usign base 10 and check if it is a valid number
    char * endptr = NULL;
    int number = strtol(color, &endptr, 10);
    if(*endptr != '\0')
        return false;

    *xc = rgba(number, number, number, 255);
    return true;
}

bool __decode_by_name(const char * color, Color * xc) {
    for(int i = 0; i < __arr_colors_size; i++) {
        if(strcmp(__arr_colors[i].key, color) == 0) {
            *xc = __arr_colors[i].color;
            return true;
        }
    }
    return false;
}

void __color_store(const char * shortcut, const char * entry, Color color) {
    setPallete(shortcut, color);
    setPallete(entry, color);
}

void setPallete(const char * entry, Color color) {
    if(strlen(entry) == 1) {
        __board_palette[(int) entry[0]] = color;
        return;
    }

    // if the color is not in the palette, add it
    for(int i = 0; i < __arr_colors_size; i++) {
        if(strcmp(__arr_colors[i].key, entry) == 0) {
            __arr_colors[i].color = color;
            return;
        }
    }

    if(__arr_colors_size < X_MAX_ITENS) {
        strcpy(__arr_colors[__arr_colors_size].key, entry);
        __arr_colors[__arr_colors_size].color = color;
        __arr_colors_size += 1;
    }
}

void __init_colors() {
    //init constant time loading colors
    for(size_t i = 0; i < 256; i++) {
        __board_palette[i] = rgba(0, 0, 0, 255);
    }

    __color_store("a", "aqua",    rgba(0, 255, 255, 255));
    __color_store("A", "amber",   rgba(255,191,0, 255));

    __color_store("b", "blue",    rgba(38 , 139, 210, 255));
    __color_store("B", "brown",   rgba(150,75,0, 255));

    __color_store("c", "cyan",    rgba(42 , 161, 152, 255));
    __color_store("C", "corn",    rgba(251,236,93, 255));
    __color_store("0", "coral",   rgba(255, 127, 80  , 255));

    __color_store("d", "dark",    rgba(7  , 54 , 66 , 255));
    __color_store("D", "desert",  rgba(193, 154, 107, 255));

    __color_store("e", "error",   rgba(255,   0,   0, 255));
    __color_store("E", "emerald", rgba(80,200,120, 255));

    __color_store("f", "flax",    rgba(238, 220, 130, 255));
    __color_store("F", "forest",  rgba(34,139,34, 255));

    __color_store("g", "green",   rgba(133, 153, 0  , 255));
    __color_store("G", "gold",    rgba(255, 215, 0, 255));
    __color_store("1", "gray",    rgba(128, 128, 128  , 255));

    __color_store("h", "heaven",  rgba(180, 176, 236, 255));
    __color_store("H", "han",     rgba(68, 108, 207, 255));

    __color_store("i", "indigo",  rgba(0  ,  65, 106, 255));
    __color_store("I", "iceberg", rgba(113, 166, 210, 255));

    __color_store("j", "jade",    rgba(0  , 168, 107, 255));
    __color_store("J", "jasmine", rgba(248, 222, 126, 255));

    __color_store("k", "black",   rgba(7  , 54 , 66 , 255));
    __color_store("K", "khaki",   rgba(195, 176, 145, 255));

    __color_store("l", "lavender",rgba(240, 230, 140, 255));
    __color_store("L", "lime",    rgba(191, 255, 0, 255));

    __color_store("m", "magenta", rgba(211, 54 , 130, 255));
    __color_store("M", "maroon",  rgba(128,0,0, 255));
    __color_store("2", "midnight",rgba(25, 25, 112, 255));

    __color_store("n", "navy",    rgba(0,0,128, 255));

    __color_store("o", "orange",  rgba(253, 106, 2, 255));
    __color_store("O", "olive",   rgba(128, 128, 0, 255));

    __color_store("p", "pink",    rgba(255, 20, 147, 255));
    __color_store("P", "purple",  rgba(128,0,128, 255));

    __color_store("r", "red",     rgba(211, 1  , 2  , 255));
    __color_store("R", "ruby",    rgba(224, 17, 95, 255));

    __color_store("s", "silver",  rgba(192, 192, 192, 255));
    __color_store("S", "sepia",   rgba(112, 66, 20, 255));
    __color_store("3", "salmon",  rgba(250, 128, 114  , 255));

    __color_store("t", "tan",     rgba(210, 180, 140, 255));
    __color_store("T", "turquoise",  rgba(62, 224, 208, 255));
    __color_store("4", "teal",    rgba(0, 128, 128 , 255));

    __color_store("u", "umber",   rgba(99, 81, 71, 255));
    __color_store("U", "ultramarine",  rgba(18, 10, 143, 255));

    __color_store("v", "violet",  rgba(108, 113, 196, 255));
    __color_store("V", "vanilla", rgba(243, 229, 171, 255));

    __color_store("w", "white",   rgba(238, 232, 213, 255));
    __color_store("W", "wheat",   rgba(254, 222, 179, 255));

    __color_store("y", "yellow",  rgba(181, 137, 0  , 255));
}

void colorShow(Color color) {
    printf("{%3d, %3d, %3d, %3d}\n", color.r, color.g, color.b, color.a);
}

Color color(const char * format, ...) {
    char color[1000];
    va_list args;
    va_start( args, format );
    vsprintf(color, format, args);
    va_end( args );

    Color xc;
    if(__decode_single_char(color, &xc) || 
            __x_decode_rgba(color, &xc) ||
              __decode_gray(color, &xc) || 
               __decode_hex(color, &xc) ||
           __decode_by_name(color, &xc))
        return xc;
    printf("fail: Color \"%s\" could not be decoded\n", color);
    return xc;
}

void colorShowAll() {
    for(int i = 0; i < __arr_colors_size; i++) {
        printf("%s: ", __arr_colors[i].key);
        colorShow(__arr_colors[i].color);
    }
}
