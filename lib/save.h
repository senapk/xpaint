#ifndef SAVE_H /*XDDDX*/
#define SAVE_H /*XDDDX*/

//saves the bitmap in ppm format
void x_save_ppm(unsigned dimx, unsigned dimy, unsigned char * bitmap, const char * filename);

//saves the bitmap in png format
void x_save_png(unsigned dimx, unsigned dimy, unsigned char * bitmap, const char * filename);

#endif /*XDDDX*/


