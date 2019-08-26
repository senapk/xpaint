
#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>

#include "text.h" /*XDDDX*/
#include "base.h" /*XDDDX*/
#include "font.h" /*XDDDX*/
#include "true.h" /*XDDDX*/

typedef struct{
    unsigned char * buffer;
    struct stbtt_fontinfo info;
    float scale;
    int ascent;
    int descent;
    int lineGap;
} X_Font;

static X_Font __board_font_default;
static X_Font * __board_font = NULL;
static bool __board_using_default_font = false;
static int __board_font_size = 20;

void __x_init_font(){
    /*__board_font_default = (X_Font*) malloc(sizeof(X_Font));*/
    __board_font_default.buffer = __x_font_buffer_profont;
    stbtt_InitFont(&__board_font_default.info, __board_font_default.buffer, 0);

    /* setando a font default como fonte do sistema */
    __board_font = &__board_font_default;
    __board_using_default_font = true;
    x_set_font_size(20);
}

void x_set_font_size(int size){
    __board_font_size = size;
    __board_font->scale = stbtt_ScaleForPixelHeight(&__board_font->info, size);
    stbtt_GetFontVMetrics(&__board_font->info, &__board_font->ascent, &__board_font->descent, &__board_font->lineGap);
    __board_font->ascent *= __board_font->scale;
    __board_font->descent *= __board_font->scale;
}

int x_write(int x, int y, const char * format, ...){
    char text[1000];
    va_list args;
    va_start( args, format );
    vsprintf(text, format, args);
    va_end( args );

    int i;
    unsigned _x = x;

    /* setando a cor */
    X_Color xc = x_get_color();
    unsigned char color[3] = {xc.r, xc.g, xc.b};
    __board_font->info.userdata = (void *) color;

    for (i = 0; i < (int) strlen(text); ++i) {
        if(text[i] == '\n'){
            y += __board_font_size;
            _x = x;
            continue;
        }

        /* how wide is this character */
        int ax;
        stbtt_GetCodepointHMetrics(&__board_font->info, text[i], &ax, 0);
        ax = ax * __board_font->scale;

        if(_x + ax > x_get_width()){
            y += __board_font_size;
            _x = 10;
        }

        if((unsigned) y + __board_font_size > x_get_height()){
            return _x;
        }

        /* get bounding box for character (may be offset to account for chars that dip above or below the line */
        int c_x1, c_y1, c_x2, c_y2;
        stbtt_GetCodepointBitmapBox(&__board_font->info, text[i], __board_font->scale, __board_font->scale, &c_x1, &c_y1, &c_x2, &c_y2);

        /* compute y (different characters have different heights */
        int _y = y + __board_font->ascent + c_y1;

        /* render character (stride and offset is important here) */
        uchar * bitmap = x_get_bitmap();
        int byteOffset = _x + (_y  * x_get_width());
        stbtt_MakeCodepointBitmap(&__board_font->info, bitmap + 3 * byteOffset, c_x2 - c_x1, c_y2 - c_y1,
                                  x_get_width(), __board_font->scale, __board_font->scale, text[i]);

        _x += ax; /* desloca x para proximo caractere */

        /* add kerning */
        int kern;
        kern = stbtt_GetCodepointKernAdvance(&__board_font->info, text[i], text[i + 1]);
        _x += kern * __board_font->scale;
    }
    return _x;
}

