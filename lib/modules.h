/*
###############################################
############ FUNÇÕES DE GRID ##################
###############################################
*/
#include <stdarg.h>
/*Init the grid*/
/*side is the size of the cell */
/*sep the space in black between cells */
void x_grid_init(int side, int sep);

/*plots a square in cell*/
void x_grid_square(int l, int c);

/*plots a circle in cell*/
void x_grid_circle(int l, int c);

/*writes a text until 5 char in cell*/
void x_grid_write(int l, int c, const char *format, ...);


/*
###############################################
####### FUNÇÕES PARA VISUALIZAR VETORES #######
###############################################
*/


/**
 * @brief initialize the module to print bars for show sort
 * 
 * @param size the size of the array
 * @param max the max value of the array
 */
void x_bar_init(int size, int max);

/**
 * @brief print a single bar
 * 
 * @param i the index
 * @param value the value of the bar size
 */
void x_bar_one(int i, int value);

/**
 * @brief show the entire array
 * 
 * @param vet the vector with the values
 * @param size of the vector
 * @param colors the array of color to mark unique elements or NULL
 * @param indices the array with the unique indices to be marked with the colors
 */
void x_bar_all(int * vet, int size, const char * colors, int * indices);


#define x_bar_save(vet, size, colors, ...) do{\
    int __indices[] = {__VA_ARGS__};\
    x_bar_all(vet, size, colors, __indices);\
    x_save();\
} while(0);

/*
###############################################
####### FUNÇÕES PARA DESENHAR COM A CANETA ####
###############################################
*/

void   x_pen_set_angle(double degrees);
void   x_pen_set_thick(int thick);
void   x_pen_set_pos(double x, double y);
double x_pen_get_angle();
int    x_pen_get_thick();
double x_pen_get_x();
double x_pen_get_y();
void   x_pen_up(void);
void   x_pen_down(void);
void   x_pen_walk(double distance);
void   x_pen_rotate(int degrees);
void   x_pen_goto(double x, double y);




