#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include "xpng.h" /* XDDDX */
#include "ximage.h" /* XDDDX */
#include "xttf.h" /* XDDDX */
#include "xfont.h" /* XDDDX */

XColor RED    = {211, 1, 2};
XColor GREEN  = {133, 153, 0};
XColor BLUE   = {38, 139, 210};
XColor YELLOW = {181, 137, 0};
XColor CYAN   = {42, 161, 152};
XColor MAGENTA = {211, 54, 130};
XColor ORANGE = {203, 75, 22};
XColor VIOLET = {108, 113, 196};
XColor WHITE = {253, 246, 227};
XColor BLACK = {0, 43, 54};

/* Definicoes das funcoes da biblioteca */
typedef struct{
    uchar* image;
    unsigned width;
    unsigned height;
} XBitmap;

typedef struct{
    uchar * buffer;
    struct stbtt_fontinfo info;
    float scale;
    int ascent;
    int descent;
    int lineGap;
} XFont;


static XColor   __palette[256];
static XBitmap* __bitmap;
static XFont*   __font;
static XFont*   __font_default;
static int      __font_size;
static bool     __using_default_font;
static uchar    __color[3];

static int xstep_jump = 1;


XBitmap * x_bitmap_create(unsigned width, unsigned height, const uchar * color);
void         x_bitmap_destroy(XBitmap * bitmap);

/* se quiser trocar a font default, passe o nome do arquivo e crie um buffer */
uchar *x_buffer_create(const char* filename);
uchar * x_get_pixel_pos(int x, int y);

uchar * x_get_pixel_pos(int x, int y){
    return __bitmap->image + 3 * (__bitmap->width * y + x);
}

XBitmap * x_bitmap_create(unsigned width, unsigned height, const uchar * color){
    XBitmap * bitmap = (XBitmap*) malloc(sizeof(XBitmap));
    bitmap->height = height;
    bitmap->width = width;
    bitmap->image = (uchar*) malloc(width * height * 3);
    unsigned y = 0, x = 0;
    for(y = 0; y < height; y++)
        for(x = 0; x < width; x++)
            memcpy(bitmap->image + 3 * (width * y + x), color, 3);
    return bitmap;
}

void x_bitmap_destroy(XBitmap * bitmap){
    free(bitmap->image);
    free(bitmap);
}

void x_open(int width, int height){
    /* inicializando a cor de fundo */
    uchar cinza[] = {30, 30, 30};
    __bitmap = x_bitmap_create(width, height, cinza);
    /* inicializando a cor de desenho e escrita */
    xs_color(make_xcolor(200, 200, 200));

    __font_default = malloc(sizeof(XFont));
    __font_default->buffer = font_buffer_profont;
    stbtt_InitFont(&__font_default->info, __font_default->buffer, 0);

    /* setando a font default como fonte do sistema */
    __font = __font_default;
    __using_default_font = true;
    xs_font_size(20);

    __palette['r'] = RED;
    __palette['g'] = GREEN;
    __palette['b'] = BLUE;
    __palette['y'] = YELLOW;
    __palette['m'] = MAGENTA;
    __palette['c'] = CYAN;
    __palette['k'] = BLACK;
    __palette['w'] = WHITE;
    __palette['v'] = VIOLET;
    __palette['o'] = ORANGE;

    srand(time(NULL));
}

void x_close(){
    x_bitmap_destroy(__bitmap);
    if(__using_default_font == false){
        free(__font->buffer);
        free(__font);
    }
}

void x_clear(XColor color){
    unsigned x, y;
    for(x = 0; x < __bitmap->width; x++){
        for(y = 0; y < __bitmap->height; y++){
            uchar * pixel = x_get_pixel_pos(x, y);
            pixel[0] = color.r;
            pixel[1] = color.g;
            pixel[2] = color.b;
        }
    }
}

void xs_color(XColor color){
    __color[0] = color.r;
    __color[1] = color.g;
    __color[2] = color.b;
}

XColor xg_color(){
    XColor color = {__color[0], __color[1], __color[2]};
    return color;
}

XColor xg_pixel(int x, int y){
    uchar * pixel = x_get_pixel_pos(x, y);
    XColor color = {pixel[0], pixel[1], pixel[2]};
    return color;
}

uchar * x_buffer_create(const char* filename){
    long size;
    uchar * font_buffer;
    FILE* font_file = fopen(filename, "rb");
    if(font_file == NULL){
        puts("arquivo não encontrado");
        exit(1);
    }
    fseek(font_file, 0, SEEK_END);
    size = ftell(font_file); /* how long is the file ? */
    fseek(font_file, 0, SEEK_SET); /* reset */
    font_buffer = malloc(size);
    fread(font_buffer, size, 1, font_file);
    fclose(font_file);
    return font_buffer;
}

