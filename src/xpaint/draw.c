#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

#include "draw.h" /*XDDDX*/
#include "xmath.h" /*XDDDX*/
#include "base.h" /*XDDDX*/

static Color     __stroke = {0, 0, 0, 255};
static Color     __fill = {255, 255, 255, 255};

static bool      __stroke_enable = true;
static bool      __fill_enable = true;
static int       __thickness = 1;


void __plot_block(double x, double y, int side, Color color);
// desenha uma linha com antialias sem transformação e sem espessura
void __raw_alias_line(double x0 , double y0 , double x1 , double y1, Color color);
// divida pela escala atual antes de fazer a transformação
void __point_scale(double x, double y, Color color);
// desenha uma linha com transf espessura de 1 pixel entre os pontos (x0, y0) e (x1, y1)
void __draw_line(double x0, double y0, double x1, double y1, Color color);
// divide pela escala atual antes de fazer a transformação
void __draw_line_scale(double x0 , double y0 , double x1 , double y1, Color color);
// linha de espessura 1 sem transformação
void __raw_line(double x0, double y0, double x1, double y1, Color color);
// desenha uma linha com espessura de thickness pixels entre os pontos (x0, y0) e (x1, y1)
void __fill_line(double x0, double y0, double x1, double y1, int thickness, Color color);
// desenha um circulo dado centro e raio
void __fill_circle(double centerx, double centery, double radius);
// desenha uma elipse dentro do rect de ponto superior esquerdo(x0, y0), largura e altura
void __draw_ellipse(double x0, double y0, double width, double height);
// desenha uma elipse dentro do rect de ponto superior esquerdo(x0, y0), largura e altura
void __fill_ellipse(double x0, double y0, double width, double height);
// desenha um retangulo dados os cantos superior esquerdo (x0, y0), largura e altura
void __fill_rect(double x0, double y0, double width, double height);
// desenha um triangulo dados os 3 vertices
void __fill_raw_triangle(double v1x, double v1y, double v2x, double v2y, double v3x, double v3y, Color color);

void __plot_block(double x, double y, int side, Color color){
    for(int i = x; i < x + side; i++)
        for(int j = y; j < y + side; j++)
            __plot(i, j, color);
}

void strokeWeight(int thickness){
    __thickness = thickness;
}

void __point(double x, double y, Color color){
    V2d p = __transform(x, y);
    __plot(p.x, p.y, color);
}

void point(double x, double y) {
    double s = __get_transform_scale();
    if (s < 2) {
        __point(x, y, __stroke);
        return;
    }
    for (int i = 0; i < s; ++i) {
        for (int j = 0; j < s; ++j) {
            __point(x + (i / s), y + (j / s), __stroke);
        }
    }
}

void __point_scale(double x, double y, Color color){
    double s = __get_transform_scale();
    V2d p = __transform(x/s, y/s);
    __plot(p.x, p.y, color);
}

void stroke(const char * format, ...) {
    char value[1000];
    va_list args;
    va_start(args, format );
    vsprintf(value, format, args);
    va_end( args );

    __stroke = color(value);
    __stroke_enable = true;

}

void fill(const char * format, ...) {
    char value[1000];
    va_list args;
    va_start(args, format );
    vsprintf(value, format, args);
    va_end( args );

    __fill = color(value);
    __fill_enable = true;
}

void setStroke(Color value) {
    __stroke = value;
    __stroke_enable = true;
}

void setFill(Color value) {
    __fill = value;
    __fill_enable = true;
}


void noStroke(){
    __stroke_enable = false;
}

void noFill(){
    __fill_enable = false;
}


Color getStroke(){
    return __stroke;
}

Color getFill(){
    return __fill;
}

void __x_draw_block(int x, int y, int side, Color color){
    for(int i = x; i < x + side; i++)
        for(int j = y; j < y + side; j++)
            __point(i, j, color);
}

int ascArt(int x, int y, int zoom, const char * picture){
    int dx = 0;
    int dy = 0;
    int maxdx = 0;

    for(size_t i = 0; picture[i] != '\0'; i++){
        if(picture[i] == '\n'){
            dy += 1;
            dx = 0;
            continue;
        }
        if(picture[i] == ' '){
            dx += 1;
        }else if(picture[i] == '#'){
            __x_draw_block(x + dx * zoom, y + dy * zoom, zoom, __stroke);
            dx += 1;
            maxdx = dx > maxdx ? dx : maxdx;
        }else{
            char c[2] = {picture[i], '\0'};
            __x_draw_block(x + dx * zoom, y + dy * zoom, zoom, color(c));
            dx += 1;
            maxdx = dx > maxdx ? dx : maxdx;
        }
    }
    return (maxdx + 1) * zoom;
}

