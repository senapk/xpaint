#ifndef BASE_H /*XDDDX*/
#define BASE_H /*XDDDX*/

#include "color.h" /*XDDDX*/
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

/* a funcao plot pinta o pixel usando a cor padrão */
void point(int x, int y);

/* a funcao plot pinta o pixel usando a cor de preenchimento padrão */
void point_fill(int x, int y);

/* retorna a cor do pixel dessa posicao do bitmap */
Color get_pixel(int x, int y);

/* muda a cor do pincel*/
void stroke(Color color);

/* muda a cor do pincel*/
void stroke_rgba(uchar r, uchar g, uchar b, uchar a);

/* muda a cor do pincel usando a paleta de cores*/
void stroke_char(char c);

/* muda a cor do pincel*/
void fill(Color color);

/* muda a cor do pincel*/
void fill_rgba(uchar r, uchar g, uchar b, uchar a);

/* muda a cor do pincel usando a paleta de cores*/
void fill_char(char c);

/* desabilita o pincel */
void no_stroke();

/* desabilita o preenchimento */
void no_fill();

/* return the current color for brush */
Color get_stroke(void);

/* return the current color for brush */
Color get_fill(void);


/* limpa a tela inteira com a mesma cor */
void background(Color color);

/* save the bitmap in filename.png */
void save(void);

/* Enable interactive save and lock control */
void x_set_lock();

/*
    define folder to saves the file with a numeric sufix at the end
    if the filename is img, sequencial calls of this function
    will save the following files
    img_00000.png img_00001.png img_00002.png img_00003.png
*/
void x_set_log(const char * folder);

/* creates a .mp4 video using all .png stored in folder using ffmpeg */
void x_make_video(int framerate);


#endif /*XDDDX*/
