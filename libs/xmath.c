

#include "xmath.h" /* XDDDX */
#include <stdint.h>
#include <stdlib.h>

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

int   xm_rand(int min, int max){
    return rand() % (max + 1 - min) + min;
}

/* https://stackoverflow.com/questions/5122993/floor-int-function-implementaton?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa */
int xm_floor(double x) {
    int xi = (int) x;
    return x < xi ? xi - 1 : xi;
}


/* funcao necessario para o po */
float xm_sqrt(const float m)
{
   float i=0;
   float x1,x2;
   while( (i*i) <= m )
          i+=0.1f;
   x1=i;
   int j;
   for(j=0;j<10;j++)
   {
       x2=m;
      x2/=x1;
      x2+=x1;
      x2/=2;
      x1=x2;
   }
   return x2;
}

float xm_pow( float x, float z ){
    int y =  z;
    double temp;
    if (y == 0)
    return 1;
    temp = xm_pow (x, y / 2);
    if ((y % 2) == 0) {
        return temp * temp;
    } else {
        if (y > 0)
            return x * temp * temp;
        else
            return (temp * temp) / x;
    }
}

float xm_fmod(float a, float b)
{
    return (a - b * xm_floor(a / b));
}

int xm_ceil(float n){
    return -xm_floor(-n);
}


/* Sin e Cos retirados de
   http://forum.arduino.cc/index.php?topic=69723.0
*/

unsigned int __isinTable16[] = {
    0, 1144, 2287, 3430, 4571, 5712, 6850, 7987, 9121, 10252, 11380,
    12505, 13625, 14742, 15854, 16962, 18064, 19161, 20251, 21336, 22414,
    23486, 24550, 25607, 26655, 27696, 28729, 29752, 30767, 31772, 32768,

    33753, 34728, 35693, 36647, 37589, 38521, 39440, 40347, 41243, 42125,
    42995, 43851, 44695, 45524, 46340, 47142, 47929, 48702, 49460, 50203,
    50930, 51642, 52339, 53019, 53683, 54331, 54962, 55577, 56174, 56755,

    57318, 57864, 58392, 58902, 59395, 59869, 60325, 60763, 61182, 61583,
    61965, 62327, 62671, 62996, 63302, 63588, 63855, 64103, 64331, 64539,
    64728, 64897, 65047, 65176, 65286, 65375, 65445, 65495, 65525, 65535,
};


float __isin(long x)
{
    int bool_pos = 1;  /* positive - keeps an eye on the sign. */
    if (x < 0)
    {
        x = -x;
        bool_pos = !bool_pos;
    }
    if (x >= 360) x %= 360;
    if (x > 180)
    {
        x -= 180;
        bool_pos = !bool_pos;
    }
    if (x > 90) x = 180 - x;
    if (bool_pos) return __isinTable16[x] * 0.0000152590219; 
    return __isinTable16[x] * -0.0000152590219 ;
}

float __icos(long x)
{
    return __isin(x+90);
}

float xm_sin(float d)
{
    float a = __isin(d);
    float b = __isin(d+1);
    return a + (d-(int)d) * (b-a);
}

float xm_cos(float d)
{
    float a = __icos(d);
    float b = __icos(d+1);
    return a + (d-(int)d) * (b-a);
}

/* Nvidia */
float xm_acos(float x) {
    float negate = (float)(x < 0);
    x = (x >= 0) ? x : -x;
    float ret = -0.0187293;
    ret = ret * x;
    ret = ret + 0.0742610;
    ret = ret * x;
    ret = ret - 0.2121144;
    ret = ret * x;
    ret = ret + 1.5707288;
    ret = ret * xm_sqrt(1.0-x);
    ret = ret - 2 * negate * ret;
    return negate * 3.14159265358979 + ret;
}

float xm_fabs(float f){
    return f < 0 ? -f : f;
}

#ifdef __cplusplus
}
#endif

