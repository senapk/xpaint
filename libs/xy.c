#include "xy.h" /* XDDDX */
#include "xmath.h" /* XDDDX */

#ifdef __cplusplus
extern "C" {
#endif

XY make_xy(float x, float y){
    XY v = {x, y};
    return v;
}

float xy_lenght(float x, float y){
    return xm_sqrt(x * x + y * y);
}

float xy_distance(float ax, float ay, float bx, float by){
    return xy_lenght(bx - ax, by - ay);
}

XY xy_sum(XY a, XY b){
    return make_xy(a.x + b.x, a.y + b.y);
}

XY xy_sub(XY a, XY b){
    return make_xy(a.x - b.x, a.y - b.y);
}

XY xy_dot(XY a, float value){
    return make_xy(a.x * value, a.y  * value);
}

XY xy_normalize(XY v){
    float lenght = xy_lenght(v.x, v.y);
    if(lenght == 0)
        return v;
    v.x = v.x * (1.0/lenght);
    v.y = v.y * (1.0/lenght);
    return v;
}

XY xy_ortho(XY v){
    return make_xy(v.y, -v.x);
}

#ifdef __cplusplus
}
#endif


