
#include "base.h" /*XDDDX*/
#include "text.h" /*XDDDX*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> /* mencpy, srand */
#include <string.h> /* strcpy */
#include <time.h>   /* time */
#include "color.h" /*XDDDX*/
#include "lodepng.h" /*XDDDX*/
#include "xmath.h" /*XDDDX*/

void save_ppm(unsigned dimx, unsigned dimy, unsigned char * bitmap, const char * filename);
void save_png(unsigned dimx, unsigned dimy, unsigned char * bitmap, const char * filename);

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

static bool      __board_is_open = false;
static bool      __board_lock = false;
static char      __board_filename[200] = "";
static char      __board_viewer  [200] = "";
static char      __board_folder  [200] = "";
static int       __board_step          = 1;

static Transform __board_transform[10];
static int       __board_transform_index = -1;

/* Local prototypes */
uchar * __pixel(unsigned int x, unsigned int y);

uchar * __pixel(unsigned int x, unsigned int y) {
    return __board_bitmap + __X_BYTES_PER_PIXEL * (__board_width * y + x);
}

//__plot sem as verificações de limite
void __alpha_plot(int x, int y, Color color);

void xopen(unsigned int width, unsigned int height, const char * filename){
    if(__board_is_open){
        fprintf(stderr, "fail: bitmat already open\n");
        return;
    }
    __board_is_open = true;
    __board_height = height;
    __board_width = width;
    strcpy(__board_filename, filename);

    __board_bitmap = (uchar*) calloc(sizeof(uchar), width * height * __X_BYTES_PER_PIXEL);
    background("30, 30, 30, 255");

    __init_colors();
    __x_init_font();
    srand((unsigned) time(NULL));
}

int height(void){
    return (int) __board_height;
}

int width(void){
    return (int) __board_width;
}

uchar * getBitmap(void){
    return __board_bitmap;
}

const char * getFilename(void){
    return __board_filename;
}

void xclose(void){
    if(__board_bitmap != NULL){
        free(__board_bitmap);
        __board_is_open = false;
    }
    __board_is_open = false;
}


void setFilename(const char * filename){
    if(filename != NULL)
        strcpy(__board_filename, filename);
    else
        strcpy(__board_filename, "");
}

// void __raw_plot(int x, int y, Color _color) {
//     uchar color[__X_BYTES_PER_PIXEL];
//     color[0] = _color.r;
//     color[1] = _color.g;
//     color[2] = _color.b;
//     color[3] = _color.a;
//     uchar * pos = __pixel((unsigned) x, (unsigned) y);
//     memcpy(pos, color, __X_BYTES_PER_PIXEL * sizeof(uchar));
// }

void __alpha_plot(int x, int y, Color _color) {
    uchar color[__X_BYTES_PER_PIXEL];
    color[0] = _color.r;
    color[1] = _color.g;
    color[2] = _color.b;
    color[3] = _color.a;
    uchar * pos = __pixel((unsigned) x, (unsigned) y);
    for(int i = 0; i < 3; i++) {
        float fc = color[i] / 255.f;
        float fa = color[3] / 255.f;
        float bc = pos[i] / 255.f;
        float ba = pos[3] / 255.f;
        pos[i] = ((fc * fa) + (bc * (1 - fa))) * 255;
        pos[3] = (fa + (ba * (1 - fa))) * 255;
    }
}


void __plot(double x, double y,  Color color) {
    if(!__board_is_open){
        fprintf(stderr, "fail: x_open(weight, width, filename) missing\n");
        exit(1);
    }
    if((x >= 0) && (x < (int) __board_width) && (y >= 0) && (y <  (int) __board_height)) {
        __alpha_plot(x, y, color);
    }
}



Color getPixel(int x, int y){
    uchar * pixel = __pixel((unsigned) x, (unsigned) y);
    Color color;
    memcpy(&color, pixel, __X_BYTES_PER_PIXEL * sizeof(uchar));
    return color;
}

void background(const char* format, ...) {
    char value[1000];
    va_list args;
    va_start(args, format );
    vsprintf(value, format, args);
    va_end( args );
    Color _color = color(value);


    uchar __color[__X_BYTES_PER_PIXEL];
    memcpy(__color, &_color, __X_BYTES_PER_PIXEL * sizeof(uchar));

    unsigned x, y;
    for(x = 0; x < __board_width; x++)
        for(y = 0; y < __board_height; y++)
            memcpy(__pixel((unsigned) x, (unsigned) y), __color, __X_BYTES_PER_PIXEL * sizeof(uchar));
}

