#ifndef BASE_H /*XDDDX*/
#define BASE_H /*XDDDX*/

#include "color.h" /*XDDDX*/
#include "xmath.h" /*XDDDX*/

#include <stdarg.h>

/* @brief Open the board to draw */
/* @param filename path to save the png */
void open(unsigned int width, unsigned int height, const char * filename);

/* retorna altura, largura, filename and bitmap */
int          get_height(void);
int          get_width(void);
const char * get_filename(void);
uchar      * get_bitmap(void);


/* @brief Clear all resources */
void close(void);

/* @brief Changes the the default filename to save the image */
/* @param filename path */
void set_filename(const char * filename);

/* define the path ou command to external tool to open the image in first save */
/* Ex: "gthumb", "gthumb" */
void set_viewer(const char * viewer);

void plot(int x, int y,  Color color);

/* retorna a cor do pixel dessa posicao do bitmap */
Color get_pixel(int x, int y);

/* limpa a tela inteira com a mesma cor */
void background(Color color);

/* save the bitmap in filename.png */
void save(void);

/* Enable interactive save and lock control */
void set_lock();

/*
    define folder to saves the file with a numeric sufix at the end
    if the filename is img, sequencial calls of this function
    will save the following files
    img_00000.png img_00001.png img_00002.png img_00003.png
*/
void set_log(const char * folder);

/* creates a .mp4 video using all .png stored in folder using ffmpeg */
void make_video(int framerate);

typedef struct {
    double dx;
    double dy;
    double s;
    double angle;
} Transform;


void push();
void pop();
void translate(double dx, double dy);
void scale(double s);
void rotate(double angle);
V2d transform(double x, double y);

#endif /*XDDDX*/
