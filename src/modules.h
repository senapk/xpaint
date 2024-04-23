/*
###############################################
############ FUNÇÕES DE GRID ##################
###############################################
*/
#include <stdarg.h>
/*Init the grid*/
/*side is the size of the cell */
/*sep the space in black between cells */
void gridInit(int side, int sep);

/*plots a square in cell*/
void gridSquare(int l, int c);

/*plots a circle in cell*/
void gridCircle(int l, int c);

/*writes a text until 5 char in cell*/
void gridText(int l, int c, const char *format, ...);


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
void barInit(int size, int max);

/**
 * @brief print a single bar
 * 
 * @param i the index
 * @param value the value of the bar size
 */
void barOne(int i, int value);

/**
 * @brief show the entire array
 * 
 * @param vet the vector with the values
 * @param size of the vector
 * @param colors the array of color to mark unique elements or NULL
 * @param indices the array with the unique indices to be marked with the colors
 */
void barAll(int * vet, int size, const char * colors, int * indices);


#define barSave(vet, size, colors, ...) do{\
    int __indices[] = {__VA_ARGS__};\
    barAll(vet, size, colors, __indices);\
    save();\
} while(0);

/*
###############################################
####### FUNÇÕES PARA DESENHAR COM A CANETA ####
###############################################
*/

void   penSetAngle(double degrees);
void   penSetThick(int thick);
void   penSetPos(double x, double y);
double penGetAngle();
int    penGetThick();
double penGetX();
double penGetY();
void   penUp(void);
void   penDown(void);
void   penWalk(double distance);
void   penRotate(int degrees);
void   penGoto(double x, double y);




