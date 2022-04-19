#ifndef BASE_H /*XDDDX*/
#define BASE_H /*XDDDX*/

#include "color.h" /*XDDDX*/
#include <stdarg.h>

/* @brief Open the board to draw */
/* @param filename path to save the png */
void x_open(unsigned int width, unsigned int height, const char * filename);

/* retorna altura, largura, filename and bitmap */
int          x_get_height(void);
int          x_get_width(void);
const char * x_get_filename(void);
uchar      * x_get_bitmap(void);

/* @brief Clear all resources */
void x_close(void);

/* @brief Changes the the default filename to save the image */
/* @param filename path */
void x_set_filename(const char * filename);

/* define the path ou command to external tool to open the image in first save */
/* Ex: "gthumb", "gthumb" */
void x_set_viewer(const char * viewer);

/* a funcao plot pinta o pixel usando a cor padrão */
void x_plot(int x, int y);

/* retorna a cor do pixel dessa posicao do bitmap */
X_Color x_get_pixel(int x, int y);

/* muda a cor do pincel*/
void x_color_set(X_Color color);

#ifdef __cplusplus

void x_color_set(int r, int g, int b, int a = 255);
void x_color_set(char color);

#endif

/* muda a cor do pincel usando a paleta de cores*/
void x_color_load(char color);

/* return the current color for brush */
X_Color x_color_get(void);

/* limpa a tela inteira com a mesma cor */
void x_clear(void);

/* save the bitmap in filename.png */
void x_save(void);

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


void __x_make_layer(void);
void __x_merge_layer(void);


#endif /*XDDDX*/
