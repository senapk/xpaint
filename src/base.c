
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
uchar * __x_get_pixel_pos(unsigned int x, unsigned int y);

uchar * __x_get_pixel_pos(unsigned int x, unsigned int y) {
    return __board_bitmap + __X_BYTES_PER_PIXEL * (__board_width * y + x);
}

//plot sem as verificações de limite
void __x_plot(int x, int y, uchar * color);

void open(unsigned int width, unsigned int height, const char * filename){
    if(__board_is_open){
        fprintf(stderr, "fail: bitmat already open\n");
        return;
    }
    __board_is_open = true;
    __board_height = height;
    __board_width = width;
    strcpy(__board_filename, filename);

    __board_bitmap = (uchar*) calloc(sizeof(uchar), width * height * __X_BYTES_PER_PIXEL);
    background(make_color(30, 30, 30, 255));

    // __stroke[0] = 200;
    // __stroke[1] = 200;
    // __stroke[2] = 200;
    // __stroke[3] = 255;

    __x_init_pallete();
    __x_init_font();
    srand((unsigned) time(NULL));
}

int get_height(void){
    return (int) __board_height;
}

int get_width(void){
    return (int) __board_width;
}

uchar * get_bitmap(void){
    return __board_bitmap;
}

const char * get_filename(void){
    return __board_filename;
}

void close(void){
    if(__board_bitmap != NULL){
        free(__board_bitmap);
        __board_is_open = false;
    }
    __board_is_open = false;
}


void set_filename(const char * filename){
    if(filename != NULL)
        strcpy(__board_filename, filename);
    else
        strcpy(__board_filename, "");
}

void set_viewer(const char * viewer){
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

void plot(int x, int y,  Color color) {
    if(!__board_is_open){
        fprintf(stderr, "fail: x_open(weight, width, filename) missing\n");
        exit(1);
    }
    uchar __color[__X_BYTES_PER_PIXEL];
    __color[0] = color.r;
    __color[1] = color.g;
    __color[2] = color.b;
    __color[3] = color.a;

    if((x >= 0) && (x < (int) __board_width) && (y >= 0) && (y <  (int) __board_height))
        __x_plot(x, y, __color);
}


Color get_pixel(int x, int y){
    uchar * pixel = __x_get_pixel_pos((unsigned) x, (unsigned) y);
    Color color;
    memcpy(&color, pixel, __X_BYTES_PER_PIXEL * sizeof(uchar));
    return color;
}

void background(Color color){
    uchar __color[__X_BYTES_PER_PIXEL];
    memcpy(__color, &color, __X_BYTES_PER_PIXEL * sizeof(uchar));

    unsigned x, y;
    for(x = 0; x < __board_width; x++)
        for(y = 0; y < __board_height; y++)
            memcpy(__x_get_pixel_pos((unsigned) x, (unsigned) y), __color, __X_BYTES_PER_PIXEL * sizeof(uchar));
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



void save(){
    if (strcmp(__board_folder, "") != 0)
        __x_log();
    if (__board_lock)
        __x_lock();
    else
        __x_save();
}

void make_video(int framerate){
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

void set_log(const char * folder) {
    strcpy(__board_folder, folder);
}

void set_lock(){
    __board_lock = true;
}

void save_ppm(unsigned dimx, unsigned dimy, unsigned char * bitmap, const char * filename){
    /* const int dimx = x_get_width();
    const int dimy = get_height();
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
    __board_transform[__board_transform_index] = (Transform) {0, 0, 1, 0};
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

void rotate(double angle) {
    if(__board_transform_index < 0){
        fprintf(stderr, "fail: stack is empty\n");
        exit(1);
    }
    __board_transform[__board_transform_index].angle = angle;
}

//pass x and y to all transformations in the stack
V2d transform(double x, double y) {
    V2d point = make_v2d(x, y);
    for(int i = 0; i <= __board_transform_index; i++) {
        Transform t = __board_transform[i];
        double angle = t.angle;
        double x = point.x;
        double y = point.y;
        point.x = x * math_cos(angle) - y * math_sin(angle);
        point.y = x * math_sin(angle) + y * math_cos(angle);
        point.x *= t.s;
        point.y *= t.s;
        point.x += t.dx;
        point.y += t.dy;
    }
    return point;
}


double get_transform_scale() {
    double s = 1;
    for(int i = 0; i <= __board_transform_index; i++){
        s *= __board_transform[i].s;
    }
    return s;
}
