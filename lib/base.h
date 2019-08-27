#ifndef BASE_H /*XDDDX*/
#define BASE_H /*XDDDX*/

#include "color.h" /*XDDDX*/

/*
###############################################
######## ABRINDO, FECHANDO, SALVANDO ##########
###############################################
*/

/* @brief Open the board to draw */
/* @param filename path to save the png */
void x_open(unsigned int width, unsigned int height, const char * filename);

/* retorna altura, largura, filename and bitmap */
int           x_get_height(void);
int           x_get_width(void);
const char *  x_get_filename(void);
uchar * x_get_bitmap(void);

/* @brief Clear all resources */
void x_close(void);

/* @brief Changes the the default filename to save the image */
/* @param filename path */
void x_set_filename(const char * filename);

/* define the path ou command to external tool to open the image in first save */
/* Ex: "eog", "gthumb" */
void x_set_viewer(const char * viewer);

/* a funcao plot pinta o pixel usando a cor padrão */
void x_plot(int x, int y);

/* retorna a cor do pixel dessa posicao do bitmap */
X_Color x_get_pixel(int x, int y);

/* muda a cor do pincel para todas as funcoes de desenho */
void x_set_color(X_Color color);

/* return the current color for brush */
X_Color x_get_color(void);

/* limpa a tela inteira com a mesma cor */
void x_clear(void);

/* save the bitmap in filename.png */
void x_save(void);

/*
    saves the file with a numeric sufix at the end
    if the filename is img, sequencial calls of this function
    will save the following files
    img_00000.png img_00001.png img_00002.png img_00003.png
*/
void x_log();

/* set the step for x_control */
void x_set_step(int value);

/* Interact with user to perform saves */
/* Returns true if save is should be done */
int x_control();

void __x_make_layer(void);
void __x_merge_layer(void);


#endif /*XDDDX*/
