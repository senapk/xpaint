#include "save.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lodepng.h"

void x_save_ppm(unsigned dimx, unsigned dimy, unsigned char * bitmap, const char * filename){
    /* const int dimx = x_get_width();
    const int dimy = x_get_height();
     */
    char path[400];
    sprintf(path, "%s.ppm", filename);
    FILE *fp = fopen(path, "wb"); /* b - binary mode */
    fprintf(fp, "P6\n%d %d\n255\n", dimx, dimy);
    fwrite(bitmap, 1, (size_t) (dimx * dimy * 3), fp);
    fclose(fp);
}

void x_save_png(unsigned dimx, unsigned dimy, unsigned char * bitmap, const char * filename){
    char * dest = (char*) malloc(strlen(filename + 10));
    strcpy(dest, filename);
    strcat(dest, ".png");
    unsigned error = lodepng_encode_file(dest, bitmap, dimx, dimy, LCT_RGB, 8);
    if(error)
        printf("error %u: %s\n", error, lodepng_error_text(error));
    free(dest);
}