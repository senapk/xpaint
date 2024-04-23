#ifndef BASE_H /*XDDDX*/
#define BASE_H /*XDDDX*/

#include "color.h" /*XDDDX*/
#include "xmath.h" /*XDDDX*/

#include <stdarg.h>

/* @brief Open the board to draw */
/* @param filename path to save the png */
void open(unsigned int width, unsigned int height, const char * filename);

/* retorna altura, largura, filename and bitmap */
int          height(void);
int          width(void);
const char * getFilename(void);
uchar      * getBitmap(void);


/* @brief Clear all resources */
void close(void);

/* @brief Changes the the default filename to save the image */
/* @param filename path */
void setFilename(const char * filename);

void __plot(int x, int y,  Color color);

/* retorna a cor do pixel dessa posicao do bitmap */
Color getPixel(int x, int y);

/* limpa a tela inteira com a mesma cor */
void background(Color color);

/* save the bitmap in filename.png */
void save(void);

/* Enable interactive save and lock control */
void setLock();

/*
    define folder to saves the file with a numeric sufix at the end
    if the filename is img, sequencial calls of this function
    will save the following files
    img_00000.png img_00001.png img_00002.png img_00003.png
*/
void setLog(const char * folder);

/* creates a .mp4 video using all .png stored in folder using ffmpeg */
void makeVideo(int framerate);

typedef struct {
    double dx;
    double dy;
    double s;
    double angle;
} Transform;

/* Define um vetor bidimensional com x e y */
typedef struct{
    double x;
    double y;
} V2d;

void push();
void pop();
void translate(double dx, double dy);
void scale(double s);
void rotate(double angle);

V2d __transform(double x, double y);
double __get_transform_scale();

#endif /*XDDDX*/
