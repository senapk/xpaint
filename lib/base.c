
#include "base.h" /*XDDDX*/
#include "text.h" /*XDDDX*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> /* mencpy, srand */
#include <string.h> /* strcpy */
#include <time.h>   /* time */


void x_save_ppm(unsigned dimx, unsigned dimy, unsigned char * bitmap, const char * filename);
void x_save_png(unsigned dimx, unsigned dimy, unsigned char * bitmap, const char * filename);
void x_init_font();

/* #define X_SAVE_PPM */


#ifndef X_SAVE_PPM
const char * __board_extension = ".png";
#else
const char * __board_extension = ".ppm";
#endif


static uchar *   __board_bitmap  = NULL;
static unsigned  __board_width  = 0;
static unsigned  __board_height = 0;

static uchar     __board_color[X_BYTES_PER_PIXEL];

static bool      __board_is_open = false;
static char      __board_filename[200] = "";
static char      __board_viewer  [200] = "";
static int       __board_step          = 1;

/* Local prototypes */
uchar * __x_get_pixel_pos(unsigned int x, unsigned int y);

uchar * __x_get_pixel_pos(unsigned x, unsigned y){
    return __board_bitmap + X_BYTES_PER_PIXEL * (__board_width * y + x);
}



void x_open(unsigned int width, unsigned int height, const char * filename){
    if(__board_is_open){
        fprintf(stderr, "fail: bitmat already open\n");
        return;
    }
    __board_is_open = true;
    __board_height = height;
    __board_width = width;
    strcpy(__board_filename, filename);

    __board_bitmap = (uchar*) calloc(sizeof(uchar), width * height * X_BYTES_PER_PIXEL);
    __board_color[0] = 200;
    __board_color[1] = 200;
    __board_color[2] = 200;

    __x_init_colors();
    __x_init_font();
    srand((unsigned) time(NULL));
}

int x_get_height(void){
    return (int) __board_height;
}

int x_get_width(void){
    return (int) __board_width;
}

uchar * x_get_bitmap(void){
    return __board_bitmap;
}

const char * x_get_filename(void){
    return __board_filename;
}

void x_close(void){
    if(__board_bitmap != NULL){
        free(__board_bitmap);
        __board_is_open = false;
    }
    __board_is_open = false;
    //TODO close font
}

void x_set_filename(const char * filename){
    if(filename != NULL)
        strcpy(__board_filename, filename);
    else
        strcpy(__board_filename, "");
}

void x_set_viewer(const char * viewer){
    if(viewer != NULL)
        strcpy(__board_viewer, viewer);
    else
        strcpy(__board_viewer, "");
}

void x_plot(int x, int y){
    if(!__board_is_open){
        fprintf(stderr, "fail: x_open(weight, width, filename) missing\n");
        exit(1);
    }
    if((x >= 0) && (x < (int) __board_width) && (y >= 0) && (y <  (int) __board_height)){
        uchar * pos = __x_get_pixel_pos((unsigned) x, (unsigned) y);
        memcpy(pos, __board_color, X_BYTES_PER_PIXEL * sizeof(uchar));
    }
}

X_Color x_get_pixel(int x, int y){
    uchar * pixel = __x_get_pixel_pos((unsigned) x, (unsigned) y);
    X_Color color;
    memcpy(&color, pixel, X_BYTES_PER_PIXEL * sizeof(uchar));
    return color;
}

void x_set_color(X_Color color){
    memcpy(__board_color, &color, X_BYTES_PER_PIXEL * sizeof(uchar));
}

X_Color x_get_color(void){
    X_Color color;
    memcpy(&color, __board_color, X_BYTES_PER_PIXEL * sizeof(uchar));
    return color;
}

void x_clear(void){
    unsigned x, y;
    for(x = 0; x < __board_width; x++)
        for(y = 0; y < __board_height; y++)
            memcpy(__x_get_pixel_pos((unsigned) x, (unsigned) y), __board_color, X_BYTES_PER_PIXEL * sizeof(uchar));
}

void x_save(){
#ifndef X_SAVE_PPM
    x_save_png(__board_width, __board_height, __board_bitmap, __board_filename);
#else
    x_save_ppm(__board_width, __board_height, __board_bitmap, __board_filename);
#endif
    static int init = 1;
    if(init){
        init = 0;
        char cmd[500];
        if(strcmp(__board_viewer, "") != 0){
            sprintf(cmd, "%s %s%s&",__board_viewer, __board_filename, __board_extension);
            puts(cmd);
            system(cmd);
        }
    }
}

void x_log(){
    static int index = 0;
    char * name = (char *) malloc((strlen(__board_filename) + 10) * sizeof(char));
    sprintf(name, "%s%05d", __board_filename, index);
    index += 1;
    printf("saving: %s%s\n", name, __board_extension);
#ifndef X_SAVE_PPM
    x_save_png(__board_width, __board_height, __board_bitmap, name);
#else
    x_save_ppm(__board_width, __board_height, __board_bitmap, name);
#endif
    free(name);
}

void x_set_step(int value){
    __board_step = value;
}

int x_control(){
    static int init = 1;
    static int rounds = 0;
    static int state = 0;
    if(init == 1){
        init = 0;
        printf("press{enter/step value/0 to skip}\n");
    }

    rounds += 1;
    state += 1;
    if((__board_step != 0) && (rounds >= __board_step)){
        printf("(state: %i, step: %i): ", state, __board_step);
        char line[200];
        fgets(line, sizeof(line), stdin);
        char * ptr = line;
        int value = (int) strtol(line, &ptr, 10);
        if(ptr != line)
            __board_step = value;
        rounds = 0;
        return true;
    }
    return false;
}
