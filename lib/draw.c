#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "draw.h" /*XDDDX*/
#include "xmath.h" /*XDDDX*/
#include "base.h" /*XDDDX*/

void x_plot(int x, int y);
void __x_make_layer(void);
void __x_merge_layer(void);

void __x_draw_block(int x, int y, int side){
    for(int i = x; i < x + side; i++)
        for(int j = y; j < y + side; j++)
            x_plot(i, j);
}

int x_draw_art(int x, int y, int zoom, const char * picture){
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
            __x_draw_block(x + dx * zoom, y + dy * zoom, zoom);
            dx += 1;
            maxdx = dx > maxdx ? dx : maxdx;
        }else{
            x_color_load(picture[i]);
            __x_draw_block(x + dx * zoom, y + dy * zoom, zoom);
            dx += 1;
            maxdx = dx > maxdx ? dx : maxdx;
        }
    }
    return (maxdx + 1) * zoom;
}

void x_draw_line(int x0, int y0, int x1, int y1){
    /* Bresenham's Line Algorithm */
    int dx = (x0 > x1) ? x0 - x1 : x1 - x0;
    int dy = (y0 > y1) ? y0 - y1 : y1 - y0;
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        x_plot(x0, y0);
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

void __x_fill_bottom_flat_triangle(float v1x, float v1y, float v2x, float v2y, float v3x, float v3y)
{
    float invslope1 = ((int)v2x - (int)v1x) / (float)((int)v2y - (int)v1y);
    float invslope2 = ((int)v3x - (int)v1x) / (float)((int)v3y - (int)v1y);

    float curx1 = v1x;
    float curx2 = v1x;
    int scanlineY;

    for (scanlineY = v1y; scanlineY <= (int)v2y; scanlineY++){
        x_draw_line(curx1, scanlineY, curx2, scanlineY);
        curx1 += invslope1;
        curx2 += invslope2;
    }
}

void __x_fill_top_flat_triangle(float v1x, float v1y, float v2x, float v2y, float v3x, float v3y)
{
    float invslope1 = ((int)v3x - (int)v1x) / (float)((int)v3y - (int)v1y);
    float invslope2 = ((int)v3x - (int)v2x) / (float)((int)v3y - (int)v2y);

    float curx1 = v3x;
    float curx2 = v3x;

    int scanlineY;

    for (scanlineY = v3y; scanlineY >= v1y; scanlineY--)
    {
        x_draw_line(curx1, scanlineY, curx2, scanlineY);
        curx1 -= invslope1;
        curx2 -= invslope2;
    }
}

void x_fill_triangle(float v1x, float v1y, float v2x, float v2y, float v3x, float v3y)
{
    __x_make_layer();
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
        __x_fill_bottom_flat_triangle(v1.x, v1.y, v2.x, v2.y, v3.x, v3.y);
    else if (v1.y == v2.y)
        __x_fill_top_flat_triangle(v1.x, v1.y, v2.x, v2.y, v3.x, v3.y);
    else
    {
        /* general case - split the triangle in a topflat and bottom-flat one */
        V2d v4 = {0.f, 0.f};
        v4.x = (v1.x + ((float)(v2.y - v1.y) / (float)(v3.y - v1.y)) * (v3.x - v1.x));
        v4.y = v2.y;
        __x_fill_bottom_flat_triangle(v1.x, v1.y, v2.x, v2.y, v4.x, v4.y);
        __x_fill_top_flat_triangle(v2.x, v2.y, v4.x, v4.y, v3.x, v3.y);
    }
    __x_merge_layer();
}

void x_fill_line(float x0, float y0, float x1, float y1, int thickness){
    V2d a = {x0, y0};
    V2d b = {x1, y1};
    if(thickness == 1){
        x_draw_line(a.x, a.y, b.x, b.y);
        return;
    }
    __x_make_layer();
    V2d _offset = x_v2d_make(b.x - a.x, b.y - a.y);
    _offset = x_v2d_dot(x_v2d_ortho(x_v2d_normalize(_offset)), (thickness / 2.f));

    V2d p1 = x_v2d_sub(a, _offset);
    V2d p2 = x_v2d_sub(b, _offset);
    V2d p3 = x_v2d_sum(a, _offset);
    V2d p4 = x_v2d_sum(b, _offset);

    x_fill_triangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
    x_fill_triangle(p3.x, p3.y, p2.x, p2.y, p4.x, p4.y);
    __x_merge_layer();
}

void x_fill_rect(int x0, int y0, int width, int height){
    int i, x1 = x0 + width - 1, y1 = y0 + height - 1;
    for(i = x0; i <= x1; i++)
        x_draw_line(i, y0, i, y1);
}

/* https://en.wikipedia.org/wiki/Midpoint_circle_algorithm */
void x_draw_circle(int centerx, int centery, int radius){
    int x = radius - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);
    while(x >= y){
        x_plot(centerx + x, centery + y);
        x_plot(centerx - x, centery + y);
        x_plot(centerx + x, centery - y);
        x_plot(centerx - x, centery - y);
        x_plot(centerx + y, centery + x);
        x_plot(centerx - y, centery + x);
        x_plot(centerx - y, centery - x);
        x_plot(centerx + y, centery - x);

        if(err <= 0){
            y++;
            err += dy;
            dy += 2;
        }else{
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}

void x_fill_circle(int centerx, int centery, int radius){
    int x = radius - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);
    int * lined = (int *) calloc(2 * radius, sizeof(int));
    while(x >= y){
        if(lined[y + radius] == 0){
            x_draw_line(centerx + x, centery + y, centerx - x, centery + y);
            lined[y + radius] = 1;
        }
        if(lined[-y + radius] == 0){
            x_draw_line(centerx + x, centery - y, centerx - x, centery - y);
            lined[-y + radius] = 1;
        }
        if(lined[x + radius] == 0){
            x_draw_line(centerx + y, centery + x, centerx - y, centery + x);
            lined[x + radius] = 1;
        }
        if(lined[-x + radius] == 0){
            x_draw_line(centerx - y, centery - x, centerx + y, centery - x);
            lined[-x + radius] = 1;
        }
        /* 
        x_draw_line(centerx + x, centery + y, centerx - x, centery + y);
        x_draw_line(centerx + x, centery - y, centerx - x, centery - y);
        x_draw_line(centerx + y, centery + x, centerx - y, centery + x);
        x_draw_line(centerx - y, centery - x, centerx + y, centery - x);
         */
        if(err <= 0){
            y++;
            err += dy;
            dy += 2;
        }else{
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
    free(lined);
}

void x_draw_ellipse(int x0, int y0, int width, int height){
    int x1 = x0 + width - 1, y1 = y0 + height - 1;
    int a = abs(x1-x0), b = abs(y1-y0), b1 = b&1; /* values of diameter */
    long dx = 4*(1-a)*b*b, dy = 4*(b1+1)*a*a; /* error increment */
    long err = dx+dy+b1*a*a, e2; /* error of 1.step */

    if (x0 > x1) { x0 = x1; x1 += a; } /* if called with swapped points */
    if (y0 > y1) y0 = y1; /* .. exchange them */
    y0 += (b+1)/2; y1 = y0-b1;   /* starting pixel */
    a *= 8*a; b1 = 8*b*b;

    do {
        x_plot(x1, y0); /*   I. Quadrant */
        x_plot(x0, y0); /*  II. Quadrant */
        x_plot(x0, y1); /* III. Quadrant */
        x_plot(x1, y1); /*  IV. Quadrant */
        e2 = 2*err;
        if (e2 <= dy) { y0++; y1--; err += dy += a; }  /* y step */
        if (e2 >= dx || 2*err > dy) { x0++; x1--; err += dx += b1; } /* x step */
    } while (x0 <= x1);

    while (y0-y1 < b) {  /* too early stop of flat ellipses a=1 */
        x_plot(x0-1, y0); /* -> finish tip of ellipse */
        x_plot(x1+1, y0++);
        x_plot(x0-1, y1);
        x_plot(x1+1, y1--);
    }
}

void x_fill_ellipse(int x0, int y0, int width, int height){
    int ytop = y0;
    int x1 = x0 + width - 1, y1 = y0 + height - 1;
    int a = abs(x1-x0), b = abs(y1-y0), b1 = b&1; /* values of diameter */
    long dx = 4*(1-a)*b*b, dy = 4*(b1+1)*a*a; /* error increment */
    long err = dx+dy+b1*a*a, e2; /* error of 1.step */

    if (x0 > x1) { x0 = x1; x1 += a; } /* if called with swapped points */
    if (y0 > y1) y0 = y1; /* .. exchange them */
    y0 += (b+1)/2; y1 = y0-b1;   /* starting pixel */
    a *= 8*a; b1 = 8*b*b;
    
    int * lined = (int *) calloc(height, sizeof(int));
    
    do {
        if(lined[y0 - ytop] == 0){
            x_draw_line(x1, y0, x0, y0); /*   I. Quadrant */
            lined[y0 - ytop] = 1;
        }
        if(lined[y1 - ytop] == 0){
            x_draw_line(x0, y1, x1, y1); /* III. Quadrant */
            lined[y1 - ytop] = 1;
        }
        e2 = 2*err;
        if (e2 <= dy) { y0++; y1--; err += dy += a; }  /* y step */
        if (e2 >= dx || 2*err > dy) { x0++; x1--; err += dx += b1; } /* x step */
    } while (x0 <= x1);

    while (y0-y1 < b) {  /* too early stop of flat ellipses a=1 */
        x_plot(x0-1, y0); /* -> finish tip of ellipse */
        x_plot(x1+1, y0++);
        x_plot(x0-1, y1);
        x_plot(x1+1, y1--);
    }
    free(lined);
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
            x_plot(x0,y0);                                     /* plot curve */
            if (x0 == x2 && y0 == y2) return;  /* last pixel -> curve finished */
            y1 = 2*err < dx;                  /* save value for test of y step */
            if (2*err > dy) { x0 += sx; dx -= xy; err += dy += yy; } /* x step */
            if (    y1    ) { y0 += sy; dy -= xy; err += dx += xx; } /* y step */
        } while (dy < dx );           /* gradient negates -> algorithm fails */
    }
    x_draw_line(x0, y0, x2, y2);                  /* plot remaining part to end */
}
void x_draw_bezier(int x0, int y0, int x1, int y1, int x2, int y2)
{                                          /* plot any quadratic Bezier curve */
    int x = x0-x1, y = y0-y1;
    double t = x0-2*x1+x2, r;

    if ((long)x*(x2-x1) > 0) {                        /* horizontal cut at P4? */
        if ((long)y*(y2-y1) > 0)                     /* vertical cut at P6 too? */
            if (x_math_fabs((y0-2*y1+y2)/t*x) > abs(y)) {               /* which first? */
                x0 = x2; x2 = x+x1; y0 = y2; y2 = y+y1;            /* swap points */
            }                            /* now horizontal cut at P4 comes first */
        t = (x0-x1)/t;
        r = (1-t)*((1-t)*y0+2.0*t*y1)+t*t*y2;                       /* By(t=P4) */
        t = (x0*x2-x1*x1)*t/(x0-x1);                       /* gradient dP4/dx=0 */
        x = x_math_floor(t+0.5); y = x_math_floor(r+0.5);
        r = (y1-y0)*(t-x0)/(x1-x0)+y0;                  /* intersect P3 | P0 P1 */
        __x_plot_quad_bezier_seg(x0,y0, x,x_math_floor(r+0.5), x,y);
        r = (y1-y2)*(t-x2)/(x1-x2)+y2;                  /* intersect P4 | P1 P2 */
        x0 = x1 = x; y0 = y; y1 = x_math_floor(r+0.5);             /* P0 = P4, P1 = P8 */
    }
    if ((long)(y0-y1)*(y2-y1) > 0) {                    /* vertical cut at P6? */
        t = y0-2*y1+y2; t = (y0-y1)/t;
        r = (1-t)*((1-t)*x0+2.0*t*x1)+t*t*x2;                       /* Bx(t=P6) */
        t = (y0*y2-y1*y1)*t/(y0-y1);                       /* gradient dP6/dy=0 */
        x = x_math_floor(r+0.5); y = x_math_floor(t+0.5);
        r = (x1-x0)*(t-y0)/(y1-y0)+x0;                  /* intersect P6 | P0 P1 */
        __x_plot_quad_bezier_seg(x0,y0, x_math_floor(r+0.5),y, x,y);
        r = (x1-x2)*(t-y2)/(y1-y2)+x2;                  /* intersect P7 | P1 P2 */
        x0 = x; x1 = x_math_floor(r+0.5); y0 = y1 = y;             /* P0 = P6, P1 = P7 */
    }
    __x_plot_quad_bezier_seg(x0,y0, x1,y1, x2,y2);                  /* remaining part */
}

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

static int32_t __SIN(int d) {
    d = d%360;
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

static int32_t __COS(int d) {
    d = d%360;
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
void __x_fill_arc(float centerx, float centery, int radius, int thickness, int degrees_begin, int degrees_end) {
    V2d center = {centerx, centery};
    float sslope = (float)__COS(degrees_begin) / (float)__SIN(degrees_begin);
    float eslope = (float)__COS(degrees_end) / (float)__SIN(degrees_end);

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
                x_plot(center.x+x, center.y-y);
        }
    }

}

void x_fill_arc(float centerx, float centery, int radius, int thickness, int degrees_begin, int degrees_lenght){
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
        __x_fill_arc(centerx, centery, radius, thickness, degrees_begin, degrees_end);
    }else{
        __x_fill_arc(centerx, centery, radius, thickness, degrees_begin, 360);
        __x_fill_arc(centerx, centery, radius, thickness, 0, degrees_end - 360);
    }
}

