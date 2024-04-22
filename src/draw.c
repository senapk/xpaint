#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

#include "draw.h" /*XDDDX*/
#include "xmath.h" /*XDDDX*/
#include "base.h" /*XDDDX*/

static Color     __stroke;
static Color     __fill;

static bool      __stroke_enable = true;
static bool      __fill_enable = true;
static int       __thickness = 1;

void __raw_line(int x0 , int y0 , int x1 , int y1, Color color);

void __plot_block(int x, int y, int side, Color color){
    for(int i = x; i < x + side; i++)
        for(int j = y; j < y + side; j++)
            plot(i, j, color);
}

void stroke_weight(int thickness){
    __thickness = thickness;
}


void point(double x, double y, Color color){
    V2d p = __transform(x, y);
    plot((int) p.x, (int) p.y, color);
}

void __point_scale(double x, double y, Color color){
    double s = __get_transform_scale();
    V2d p = __transform(x/s, y/s);
    plot((int) p.x, (int) p.y, color);
}

void stroke(Color color){
    __stroke = color;
    __stroke_enable = true;
}

void stroke_rgba(uchar r, uchar g, uchar b, uchar a) {
    __stroke.r = r;
    __stroke.g = g;
    __stroke.b = b;
    __stroke.a = a;
    __stroke_enable = true;
}

void stroke_char(char c){
    __stroke = get_palette(c);
    __stroke_enable = true;
}

void fill(Color color){
    __fill = color;
    __fill_enable = true;
}

void fill_rgba(uchar r, uchar g, uchar b, uchar a) {
    __fill_enable = true;
    __fill.r = r;
    __fill.g = g;
    __fill.b = b;
    __fill.a = a;
}

void fill_char(char c){
    __fill = get_palette(c);
    __fill_enable = true;
}

void no_stroke(){
    __stroke_enable = false;
}

void no_fill(){
    __fill_enable = false;
}


Color get_stroke(){
    return __stroke;
}

Color get_fill(){
    return __fill;
}

void __x_draw_block(int x, int y, int side, Color color){
    for(int i = x; i < x + side; i++)
        for(int j = y; j < y + side; j++)
            point(i, j, color);
}

int draw_art(int x, int y, int zoom, const char * picture){
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
            __x_draw_block(x + dx * zoom, y + dy * zoom, zoom, get_palette(picture[i]));
            dx += 1;
            maxdx = dx > maxdx ? dx : maxdx;
        }
    }
    return (maxdx + 1) * zoom;
}

void __raw_sline(int x0, int y0, int x1, int y1) {
    /* Bresenham's Line Algorithm */
    int dx = (x0 > x1) ? x0 - x1 : x1 - x0;
    int dy = (y0 > y1) ? y0 - y1 : y1 - y0;
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        plot(x0, y0, __fill);
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

void __x_fill_bottom_flat_triangle(double v1x, double v1y, double v2x, double v2y, double v3x, double v3y)
{
    double invslope1 = ((int)v2x - (int)v1x) / (double)((int)v2y - (int)v1y);
    double invslope2 = ((int)v3x - (int)v1x) / (double)((int)v3y - (int)v1y);

    double curx1 = v1x;
    double curx2 = v1x;
    int scanlineY;

    for (scanlineY = v1y; scanlineY <= (int)v2y; scanlineY++){
        __raw_sline(curx1, scanlineY, curx2, scanlineY);
        curx1 += invslope1;
        curx2 += invslope2;
    }
}

void __x_fill_top_flat_triangle(double v1x, double v1y, double v2x, double v2y, double v3x, double v3y)
{
    double invslope1 = ((int)v3x - (int)v1x) / (double)((int)v3y - (int)v1y);
    double invslope2 = ((int)v3x - (int)v2x) / (double)((int)v3y - (int)v2y);

    double curx1 = v3x;
    double curx2 = v3x;

    int scanlineY;

    for (scanlineY = v3y; scanlineY >= v1y; scanlineY--)
    {
        __raw_sline(curx1, scanlineY, curx2, scanlineY);
        curx1 -= invslope1;
        curx2 -= invslope2;
    }
}

void raw_fill_triangle(double v1x, double v1y, double v2x, double v2y, double v3x, double v3y)
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
        __x_fill_bottom_flat_triangle(v1.x, v1.y, v2.x, v2.y, v3.x, v3.y);
    else if (v1.y == v2.y)
        __x_fill_top_flat_triangle(v1.x, v1.y, v2.x, v2.y, v3.x, v3.y);
    else
    {
        /* general case - split the triangle in a topflat and bottom-flat one */
        V2d v4 = {0.f, 0.f};
        v4.x = (v1.x + ((double)(v2.y - v1.y) / (double)(v3.y - v1.y)) * (v3.x - v1.x));
        v4.y = v2.y;
        __x_fill_bottom_flat_triangle(v1.x, v1.y, v2.x, v2.y, v4.x, v4.y);
        __x_fill_top_flat_triangle(v2.x, v2.y, v4.x, v4.y, v3.x, v3.y);
    }
}

