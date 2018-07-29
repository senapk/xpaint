#include "xy.h" //XDDDX
#include "xmath.h" //XDDDX

XY make_xy(float x, float y){
    XY v = {x, y};
    return v;
}

float xy_lenght(XY v){
    return xm_sqrt(v.x * v.x + v.y * v.y);
}

float xy_distance(XY a, XY b){
    return xy_lenght(make_xy(b.x - a.x, b.y - a.y));
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
    float lenght = xy_lenght(v);
    if(lenght == 0)
        return v;
    v.x = v.x * (1.0/lenght);
    v.y = v.y * (1.0/lenght);
    return v;
}

XY xy_ortho(XY v){
    return make_xy(v.y, -v.x);
}