void __x_save_buffer(const char * filename) {
#ifndef XPPM
    save_png(__board_width, __board_height, __board_bitmap, filename);
#else
    save_ppm(__board_width, __board_height, __board_bitmap, filename);
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
            int result = system(cmd);
            if(result != 0)
                printf("%d\n", result);
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
    char * name = (char *) malloc((strlen(folder) + 100) * sizeof(char));
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
        if (fgets(line, sizeof(line), stdin) == NULL) {
            puts("fgets error");
        }
        char * ptr = line;
        int value = (int) strtol(line, &ptr, 10);
        if(ptr != line)
            __board_step = value;
        rounds = 0;
        __x_save();
    }
}



void save(){
    if (strcmp(__board_folder, "") != 0)
        __x_log();
    if (__board_lock)
        __x_lock();
    else
        __x_save();
}

void makeVideo(int framerate, const char * filename){
    char cmd[500];
    const char * folder = __board_folder;
    char * name = (char *) malloc((strlen(folder) + 20) * sizeof(char));
    strcpy(name, folder);
    if(folder[strlen(folder) - 1] != '/')
        strcat(name, "/");
    sprintf(cmd, "ffmpeg -y -framerate %d -pattern_type glob -i '%s*.png' -c:v libx264 -profile:v high -crf 20 -pix_fmt yuv420p %s.mp4", framerate, name, filename);
    puts(cmd);
    int result = system(cmd);
    if(result != 0)
        printf("%d\n", result);
    free(name);
}

void setLog(const char * folder) {
    strcpy(__board_folder, folder);
}

void setLock(){
    __board_lock = true;
}

void save_ppm(unsigned dimx, unsigned dimy, unsigned char * bitmap, const char * filename){
    /* const int dimx = x_get_width();
    const int dimy = height();
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

void save_png(unsigned dimx, unsigned dimy, unsigned char * bitmap, const char * filename){
    char dest[500];
    strcpy(dest, filename);
    strcat(dest, ".png");
    unsigned error = 0;
    error = lodepng_encode_file(dest, bitmap, dimx, dimy, LCT_RGBA, 8);
    if(error) {
        printf("error %u: %s\n", error, lodepng_error_text(error));
    }
}

void push() {
    __board_transform_index += 1;
    if(__board_transform_index >= 10){
        fprintf(stderr, "fail: max stack size reached\n");
        exit(1);
    }
    __board_transform[__board_transform_index] = (Transform) {0, 0, 0, 0, 1, 0};
}

void pop() {
    if(__board_transform_index < 0){
        fprintf(stderr, "fail: stack is empty\n");
        exit(1);
    }
    __board_transform_index -= 1;
}

void translate(double dx, double dy) {
    if(__board_transform_index < 0){
        fprintf(stderr, "fail: stack is empty\n");
        exit(1);
    }
    __board_transform[__board_transform_index].dx = dx;
    __board_transform[__board_transform_index].dy = dy;
}

void scale(double s) {
    if(__board_transform_index < 0){
        fprintf(stderr, "fail: stack is empty\n");
        exit(1);
    }
    __board_transform[__board_transform_index].s = s;
}

void center(double x, double y) {
    if(__board_transform_index < 0){
        fprintf(stderr, "fail: stack is empty\n");
        exit(1);
    }
    __board_transform[__board_transform_index].cx = x;
    __board_transform[__board_transform_index].cy = y;
}

void rotate(double angle) {
    if(__board_transform_index < 0){
        fprintf(stderr, "fail: stack is empty\n");
        exit(1);
    }
    __board_transform[__board_transform_index].angle = angle;
}

//pass x and y to all transformations in the stack
V2d __transform(double x, double y) {
    V2d __point = v2d(x, y);
    for(int i = 0; i <= __board_transform_index; i++) {
        Transform t = __board_transform[i];
        if (t.angle != 0) {
            __point.x -= t.cx;
            __point.y -= t.cy;
            double x = __point.x;
            double y = __point.y;
            double angle = t.angle;
            __point.x = x * xcos(angle) - y * xsin(angle);
            __point.y = x * xsin(angle) + y * xcos(angle);
            __point.x += t.cx;
            __point.y += t.cy;
        }
        __point.x *= t.s;
        __point.y *= t.s;
        __point.x += t.dx;
        __point.y += t.dy;
    }
    return __point;
}


double __get_transform_scale() {
    double s = 1;
    for(int i = 0; i <= __board_transform_index; i++){
        s *= __board_transform[i].s;
    }
    return s;
}