void __fill_line(double x0, double y0, double x1, double y1, int thickness){
    V2d c0 = __transform(x0, y0);
    V2d c1 = __transform(x1, y1);
    V2d a = {c0.x, c0.y};
    V2d b = {c1.x, c1.y};

    V2d _offset = make_v2d(b.x - a.x, b.y - a.y);
    _offset = v2d_dot(v2d_ortho(v2d_normalize(_offset)), (thickness / 2.f));

    V2d p1 = v2d_sub(a, _offset);
    V2d p2 = v2d_sub(b, _offset);
    V2d p3 = v2d_sum(a, _offset);
    V2d p4 = v2d_sum(b, _offset);

    raw_fill_triangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
    raw_fill_triangle(p3.x, p3.y, p2.x, p2.y, p4.x, p4.y);
}

void __fill_rect(double x0, double y0, double width, double height){
    V2d p0 = __transform(x0, y0);
    V2d p1 = __transform(x0 + width, y0);
    V2d p2 = __transform(x0 + width, y0 + height);
    V2d p3 = __transform(x0, y0 + height);

    raw_fill_triangle(p0.x, p0.y, p1.x, p1.y, p2.x, p2.y);
    raw_fill_triangle(p0.x, p0.y, p2.x, p2.y, p3.x, p3.y);
}

void rect(double x, double y, double witdh, double height) {
    if (__fill_enable) {
        __fill_rect(x, y, witdh, height);
    }
    if (__stroke_enable) {
        double s = __get_transform_scale();
        __fill_line(x, y, x + witdh * s, y, __thickness);
        __fill_line(x + witdh * s, y, x + witdh * s, y + height * s, __thickness);
        __fill_line(x + witdh * s, y + height * s, x, y + height * s, __thickness);
        __fill_line(x, y + height * s, x, y, __thickness);
    }

}

