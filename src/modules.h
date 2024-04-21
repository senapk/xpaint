/*
###############################################
############ FUNÇÕES DE GRID ##################
###############################################
*/
#include <stdarg.h>
/*Init the grid*/
/*side is the size of the cell */
/*sep the space in black between cells */
void grid_init(int side, int sep);

/*plots a square in cell*/
void grid_square(int l, int c);

/*plots a circle in cell*/
void grid_circle(int l, int c);

/*writes a text until 5 char in cell*/
void grid_write(int l, int c, const char *format, ...);


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
void bar_init(int size, int max);

/**
 * @brief print a single bar
 * 
 * @param i the index
 * @param value the value of the bar size
 */
void bar_one(int i, int value);

/**
 * @brief show the entire array
 * 
 * @param vet the vector with the values
 * @param size of the vector
 * @param colors the array of color to mark unique elements or NULL
 * @param indices the array with the unique indices to be marked with the colors
 */
void bar_all(int * vet, int size, const char * colors, int * indices);


#define x_bar_save(vet, size, colors, ...) do{\
    int __indices[] = {__VA_ARGS__};\
    bar_all(vet, size, colors, __indices);\
    save();\
} while(0);

/*
###############################################
####### FUNÇÕES PARA DESENHAR COM A CANETA ####
###############################################
*/

void   pen_set_angle(double degrees);
void   pen_set_thick(int thick);
void   pen_set_pos(double x, double y);
double pen_get_angle();
int    pen_get_thick();
double pen_get_x();
double pen_get_y();
void   pen_up(void);
void   pen_down(void);
void   pen_walk(double distance);
void   pen_rotate(int degrees);
void   pen_goto(double x, double y);