void __raw_line_int(int x0, int y0, int x1, int y1, Color color) {
    /* Bresenham's Line Algorithm */
    int dx = (x0 > x1) ? x0 - x1 : x1 - x0;
    int dy = (y0 > y1) ? y0 - y1 : y1 - y0;
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        __plot(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void __raw_line(double x0, double y0, double x1, double y1, Color color) {
    __raw_line_int(xround(x0), xround(y0), xround(x1), xround(y1), color);
}

void __x_fill_bottom_flat_triangle(double v1x, double v1y, double v2x, double v2y, double v3x, double v3y, Color color)
{
    double invslope1 = ((int)v2x - (int)v1x) / (double)((int)v2y - (int)v1y);
    double invslope2 = ((int)v3x - (int)v1x) / (double)((int)v3y - (int)v1y);

    double curx1 = v1x;
    double curx2 = v1x;

    for (int scanlineY = v1y; scanlineY <= v2y; scanlineY++){
        __raw_line(curx1, scanlineY, curx2, scanlineY, color);
        curx1 += invslope1;
        curx2 += invslope2;
    }
}

void __x_fill_top_flat_triangle(double v1x, double v1y, double v2x, double v2y, double v3x, double v3y, Color color)
{
    double invslope1 = ((int)v3x - (int)v1x) / (double)((int)v3y - (int)v1y);
    double invslope2 = ((int)v3x - (int)v2x) / (double)((int)v3y - (int)v2y);

    double curx1 = v3x;
    double curx2 = v3x;

    for (int scanlineY = v3y; scanlineY >= v1y; scanlineY--)
    {
        __raw_line(curx1, scanlineY, curx2, scanlineY, color);
        curx1 -= invslope1;
        curx2 -= invslope2;
    }
}

void __fill_raw_triangle(double v1x, double v1y, double v2x, double v2y, double v3x, double v3y, Color color)
{
    V2d v1 = {v1x, v1y};
    V2d v2 = {v2x, v2y};
    V2d v3 = {v3x, v3y};
    /* at first sort the three vertices by y-coordinate ascending so v1 is the topmost vertice */
    if((v2.y <= v1.y) && (v2.y <= v3.y))
        X_SWAP(v1, v2, V2d);
    if((v3.y <= v1.y) && (v3.y <= v2.y))
        X_SWAP(v1, v3, V2d);
    if(v3.y < v2.y)
        X_SWAP(v2, v3, V2d);

    /* here we know that v1.y <= v2.y <= v3.y */
    /* check for trivial case of bottom-flat triangle */
    if (v2.y == v3.y)
        __x_fill_bottom_flat_triangle(v1.x, v1.y, v2.x, v2.y, v3.x, v3.y, color);
    else if (v1.y == v2.y)
        __x_fill_top_flat_triangle(v1.x, v1.y, v2.x, v2.y, v3.x, v3.y, color);
    else
    {
        /* general case - split the triangle in a topflat and bottom-flat one */
        V2d v4 = {0.f, 0.f};
        v4.x = (v1.x + ((double)(v2.y - v1.y) / (double)(v3.y - v1.y)) * (v3.x - v1.x));
        v4.y = v2.y;
        __x_fill_bottom_flat_triangle(v1.x, v1.y, v2.x, v2.y, v4.x, v4.y, color);
        __x_fill_top_flat_triangle(v2.x, v2.y, v4.x, v4.y, v3.x, v3.y, color);
    }
}

void __fill_line(double x0, double y0, double x1, double y1, int thickness, Color color){
    V2d c0 = __transform(x0, y0);
    V2d c1 = __transform(x1, y1);
    V2d a = {c0.x, c0.y};
    V2d b = {c1.x, c1.y};

    V2d _offset = v2d(b.x - a.x, b.y - a.y);
    _offset = v2d_dot(v2d_ortho(v2d_normalize(_offset)), (thickness / 2.f));

    V2d p1 = v2d_sub(a, _offset);
    V2d p2 = v2d_sub(b, _offset);
    V2d p3 = v2d_sum(a, _offset);
    V2d p4 = v2d_sum(b, _offset);

    __fill_raw_triangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, color);
    __fill_raw_triangle(p3.x, p3.y, p2.x, p2.y, p4.x, p4.y, color);
}

void __fill_rect(double x0, double y0, double width, double height){
    V2d p0 = __transform(x0, y0);
    V2d p1 = __transform(x0 + width, y0);
    V2d p2 = __transform(x0 + width, y0 + height);
    V2d p3 = __transform(x0, y0 + height);

    __fill_raw_triangle(p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, __fill);
    __fill_raw_triangle(p0.x, p0.y, p2.x, p2.y, p3.x, p3.y, __fill);
}

void rect(double x, double y, double witdh, double height) {
    if (__fill_enable) {
        __fill_rect(x, y, witdh, height);
    }
    // if (__stroke_enable) {
    //     __fill_line(x, y, x + witdh, y, __thickness, __stroke);
    //     __fill_line(x + witdh, y, x + witdh, y + height, __thickness, __stroke);
    //     __fill_line(x + witdh, y + height, x, y + height, __thickness, __stroke);
    //     __fill_line(x, y + height, x, y, __thickness, __stroke);
    // }
}

void triangle(double xa, double ya, double xb, double yb, double xc, double yc){
    if(__fill_enable){
        V2d a = __transform(xa, ya);
        V2d b = __transform(xb, yb);
        V2d c = __transform(xc, yc);
        __fill_raw_triangle(a.x, a.y, b.x, b.y, c.x, c.y, __fill);
    }
    if(__stroke_enable){
        __fill_line(xa, ya, xb, yb, __thickness, __stroke);
        __fill_line(xb, yb, xc, yc, __thickness, __stroke);
        __fill_line(xc, yc, xa, ya, __thickness, __stroke);
    }
}

void square(double x, double y, double side) {
    rect(x, y, side, side);
}

/* https://en.wikipedia.org/wiki/Midpoint_circle_algorithm */
// void __draw_circle(double centerx, double centery, double radius){
//     int x = radius - 1;
//     int y = 0;
//     int dx = 1;
//     int dy = 1;
//     int err = dx - ((int) radius << 1);
//     while(x >= y){
//         __point_scale((centerx + x), (centery + y), __stroke);
//         __point_scale((centerx - x), (centery + y), __stroke);
//         __point_scale((centerx + x), (centery - y), __stroke);
//         __point_scale((centerx - x), (centery - y), __stroke);
//         __point_scale((centerx + y), (centery + x), __stroke);
//         __point_scale((centerx - y), (centery + x), __stroke);
//         __point_scale((centerx - y), (centery - x), __stroke);
//         __point_scale((centerx + y), (centery - x), __stroke);

//         if(err <= 0){
//             y++;
//             err += dy;
//             dy += 2;
//         }else{
//             x--;
//             dx += 2;
//             err += dx - ((int) radius << 1);
//         }
//     }
// }

// void __draw_circle(double centerx, double centery, double radius) {
//     int thickness = __thickness;
//     // Definindo as coordenadas do círculo
//     int x = radius - 1;
//     int y = 0;
//     int dx = 1;
//     int dy = 1;
//     int err = dx - (int)(radius * 2);

//     // Desenha o círculo utilizando o algoritmo do ponto médio
//     while (x >= y) {
//         for (int i = 0; i < thickness; i++) {
//             // Desenha os pontos simétricos em todas as oito octantes
//             __point_scale((centerx + x), (centery + y + i), __stroke);
//             __point_scale((centerx + y), (centery + x + i), __stroke);
//             __point_scale((centerx - y), (centery + x + i), __stroke);
//             __point_scale((centerx - x), (centery + y + i), __stroke);
//             __point_scale((centerx - x), (centery - y - i), __stroke);
//             __point_scale((centerx - y), (centery - x - i), __stroke);
//             __point_scale((centerx + y), (centery - x - i), __stroke);
//             __point_scale((centerx + x), (centery - y - i), __stroke);
//         }

//         if (err <= 0) {
//             y++;
//             err += dy;
//             dy += 2;
//         }

//         if (err > 0) {
//             x--;
//             dx += 2;
//             err += dx - (int)(radius * 2);
//         }
//     }
// }

void __fill_circle(double centerx, double centery, double radius){
    V2d center = __transform(centerx, centery);
    centerx = center.x;
    centery = center.y;

    radius *= __get_transform_scale();

    int x = radius - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - ((int) radius << 1);
    int * lined = (int *) calloc(2 * (int) radius + 1, sizeof(int));
    while(x >= y){
        if(lined[(int)(y + radius)] == 0){
            __raw_line(centerx + x, centery + y, centerx - x, centery + y, __fill);
            lined[(int)(y + radius)] = 1;
        }
        if(lined[(int)(-y + radius)] == 0){
            __raw_line(centerx + x, centery - y, centerx - x, centery - y, __fill);
            lined[(int)(-y + radius)] = 1;
        }
        if(lined[(int)(x + radius)] == 0){
            __raw_line(centerx + y, centery + x, centerx - y, centery + x, __fill);
            lined[(int)(x + radius)] = 1;
        }
        if(lined[(int)(-x + radius)] == 0){
            __raw_line(centerx - y, centery - x, centerx + y, centery - x, __fill);
            lined[(int)(-x + radius)] = 1;
        }
        /* 
        __raw_line(centerx + x, centery + y, centerx - x, centery + y);
        __raw_line(centerx + x, centery - y, centerx - x, centery - y);
        __raw_line(centerx + y, centery + x, centerx - y, centery + x);
        __raw_line(centerx - y, centery - x, centerx + y, centery - x);
         */
        if(err <= 0){
            y++;
            err += dy;
            dy += 2;
        }else{
            x--;
            dx += 2;
            err += dx - ((int) radius << 1);
        }
    }
    free(lined);
}



// void __draw_ellipse(double x0, double y0, double width, double height){
//     x0 = x0 - width / 2;
//     y0 = y0 - height / 2;

//     int x1 = x0 + width - 1, y1 = y0 + height - 1;
//     int a = xfabs(x1-x0), b = xfabs(y1-y0), b1 = b&1; /* values of diameter */
//     long dx = 4*(1-a)*b*b, dy = 4*(b1+1)*a*a; /* error increment */
//     long err = dx+dy+b1*a*a, e2; /* error of 1.step */

//     if (x0 > x1) { x0 = x1; x1 += a; } /* if called with swapped points */
//     if (y0 > y1) y0 = y1; /* .. exchange them */
//     y0 += (b+1)/2; y1 = y0-b1;   /* starting pixel */
//     a *= 8*a; b1 = 8*b*b;

//     do {
//         __point_scale(x1, y0, __stroke); /*   I. Quadrant */
//         __point_scale(x0, y0, __stroke); /*  II. Quadrant */
//         __point_scale(x0, y1, __stroke); /* III. Quadrant */
//         __point_scale(x1, y1, __stroke); /*  IV. Quadrant */
//         e2 = 2*err;
//         if (e2 <= dy) { y0++; y1--; err += dy += a; }  /* y step */
//         if (e2 >= dx || 2*err > dy) { x0++; x1--; err += dx += b1; } /* x step */
//     } while (x0 <= x1);

//     while (y0-y1 < b) {  /* too early stop of flat ellipses a=1 */
//         __point_scale((x0-1), (y0  ), __stroke); /* -> finish tip of ellipse */
//         __point_scale((x1+1), (y0++), __stroke);
//         __point_scale((x0-1), (y1  ), __stroke);
//         __point_scale((x1+1), (y1--), __stroke);
//     }
// }

void __draw_ellipse(double centerx, double centery, double width, double height) {
    double radius_x = width / 2;
    double radius_y = height / 2;
    int thickness = __thickness;
    // Definindo as coordenadas iniciais
    double x = 0;
    double y = radius_y;
    double d1 = (radius_y * radius_y) - (radius_x * radius_x * radius_y) + (0.25 * radius_x * radius_x);
    double dx = 2 * radius_y * radius_y * x;
    double dy = 2 * radius_x * radius_x * y;

    // Desenha a metade superior da elipse
    while (dx < dy) {
        for (int i = 0; i < thickness; i++) {
            __point_scale(centerx + x, centery + y + i, __stroke);
            __point_scale(centerx - x, centery + y + i, __stroke);
            __point_scale(centerx + x, centery - y - i, __stroke);
            __point_scale(centerx - x, centery - y - i, __stroke);

            __point_scale(centerx + x + i, centery + y, __stroke);
            __point_scale(centerx - x - i, centery + y, __stroke);
            __point_scale(centerx + x + i, centery - y, __stroke);
            __point_scale(centerx - x - i, centery - y, __stroke);
        }

        x++;
        dx += 2 * radius_y * radius_y;
        if (d1 < 0) {
            d1 += dx + radius_y * radius_y;
        } else {
            y--;
            dy -= 2 * radius_x * radius_x;
            d1 += dx - dy + radius_y * radius_y;
        }
    }

    // Desenha a metade inferior da elipse
    double d2 = ((radius_y * radius_y) * ((x + 0.5) * (x + 0.5))) +
                ((radius_x * radius_x) * ((y - 1) * (y - 1))) -
                (radius_x * radius_x * radius_y * radius_y);

    while (y >= 0) {
        for (int i = 0; i < thickness; i++) {
            __point_scale(centerx + x, centery + y + i, __stroke);
            __point_scale(centerx - x, centery + y + i, __stroke);
            __point_scale(centerx + x, centery - y - i, __stroke);
            __point_scale(centerx - x, centery - y - i, __stroke);

            __point_scale(centerx + x + i, centery + y, __stroke);
            __point_scale(centerx - x - i, centery + y, __stroke);
            __point_scale(centerx + x + i, centery - y, __stroke);
            __point_scale(centerx - x - i, centery - y, __stroke);
        }

        y--;
        dy -= 2 * radius_x * radius_x;
        if (d2 > 0) {
            d2 += radius_x * radius_x - dy;
        } else {
            x++;
            dx += 2 * radius_y * radius_y;
            d2 += dx - dy + radius_x * radius_x;
        }
    }
}

void __fill_ellipse(double x0, double y0, double width, double height){
    x0 -= width / 2;
    y0 -= height / 2;

    // V2d p0 = __transform(x0, y0);

    double ytop = y0;
    double x1 = x0 + width - 1, y1 = y0 + height - 1;
    double a = xfabs(x1-x0);
    double b = xfabs(y1-y0);
    int b1 = (int)b&1; /* values of diameter */
    double dx = 4*(1-a)*b*b, dy = 4*(b1+1)*a*a; /* error increment */
    double err = dx+dy+b1*a*a, e2; /* error of 1.step */

    if (x0 > x1) { x0 = x1; x1 += a; } /* if called with swapped points */
    if (y0 > y1) y0 = y1; /* .. exchange them */
    y0 += (b+1)/2; y1 = y0-b1;   /* starting pixel */
    a *= 8*a; b1 = 8*b*b;
    
    int * lined = (int *) calloc((int) (height + 1), sizeof(int));
    
    do {
        if(lined[xround(y0 - ytop)] == 0){
            __draw_line_scale(x1, y0, x0, y0, __fill); /*   I. Quadrant */
            lined[xround(y0 - ytop)] = 1;
        }
        if(lined[xround(y1 - ytop)] == 0){
            __draw_line_scale(x0, y1, x1, y1, __fill); /* III. Quadrant */
            lined[xround(y1 - ytop)] = 1;
        }
        e2 = 2*err;
        if (e2 <= dy) { y0++; y1--; err += dy += a; }  /* y step */
        if (e2 >= dx || 2*err > dy) { x0++; x1--; err += dx += b1; } /* x step */
    } while (x0 <= x1);

    while (y0-y1 < b) {  /* too early stop of flat ellipses a=1 */
        __point_scale((x0-1), (y0  ), __fill); /* -> finish tip of ellipse */
        __point_scale((x1+1), (y0++), __fill);
        __point_scale((x0-1), (y1  ), __fill);
        __point_scale((x1+1), (y1--), __fill);
    }
    free(lined);
}

void ellipse(double x0, double y0, double width, double height) {
    double s = __get_transform_scale();
    if (__fill_enable) {
        __fill_ellipse(x0 * s, y0 * s, width * s, height * s);
    }
    if (__stroke_enable) {
        __draw_ellipse(x0 * s, y0 * s, width * s, height * s);
    }
}

void circle(int x0, int y0, int diameter){
    if(__fill_enable){
        __fill_circle(x0, y0, diameter / 2);
    }
    if(__stroke_enable){
        double s = __get_transform_scale();
        __draw_ellipse(x0 * s, y0 * s, diameter * s, diameter * s);
    }
}

void __x_plot_quad_bezier_seg(int x0, int y0, int x1, int y1, int x2, int y2)
{
    int sx = x2-x1, sy = y2-y1;
    long xx = x0-x1, yy = y0-y1, xy;         /* relative values for checks */
    double dx, dy, err, cur = xx*sy-yy*sx;                    /* curvature */

    assert(xx*sx <= 0 && yy*sy <= 0);  /* sign of gradient must not change */

    if (sx*(long)sx+sy*(long)sy > xx*xx+yy*yy) { /* begin with longer part */
        x2 = x0; x0 = sx+x1; y2 = y0; y0 = sy+y1; cur = -cur;  /* swap P0 P2 */
    }
    if (cur != 0) {                                    /* no straight line */
        xx += sx; xx *= sx = x0 < x2 ? 1 : -1;           /* x step direction */
        yy += sy; yy *= sy = y0 < y2 ? 1 : -1;           /* y step direction */
        xy = 2*xx*yy; xx *= xx; yy *= yy;          /* differences 2nd degree */
        if (cur*sx*sy < 0) {                           /* negated curvature? */
            xx = -xx; yy = -yy; xy = -xy; cur = -cur;
        }
        dx = 4.0*sy*cur*(x1-x0)+xx-xy;             /* differences 1st degree */
        dy = 4.0*sx*cur*(y0-y1)+yy-xy;
        xx += xx; yy += yy; err = dx+dy+xy;                /* error 1st step */
        do {
            __point(x0,y0, __stroke);                                     /* plot curve */
            if (x0 == x2 && y0 == y2) return;  /* last pixel -> curve finished */
            y1 = 2*err < dx;                  /* save value for test of y step */
            if (2*err > dy) { x0 += sx; dx -= xy; err += dy += yy; } /* x step */
            if (    y1    ) { y0 += sy; dy -= xy; err += dx += xx; } /* y step */
        } while (dy < dx );           /* gradient negates -> algorithm fails */
    }
    __raw_line(x0, y0, x2, y2, __stroke);                  /* plot remaining part to end */
}
// void draw_bezier(int x0, int y0, int x1, int y1, int x2, int y2)
// {                                          /* plot any quadratic Bezier curve */
//     int x = x0-x1, y = y0-y1;
//     double t = x0-2*x1+x2, r;

//     if ((long)x*(x2-x1) > 0) {                        /* horizontal cut at P4? */
//         if ((long)y*(y2-y1) > 0)                     /* vertical cut at P6 too? */
//             if (xfabs((y0-2*y1+y2)/t*x) > abs(y)) {               /* which first? */
//                 x0 = x2; x2 = x+x1; y0 = y2; y2 = y+y1;            /* swap points */
//             }                            /* now horizontal cut at P4 comes first */
//         t = (x0-x1)/t;
//         r = (1-t)*((1-t)*y0+2.0*t*y1)+t*t*y2;                       /* By(t=P4) */
//         t = (x0*x2-x1*x1)*t/(x0-x1);                       /* gradient dP4/dx=0 */
//         x = xfloor(t+0.5); y = xfloor(r+0.5);
//         r = (y1-y0)*(t-x0)/(x1-x0)+y0;                  /* intersect P3 | P0 P1 */
//         __x_plot_quad_bezier_seg(x0,y0, x, xfloor(r+0.5), x,y);
//         r = (y1-y2)*(t-x2)/(x1-x2)+y2;                  /* intersect P4 | P1 P2 */
//         x0 = x1 = x; y0 = y; y1 = xfloor(r+0.5);             /* P0 = P4, P1 = P8 */
//     }
//     if ((long)(y0-y1)*(y2-y1) > 0) {                    /* vertical cut at P6? */
//         t = y0-2*y1+y2; t = (y0-y1)/t;
//         r = (1-t)*((1-t)*x0+2.0*t*x1)+t*t*x2;                       /* Bx(t=P6) */
//         t = (y0*y2-y1*y1)*t/(y0-y1);                       /* gradient dP6/dy=0 */
//         x = xfloor(r+0.5); y = xfloor(t+0.5);
//         r = (x1-x0)*(t-y0)/(y1-y0)+x0;                  /* intersect P6 | P0 P1 */
//         __x_plot_quad_bezier_seg(x0,y0, xfloor(r+0.5),y, x,y);
//         r = (x1-x2)*(t-y2)/(y1-y2)+x2;                  /* intersect P7 | P1 P2 */
//         x0 = x; x1 = xfloor(r+0.5); y0 = y1 = y;             /* P0 = P6, P1 = P7 */
//     }
//     __x_plot_quad_bezier_seg(x0,y0, x1,y1, x2,y2);                  /* remaining part */
// }

/* https://github.com/Jnmattern/Minimalist_2.0/blob/master/src/bitmap.h */
#define __TRIG_MAX (1<<24)
#define __TRIG_NORM(v) ((v)>>24)
#define __TRIG_MULT(v) ((v)<<24)

const int32_t __sinTable__[91] = {
    0, 292802, 585516, 878051, 1170319, 1462230, 1753696, 2044628, 2334937, 2624534, 2913332, 3201243, 3488179, 3774052,
    4058775, 4342263, 4624427, 4905183, 5184444, 5462127, 5738145, 6012416, 6284855, 6555380, 6823908, 7090357, 7354647,
    7616696, 7876425, 8133755, 8388607, 8640905, 8890569, 9137526, 9381700, 9623015, 9861400, 10096780, 10329085, 10558244,
    10784186, 11006844, 11226148, 11442033, 11654433, 11863283, 12068519, 12270079, 12467901, 12661925, 12852093, 13038345,
    13220626, 13398880, 13573052, 13743090, 13908942, 14070557, 14227886, 14380880, 14529495, 14673683, 14813402, 14948608,
    15079261, 15205321, 15326749, 15443508, 15555563, 15662880, 15765426, 15863169, 15956080, 16044131, 16127295, 16205546,
    16278860, 16347217, 16410593, 16468971, 16522332, 16570660, 16613941, 16652161, 16685308, 16713373, 16736347, 16754223,
    16766995, 16774660, 16777216
};

static double __SIN(double value) {
    // return sin(value);
    int d = (int)value%360;
    if (d < 90) {
        return __sinTable__[d];
    } else if (d < 180) {
        return __sinTable__[180-d];
    } else if (d < 270) {
        return -__sinTable__[d-180];
    } else {
        return -__sinTable__[360-d];
    }
}

static double __COS(double value) {
    // return cos(value);
    int d = (int)value%360;
    if (d < 90) {
        return __sinTable__[90-d];
    } else if (d < 180) {
        return -__sinTable__[d-90];
    } else if (d < 270) {
        return -__sinTable__[270-d];
    } else {
        return __sinTable__[d-270];
    }
}

/* begin should be smaller than end, and both must be in interval [0, 360] */
void __x_fill_arc(double centerx, double centery, int diameter, int thickness, int degrees_begin, int degrees_end, Color color) {
    double radius = diameter / 2;
    V2d center = {centerx, centery};
    double sslope = (double)__COS(degrees_begin) / (double)__SIN(degrees_begin);
    double eslope = (double)__COS(degrees_end) / (double)__SIN(degrees_end);

    if (degrees_end == 360) eslope = -1000000;

    int ir2 = (radius - thickness) * (radius - thickness);
    int or2 = radius * radius;
    int x, y;

    for (x = -radius; x <= radius; x++) {
        for (y = -radius; y <= radius; y++)
        {
            int x2 = x * x;
            int y2 = y * y;

            if (
                    (x2 + y2 < or2 && x2 + y2 >= ir2) && (
                            (y > 0 && degrees_begin < 180 && x <= y * sslope) ||
                            (y < 0 && degrees_begin > 180 && x >= y * sslope) ||
                            (y < 0 && degrees_begin <= 180) ||
                            (y == 0 && degrees_begin <= 180 && x < 0) ||
                            (y == 0 && degrees_begin == 0 && x > 0)
                    ) && (
                            (y > 0 && degrees_end < 180 && x >= y * eslope) ||
                            (y < 0 && degrees_end > 180 && x <= y * eslope) ||
                            (y > 0 && degrees_end >= 180) ||
                            (y == 0 && degrees_end >= 180 && x < 0) ||
                            (y == 0 && degrees_begin == 0 && x > 0)
                    )
                    )
                __point(center.x+x, center.y-y, color);
        }
    }

}

void __arc(double centerx, double centery, int diameter, int thickness, int degrees_begin, int degrees_lenght, Color color){
    if(degrees_lenght % 360 == 0)
        degrees_lenght = 360;
    else
        degrees_lenght %= 360;
    if(degrees_lenght < 0){
        degrees_lenght *= -1;
        degrees_begin -= degrees_lenght;
    }
    degrees_begin %= 360;
    if(degrees_begin < 0)
        degrees_begin += 360;
    int degrees_end = degrees_begin + degrees_lenght;

    if(degrees_end <= 360){
        __x_fill_arc(centerx, centery, diameter, thickness, degrees_begin, degrees_end, color);
    }else{
        __x_fill_arc(centerx, centery, diameter, thickness, degrees_begin, 360, color);
        __x_fill_arc(centerx, centery, diameter, thickness, 0, degrees_end - 360, color);
    }
}


void arc(double centerx, double centery, int out_diameter, int in_diameter, int degrees_begin, int degrees_lenght) {
    double thickness = in_diameter / 2.0;
    if (thickness < 0) {
        thickness = 0;
    }
    if (thickness > out_diameter / 2.0) {
        thickness = out_diameter / 2.0;
    }
    
    if (__fill_enable) {
        __arc(centerx, centery, out_diameter, thickness, degrees_begin, degrees_lenght, __fill);
    }
    if (__stroke_enable) {
        __arc(centerx, centery, out_diameter, __thickness, degrees_begin, degrees_lenght, __stroke);
        __arc(centerx, centery, out_diameter - 2 *  thickness, __thickness, degrees_begin, degrees_lenght, __stroke);

        //draw a line from begin __point to end __point
        //convert degrees to radians
        double r = out_diameter / 2.0;
        {
            double c = xcos(degrees_begin);
            double s = xsin(degrees_begin);
            double x0 = centerx + r * c;
            double y0 = centery - r * s;
            double x1 = centerx + (r - thickness) * c;
            double y1 = centery - (r - thickness) * s;
            line(x0, y0, x1, y1);
        }
        {
            double c = xcos(degrees_begin + degrees_lenght);
            double s = xsin(degrees_begin + degrees_lenght);
            double x0 = centerx + r * c;
            double y0 = centery - r * s;
            double x1 = centerx + (r - thickness) * c;
            double y1 = centery - (r - thickness) * s;
            line(x0, y0, x1, y1);
        }
    }
}

//returns fractional part of a number
double __m_fractional (double x) {
    return x > 0 ? x - (int) x : x - ((int) x + 1);
}

//returns 1 - fractional part of number
double __r_fractional(double x) {
	return 1 - __m_fractional(x);
}

// draws a pixel on screen of given brightness
// 0<=brightness<=1. We can use your own library
// to draw on screen
void __plot_raw_bright_pixel(double x , double y , Color color, double brightness)
{
    color.r = color.r * brightness;
    color.g = color.g * brightness;
    color.b = color.b * brightness;
    color.a = color.a * brightness;

    __plot(x, y, color);
}

void __raw_alias_line(double x0 , double y0 , double x1 , double y1, Color color) {
	int steep = xfabs(y1 - y0) > xfabs(x1 - x0) ;

	// swap the co-ordinates if slope > 1 or we
	// draw backwards
	if (steep) {
        X_SWAP(x0, y0, double);
        X_SWAP(x1, y1, double);
	}
	if (x0 > x1) {
        X_SWAP(x0, x1, double);
        X_SWAP(y0, y1, double);
	}

	//compute the slope
	double dx = x1-x0;
	double dy = y1-y0;
	double gradient = dy/dx;
	if (dx == 0.0)
		gradient = 1;

	int xpxl1 = x0;
	int xpxl2 = x1;
	double intersectY = y0;

	// main loop
	if (steep) {
		for (int x = xpxl1 ; x <=xpxl2 ; x++) {
			// pixel coverage is determined by fractional
			// part of y co-ordinate
			__plot_raw_bright_pixel(intersectY    , x, color, __r_fractional(intersectY));
			__plot_raw_bright_pixel(intersectY + 1, x, color, __m_fractional(intersectY));
			intersectY += gradient;
		}
	} else {
		for (int x = xpxl1 ; x <=xpxl2 ; x++) {
			// pixel coverage is determined by fractional
			// part of y co-ordinate
			__plot_raw_bright_pixel(x, intersectY    , color, __r_fractional(intersectY));
			__plot_raw_bright_pixel(x, intersectY + 1, color, __m_fractional(intersectY));
			intersectY += gradient;
		}
	}
}


void __draw_line(double x0 , double y0 , double x1 , double y1, Color color) {
    V2d origin = __transform(x0, y0);
    V2d destiny = __transform(x1, y1);
    x0 = origin.x;
    y0 = origin.y;
    x1 = destiny.x;
    y1 = destiny.y;
    __raw_alias_line(x0, y0, x1, y1, color);
}

void __draw_line_scale(double x0 , double y0 , double x1 , double y1, Color color) {
    double s = __get_transform_scale();
    V2d origin = __transform(x0/s, y0/s);
    V2d destiny = __transform(x1/s, y1/s);
    x0 = origin.x;
    y0 = origin.y;
    x1 = destiny.x;
    y1 = destiny.y;
    __raw_alias_line(x0, y0, x1, y1, color);
}

void line(double x0 , double y0 , double x1 , double y1) {
    if (__thickness == 1) {
        __draw_line(x0, y0, x1, y1, __stroke);
        return;
    }
    __fill_line(x0, y0, x1, y1, __thickness, __stroke);
}

double calculateBezierPoint(double p0, double p1, double p2, double p3, double t) {
    return p0 * (1 - t) * (1 - t) * (1 - t) + 3 * p1 * t * (1 - t) * (1 - t) + 3 * p2 * t * t * (1 - t) + p3 * t * t * t;
}

// Função para desenhar uma curva de Bezier de grau 3
// void bezier(double xa, double ya, double xb, double yb, double xc, double yc, double xd, double yd) {
//     // Número de segmentos
//     int numSegments = 100;
//     double increment = 1.0 / numSegments;

//     // Desenha a curva de Bezier com triângulos
//     for (int i = 0; i < numSegments; ++i) {
//         double t0 = i * increment;
//         double t1 = (i + 1) * increment;

//         double x0 = calculateBezierPoint(xa, xb, xc, xd, t0);
//         double y0 = calculateBezierPoint(ya, yb, yc, yd, t0);
//         double x1 = calculateBezierPoint(xa, xb, xc, xd, t1);
//         double y1 = calculateBezierPoint(ya, yb, yc, yd, t1);

//         __fill_raw_triangle(x0, y0, x1, y1, x1, y1, __stroke); // desenha um triângulo com vértices coincidentes
//     }
// }

void __fill_triangle_scale(double v1x, double v1y, double v2x, double v2y, double v3x, double v3y, Color color) {
    double s = __get_transform_scale();
    V2d v1 = __transform(v1x/s, v1y/s);
    V2d v2 = __transform(v2x/s, v2y/s);
    V2d v3 = __transform(v3x/s, v3y/s);
    v1x = v1.x;
    v1y = v1.y;
    v2x = v2.x;
    v2y = v2.y;
    v3x = v3.x;
    v3y = v3.y;
    __fill_raw_triangle(v1x, v1y, v2x, v2y, v3x, v3y, color);
}

void __bezier(double xa, double ya, double xb, double yb, double xc, double yc, double xd, double yd) {
    int thickness = __thickness;
    // Número de segmentos
    int numSegments = 100;
    double increment = 1.0 / numSegments;

    // Desenha a curva de Bezier com espessura
    for (int i = 0; i < numSegments; ++i) {
        double t0 = i * increment;
        double t1 = (i + 1) * increment;

        double x0 = calculateBezierPoint(xa, xb, xc, xd, t0);
        double y0 = calculateBezierPoint(ya, yb, yc, yd, t0);
        double x1 = calculateBezierPoint(xa, xb, xc, xd, t1);
        double y1 = calculateBezierPoint(ya, yb, yc, yd, t1);

        // Calcula os vetores normalizados
        double dx = x1 - x0;
        double dy = y1 - y0;
        double length = xsqrt(dx * dx + dy * dy);
        if (length != 0) {
            dx /= length;
            dy /= length;
        }

        // Calcula os vetores perpendiculares
        double vx = -dy;
        double vy = dx;

        // Calcula os vértices dos triângulos
        double x2 = x0 + vx * thickness;
        double y2 = y0 + vy * thickness;
        double x3 = x1 + vx * thickness;
        double y3 = y1 + vy * thickness;
        double x4 = x1 - vx * thickness;
        double y4 = y1 - vy * thickness;
        double x5 = x0 - vx * thickness;
        double y5 = y0 - vy * thickness;

        // Desenha os triângulos formados pelos vértices
        __fill_triangle_scale(x0, y0, x1, y1, x2, y2, __stroke);
        __fill_triangle_scale(x1, y1, x2, y2, x3, y3, __stroke);
        __fill_triangle_scale(x1, y1, x3, y3, x4, y4, __stroke);
        __fill_triangle_scale(x0, y0, x5, y5, x4, y4, __stroke);
        __fill_triangle_scale(x0, y0, x5, y5, x1, y1, __stroke);
    }
}

void bezier(double xa, double ya, double xb, double yb, double xc, double yc, double xd, double yd) {
    double s = __get_transform_scale();
    if (__fill_enable) {
        __bezier(xa * s, ya * s, xb * s, yb * s, xc * s, yc * s, xd * s, yd * s);
    }
}