/* https://en.wikipedia.org/wiki/Midpoint_circle_algorithm */
void __draw_circle(double centerx, double centery, double radius){
    int x = radius - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - ((int) radius << 1);
    while(x >= y){
        __point_scale((centerx + x), (centery + y), __stroke);
        __point_scale((centerx - x), (centery + y), __stroke);
        __point_scale((centerx + x), (centery - y), __stroke);
        __point_scale((centerx - x), (centery - y), __stroke);
        __point_scale((centerx + y), (centery + x), __stroke);
        __point_scale((centerx - y), (centery + x), __stroke);
        __point_scale((centerx - y), (centery - x), __stroke);
        __point_scale((centerx + y), (centery - x), __stroke);

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
}

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
    int * lined = (int *) calloc(2 * radius, sizeof(int));
    while(x >= y){
        if(lined[(int)(y + radius)] == 0){
            __raw_sline(centerx + x, centery + y, centerx - x, centery + y);
            lined[(int)(y + radius)] = 1;
        }
        if(lined[(int)(-y + radius)] == 0){
            __raw_sline(centerx + x, centery - y, centerx - x, centery - y);
            lined[(int)(-y + radius)] = 1;
        }
        if(lined[(int)(x + radius)] == 0){
            __raw_sline(centerx + y, centery + x, centerx - y, centery + x);
            lined[(int)(x + radius)] = 1;
        }
        if(lined[(int)(-x + radius)] == 0){
            __raw_sline(centerx - y, centery - x, centerx + y, centery - x);
            lined[(int)(-x + radius)] = 1;
        }
        /* 
        __raw_sline(centerx + x, centery + y, centerx - x, centery + y);
        __raw_sline(centerx + x, centery - y, centerx - x, centery - y);
        __raw_sline(centerx + y, centery + x, centerx - y, centery + x);
        __raw_sline(centerx - y, centery - x, centerx + y, centery - x);
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

void circle(int x0, int y0, int radius){
    if(__fill_enable){
        __fill_circle(x0, y0, radius);
    }
    if(__stroke_enable){
        double s = __get_transform_scale();
        __draw_circle(x0 * s, y0 * s, radius * s);
    }
}

void __draw_ellipse(double x0, double y0, double width, double height){
    x0 = x0 - width / 2;
    y0 = y0 - height / 2;

    int x1 = x0 + width - 1, y1 = y0 + height - 1;
    int a = math_fabs(x1-x0), b = math_fabs(y1-y0), b1 = b&1; /* values of diameter */
    long dx = 4*(1-a)*b*b, dy = 4*(b1+1)*a*a; /* error increment */
    long err = dx+dy+b1*a*a, e2; /* error of 1.step */

    if (x0 > x1) { x0 = x1; x1 += a; } /* if called with swapped points */
    if (y0 > y1) y0 = y1; /* .. exchange them */
    y0 += (b+1)/2; y1 = y0-b1;   /* starting pixel */
    a *= 8*a; b1 = 8*b*b;

    do {
        __point_scale(x1, y0, __stroke); /*   I. Quadrant */
        __point_scale(x0, y0, __stroke); /*  II. Quadrant */
        __point_scale(x0, y1, __stroke); /* III. Quadrant */
        __point_scale(x1, y1, __stroke); /*  IV. Quadrant */
        e2 = 2*err;
        if (e2 <= dy) { y0++; y1--; err += dy += a; }  /* y step */
        if (e2 >= dx || 2*err > dy) { x0++; x1--; err += dx += b1; } /* x step */
    } while (x0 <= x1);

    while (y0-y1 < b) {  /* too early stop of flat ellipses a=1 */
        __point_scale((x0-1), (y0  ), __stroke); /* -> finish tip of ellipse */
        __point_scale((x1+1), (y0++), __stroke);
        __point_scale((x0-1), (y1  ), __stroke);
        __point_scale((x1+1), (y1--), __stroke);
    }
}

void __fill_ellipse(double x0, double y0, double width, double height){
    x0 -= width / 2;
    y0 -= height / 2;

    // V2d p0 = __transform(x0, y0);

    double ytop = y0;
    double x1 = x0 + width - 1, y1 = y0 + height - 1;
    double a = math_fabs(x1-x0);
    double b = math_fabs(y1-y0);
    int b1 = (int)b&1; /* values of diameter */
    double dx = 4*(1-a)*b*b, dy = 4*(b1+1)*a*a; /* error increment */
    double err = dx+dy+b1*a*a, e2; /* error of 1.step */

    if (x0 > x1) { x0 = x1; x1 += a; } /* if called with swapped points */
    if (y0 > y1) y0 = y1; /* .. exchange them */
    y0 += (b+1)/2; y1 = y0-b1;   /* starting pixel */
    a *= 8*a; b1 = 8*b*b;
    
    int * lined = (int *) calloc((int) height, sizeof(int));
    
    do {
        if(lined[(int)(y0 - ytop)] == 0){
            __draw_line_scale(x1, y0, x0, y0, __fill); /*   I. Quadrant */
            lined[(int)(y0 - ytop)] = 1;
        }
        if(lined[(int)(y1 - ytop)] == 0){
            __draw_line_scale(x0, y1, x1, y1, __fill); /* III. Quadrant */
            lined[(int)(y1 - ytop)] = 1;
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
            point(x0,y0, __stroke);                                     /* plot curve */
            if (x0 == x2 && y0 == y2) return;  /* last pixel -> curve finished */
            y1 = 2*err < dx;                  /* save value for test of y step */
            if (2*err > dy) { x0 += sx; dx -= xy; err += dy += yy; } /* x step */
            if (    y1    ) { y0 += sy; dy -= xy; err += dx += xx; } /* y step */
        } while (dy < dx );           /* gradient negates -> algorithm fails */
    }
    __raw_sline(x0, y0, x2, y2);                  /* plot remaining part to end */
}
void draw_bezier(int x0, int y0, int x1, int y1, int x2, int y2)
{                                          /* plot any quadratic Bezier curve */
    int x = x0-x1, y = y0-y1;
    double t = x0-2*x1+x2, r;

    if ((long)x*(x2-x1) > 0) {                        /* horizontal cut at P4? */
        if ((long)y*(y2-y1) > 0)                     /* vertical cut at P6 too? */
            if (math_fabs((y0-2*y1+y2)/t*x) > abs(y)) {               /* which first? */
                x0 = x2; x2 = x+x1; y0 = y2; y2 = y+y1;            /* swap points */
            }                            /* now horizontal cut at P4 comes first */
        t = (x0-x1)/t;
        r = (1-t)*((1-t)*y0+2.0*t*y1)+t*t*y2;                       /* By(t=P4) */
        t = (x0*x2-x1*x1)*t/(x0-x1);                       /* gradient dP4/dx=0 */
        x = math_floor(t+0.5); y = math_floor(r+0.5);
        r = (y1-y0)*(t-x0)/(x1-x0)+y0;                  /* intersect P3 | P0 P1 */
        __x_plot_quad_bezier_seg(x0,y0, x,math_floor(r+0.5), x,y);
        r = (y1-y2)*(t-x2)/(x1-x2)+y2;                  /* intersect P4 | P1 P2 */
        x0 = x1 = x; y0 = y; y1 = math_floor(r+0.5);             /* P0 = P4, P1 = P8 */
    }
    if ((long)(y0-y1)*(y2-y1) > 0) {                    /* vertical cut at P6? */
        t = y0-2*y1+y2; t = (y0-y1)/t;
        r = (1-t)*((1-t)*x0+2.0*t*x1)+t*t*x2;                       /* Bx(t=P6) */
        t = (y0*y2-y1*y1)*t/(y0-y1);                       /* gradient dP6/dy=0 */
        x = math_floor(r+0.5); y = math_floor(t+0.5);
        r = (x1-x0)*(t-y0)/(y1-y0)+x0;                  /* intersect P6 | P0 P1 */
        __x_plot_quad_bezier_seg(x0,y0, math_floor(r+0.5),y, x,y);
        r = (x1-x2)*(t-y2)/(y1-y2)+x2;                  /* intersect P7 | P1 P2 */
        x0 = x; x1 = math_floor(r+0.5); y0 = y1 = y;             /* P0 = P6, P1 = P7 */
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

static int32_t __SIN(double value) {
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

static int32_t __COS(double value) {
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
void __x_fill_arc(double centerx, double centery, int radius, int thickness, int degrees_begin, int degrees_end) {
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
                point(center.x+x, center.y-y, __stroke);
        }
    }

}

void fill_arc(double centerx, double centery, int radius, int thickness, int degrees_begin, int degrees_lenght){
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
void __plot_raw_bright_pixel( int x , int y , Color color, double brightness)
{
    color.r = color.r * brightness;
    color.g = color.g * brightness;
    color.b = color.b * brightness;
    color.a = color.a * brightness;

    plot(x, y, color);
}

void __raw_line(int x0 , int y0 , int x1 , int y1, Color color) {
	int steep = math_fabs(y1 - y0) > math_fabs(x1 - x0) ;

	// swap the co-ordinates if slope > 1 or we
	// draw backwards
	if (steep) {
        X_SWAP(x0, y0, int);
        X_SWAP(x1, y1, int);
	}
	if (x0 > x1) {
        X_SWAP(x0, x1, int);
        X_SWAP(y0, y1, int);
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
			__plot_raw_bright_pixel((int) intersectY    , x, color, __r_fractional(intersectY));
			__plot_raw_bright_pixel((int) intersectY + 1, x, color, __m_fractional(intersectY));
			intersectY += gradient;
		}
	} else {
		for (int x = xpxl1 ; x <=xpxl2 ; x++) {
			// pixel coverage is determined by fractional
			// part of y co-ordinate
			__plot_raw_bright_pixel(x, (int) intersectY    , color, __r_fractional(intersectY));
			__plot_raw_bright_pixel(x, (int) intersectY + 1, color, __m_fractional(intersectY));
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
    __raw_line(x0, y0, x1, y1, color);
}

void __draw_line_scale(double x0 , double y0 , double x1 , double y1, Color color) {
    double s = __get_transform_scale();
    V2d origin = __transform(x0/s, y0/s);
    V2d destiny = __transform(x1/s, y1/s);
    x0 = origin.x;
    y0 = origin.y;
    x1 = destiny.x;
    y1 = destiny.y;
    __raw_line(x0, y0, x1, y1, color);
}

void line(double x0 , double y0 , double x1 , double y1) {
    if (__thickness == 1) {
        __draw_line(x0, y0, x1, y1, __stroke);
        return;
    }
    __fill_line(x0, y0, x1, y1, __thickness);
}
