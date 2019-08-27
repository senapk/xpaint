#include "color.h" /*XDDDX*/

static X_Color __board_palette[256];

X_Color X_COLOR_WHITE     = {238, 232, 213, 255};
X_Color X_COLOR_BLACK     = {7  , 54 , 66 , 255};
X_Color X_COLOR_GREEN     = {133, 153, 0  , 255};
X_Color X_COLOR_RED       = {211, 1  , 2  , 255};
X_Color X_COLOR_BLUE      = {38 , 139, 210, 255};
X_Color X_COLOR_YELLOW    = {181, 137, 0  , 255};
X_Color X_COLOR_CYAN      = {42 , 161, 152, 255};
X_Color X_COLOR_MAGENTA   = {211, 54 , 130, 255};
X_Color X_COLOR_ORANGE    = {253, 106, 2  , 255};
X_Color X_COLOR_VIOLET    = {108, 113, 196, 255};


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

void __x_init_colors(void){
    int i = 0;
    for(i = 0; i < 256; i++)
        __board_palette[i] = X_COLOR_WHITE;

    __board_palette['r'] = X_COLOR_RED;
    __board_palette['g'] = X_COLOR_GREEN;
    __board_palette['b'] = X_COLOR_BLUE;
    __board_palette['y'] = X_COLOR_YELLOW;
    __board_palette['m'] = X_COLOR_MAGENTA;
    __board_palette['c'] = X_COLOR_CYAN;
    __board_palette['k'] = X_COLOR_BLACK;
    __board_palette['w'] = X_COLOR_WHITE;
    __board_palette['o'] = X_COLOR_ORANGE;
    __board_palette['v'] = X_COLOR_VIOLET;
}