void xs_font(const char* filename){
    if(filename == NULL){
        if(__using_default_font == false){
            __using_default_font = true;
            free(__font->buffer);
            free(__font);
            __font = __font_default;
        }
    }else{
        XFont * font = malloc(sizeof(XFont));
        font->buffer = x_buffer_create(filename);
        unsigned error = stbtt_InitFont(&font->info, font->buffer, 0);
        if(error == 0){
            printf("Erro no carregamento da fonte\n");
            free(font->buffer);
            free(font);
        }else{
            __font = font;
            __using_default_font = false;
        }
    }
    xs_font_size(__font_size);
}

void xs_font_size(int size){
    __font_size = size;
    __font->scale = stbtt_ScaleForPixelHeight(&__font->info, size);
    stbtt_GetFontVMetrics(&__font->info, &__font->ascent, &__font->descent, &__font->lineGap);
    __font->ascent *= __font->scale;
    __font->descent *= __font->scale;
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
    __font->info.userdata = (void *) __color;

    for (i = 0; i < (int) strlen(text); ++i) {
        if(text[i] == '\n'){
            y += __font_size;
            _x = x;
            continue;
        }

        /* how wide is this character */
        int ax;
        stbtt_GetCodepointHMetrics(&__font->info, text[i], &ax, 0);
        ax = ax * __font->scale;

        if(_x + ax > __bitmap->width){
            y += __font_size;
            _x = 10;
        }

        if(y + __font_size > __bitmap->height){
            return _x;
        }

        /* get bounding box for character (may be offset to account for chars that dip above or below the line */
        int c_x1, c_y1, c_x2, c_y2;
        stbtt_GetCodepointBitmapBox(&__font->info, text[i], __font->scale, __font->scale, &c_x1, &c_y1, &c_x2, &c_y2);

        /* compute y (different characters have different heights */
        int _y = y + __font->ascent + c_y1;

        /* render character (stride and offset is important here) */
        int byteOffset = _x + (_y  * __bitmap->width);
        stbtt_MakeCodepointBitmap(&__font->info, __bitmap->image + 3 * byteOffset, c_x2 - c_x1, c_y2 - c_y1,
                                  __bitmap->width, __font->scale, __font->scale, text[i]);

        _x += ax; /* desloca x para proximo caractere */

        /* add kerning */
        int kern;
        kern = stbtt_GetCodepointKernAdvance(&__font->info, text[i], text[i + 1]);
        _x += kern * __font->scale;
    }
    return _x;
}

void x_save(const char* filename){
    char * dest = malloc(strlen(filename + 10));
    strcpy(dest, filename);
    strcat(dest, ".png");
    unsigned error = lodepng_encode_file(dest, __bitmap->image, __bitmap->width, __bitmap->height, LCT_RGB, 8);
    if(error)
        printf("error %u: %s\n", error, lodepng_error_text(error));
    free(dest);
}

int x_log(const char* filename){
    static int i = 0;
    char * name = malloc((strlen(filename) + 10) * sizeof(char));
    sprintf(name, "%05d_%s", i, filename);
    
    x_save(name);
    i++;
    free(name);
    return i - 1;
}

void x_step(const char * filename){
    static int rounds = 0;
    static int state = 0;
    char line[200];
    rounds += 1;
    state += 1;
    if(xstep_jump == 0)
        return;
    if(rounds >= xstep_jump){
        x_save(filename);
        printf("(state: %i, jump: %i) press{enter/jump value/0 to skip}:", state, xstep_jump);
        fgets(line, sizeof(line), stdin);
        char * ptr = line;
        int value = (int) strtol(line, &ptr, 10);
        if(ptr != line)
            xstep_jump = value;
        rounds = 0;
    }
}

void x_plot(int x, int y){
    if((x >= 0) && (x < (int) __bitmap->width) && (y >= 0) && (y <  (int) __bitmap->height))
        memcpy(x_get_pixel_pos(x, y), &__color, sizeof(__color));
}

XColor make_xcolor(uchar r, uchar g, uchar b){
    XColor x = {r, g, b};
    return x;
}

void xs_palette(char c, XColor color){
    __palette[(int)c] = color;
}

XColor xg_palette(char c){
    return __palette[(int)c];
}



int xg_height(){
    if(__bitmap == NULL)
        puts("voce esqueceu o x_init();");
    return __bitmap->height;
}

int xg_width(){
    if(__bitmap == NULL)
        puts("voce esqueceu o x_init();");
    return __bitmap->width;
}
