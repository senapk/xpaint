
#include "base.h" /*XDDDX*/
#include "text.h" /*XDDDX*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> /* mencpy, srand */
#include <string.h> /* strcpy */
#include <time.h>   /* time */
#include "color.h" /*XDDDX*/
#include "lodepng.h" /*XDDDX*/

void x_save_ppm(unsigned dimx, unsigned dimy, unsigned char * bitmap, const char * filename);
void x_save_png(unsigned dimx, unsigned dimy, unsigned char * bitmap, const char * filename);
void x_init_font();

//#define XPPM

#define __X_BYTES_PER_PIXEL 4

#ifndef XPPM
const char * __board_extension = ".png";
#else
const char * __board_extension = ".ppm";
#endif


static uchar *   __board_bitmap  = NULL;

static unsigned  __board_width  = 0;
static unsigned  __board_height = 0;

static uchar     __board_color[__X_BYTES_PER_PIXEL];

static bool      __board_is_open = false;
static bool      __board_lock = false;
static char      __board_filename[200] = "";
static char      __board_viewer  [200] = "";
static char      __board_folder  [200] = "";
static int       __board_step          = 1;

/* Local prototypes */
uchar * __x_get_pixel_pos(unsigned int x, unsigned int y);

uchar * __x_get_pixel_pos(unsigned x, unsigned y){
    return __board_bitmap + __X_BYTES_PER_PIXEL * (__board_width * y + x);
}

//plot sem as verificações de limite
void __x_plot(int x, int y, uchar * color);



void x_open(unsigned int width, unsigned int height, const char * filename){
    if(__board_is_open){
        fprintf(stderr, "fail: bitmat already open\n");
        return;
    }
    __board_is_open = true;
    __board_height = height;
    __board_width = width;
    strcpy(__board_filename, filename);

    __board_bitmap = (uchar*) calloc(sizeof(uchar), width * height * __X_BYTES_PER_PIXEL);
    __board_color[0] = 30;
    __board_color[1] = 30;
    __board_color[2] = 30;
    __board_color[3] = 255;
    x_clear();

    __board_color[0] = 200;
    __board_color[1] = 200;
    __board_color[2] = 200;
    __board_color[3] = 255;

    __x_init_pallete();
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

void __x_plot(int x, int y, uchar * color) {
    uchar * pos = __x_get_pixel_pos((unsigned) x, (unsigned) y);

    for(int i = 0; i < 3; i++) {
        float fc = color[i] / 255.f;
        float fa = color[3] / 255.f;
        float bc = pos[i] / 255.f;
        float ba = pos[3] / 255.f;
        pos[i] = ((fc * fa) + (bc * (1 - fa))) * 255;
        pos[3] = (fa + (ba * (1 - fa))) * 255;
    }
}

void x_plot(int x, int y){
    if(!__board_is_open){
        fprintf(stderr, "fail: x_open(weight, width, filename) missing\n");
        exit(1);
    }
    if((x >= 0) && (x < (int) __board_width) && (y >= 0) && (y <  (int) __board_height))
        __x_plot(x, y, __board_color);
}

X_Color x_get_pixel(int x, int y){
    uchar * pixel = __x_get_pixel_pos((unsigned) x, (unsigned) y);
    X_Color color;
    memcpy(&color, pixel, __X_BYTES_PER_PIXEL * sizeof(uchar));
    return color;
}

void x_color_set(X_Color color){
    memcpy(__board_color, &color, __X_BYTES_PER_PIXEL * sizeof(uchar));
}

#ifdef __cplusplus

void x_color_set(int r, int g, int b, int a) {
    x_color_set(x_color_make(r, g, b, a));
}
void x_color_set(char color) {
    x_color_load(color);
}

#endif

void x_color_load(char color){
    X_Color pcolor = x_color_get_palette(color);
    memcpy(__board_color, &pcolor, __X_BYTES_PER_PIXEL * sizeof(uchar));
}


X_Color x_color_get(){
    X_Color color;
    memcpy(&color, __board_color, __X_BYTES_PER_PIXEL * sizeof(uchar));
    return color;
}

void x_clear(void){
    unsigned x, y;
    for(x = 0; x < __board_width; x++)
        for(y = 0; y < __board_height; y++)
            memcpy(__x_get_pixel_pos((unsigned) x, (unsigned) y), __board_color, __X_BYTES_PER_PIXEL * sizeof(uchar));
}

void __x_save_buffer(const char * filename) {
#ifndef XPPM
    x_save_png(__board_width, __board_height, __board_bitmap, filename);
#else
    x_save_ppm(__board_width, __board_height, __board_bitmap, filename);
#endif
}

void __x_open_viewer() {
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

void __x_save(){
    __x_save_buffer(__board_filename);
    __x_open_viewer();
}

void __x_log(){
    static int index = 0;
    const char * folder = __board_folder;
    char * name = (char *) malloc((strlen(folder) + 20) * sizeof(char));
    if(folder[strlen(folder) - 1] != '/')
        sprintf(name, "%s/%05d", folder, index);
    else
        sprintf(name, "%s%05d", folder, index);
    index += 1;
    printf("saving: %s%s\n", name, __board_extension);
    __x_save_buffer(name);
    free(name);
}

void __x_lock(){
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
        __x_save();
    }
}



void x_save(){
    if (strcmp(__board_folder, "") != 0)
        __x_log();
    if (__board_lock)
        __x_lock();
    else
        __x_save();
}

void x_make_video(int framerate){
    char cmd[500];
    const char * folder = __board_folder;
    char * name = (char *) malloc((strlen(folder) + 20) * sizeof(char));
    strcpy(name, folder);
    if(folder[strlen(folder) - 1] != '/')
        strcat(name, "/");
    sprintf(cmd, "ffmpeg -y -framerate %d -pattern_type glob -i '%s*.png' -c:v libx264 -profile:v high -crf 20 -pix_fmt yuv420p video.mp4", framerate, name);
    puts(cmd);
    int result = system(cmd);
    if(result != 0)
        printf("%d\n", result);
    free(name);
}

void x_set_log(const char * folder) {
    strcpy(__board_folder, folder);
}

void x_set_lock(){
    __board_lock = true;
}

void x_save_ppm(unsigned dimx, unsigned dimy, unsigned char * bitmap, const char * filename){
    /* const int dimx = x_get_width();
    const int dimy = x_get_height();
     */
    char path[400];
    sprintf(path,"%s.ppm", filename);
    FILE *fp = fopen(path, "wb"); /* b - binary mode */
    fprintf(fp, "P6\n%d %d\n255\n", dimx, dimy);
    for(size_t i = 0; i < dimx * dimy; i++){
        fwrite(bitmap + i * __X_BYTES_PER_PIXEL, 1, 3, fp);
    }
    fclose(fp);
}

void x_save_png(unsigned dimx, unsigned dimy, unsigned char * bitmap, const char * filename){
    char dest[500];
    strcpy(dest, filename);
    strcat(dest, ".png");
    unsigned error = 0;
    error = lodepng_encode_file(dest, bitmap, dimx, dimy, LCT_RGBA, 8);
    if(error) {
        printf("error %u: %s\n", error, lodepng_error_text(error));
    }
}
