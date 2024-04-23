#include "xmath.h" /*XDDDX*/

/*########################*/
/*###### X_MATH MODULE ###*/
/*########################*/

#include <stdint.h>
#include <stdlib.h>


V2d v2d(double x, double y){
    V2d v = {x, y};
    return v;
}

double v2d_length(double x, double y){
    return xsqrt(x * x + y * y);
}

double dist(double ax, double ay, double bx, double by){
    return v2d_length(bx - ax, by - ay);
}

V2d v2d_sum(V2d a, V2d b){
    return v2d(a.x + b.x, a.y + b.y);
}

V2d v2d_sub(V2d a, V2d b){
    return v2d(a.x - b.x, a.y - b.y);
}

V2d v2d_dot(V2d a, double value){
    return v2d(a.x * value, a.y * value);
}

V2d v2d_normalize(V2d v){
    double lenght = v2d_length(v.x, v.y);
    if(lenght < 0.0000001)
        return v;
    v.x = v.x * (1.0/lenght);
    v.y = v.y * (1.0/lenght);
    return v;
}

V2d v2d_ortho(V2d v){
    return v2d(v.y, -v.x);
}

int   xrand(int min, int max){
    return rand() % (max - min) + min;
}

/* https://stackoverflow.com/questions/5122993/floor-int-function-implementaton?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa */
int xfloor(double x) {
    int xi = (int) x;
    return x < xi ? xi - 1 : xi;
}

int xround(double x) {
	return x + 0.5;
}


/* funcao necessario para o po */
double xsqrt(const double m)
{
   double i=0;
   double x1 = 0, x2 = 0;
   while( (i*i) <= m )
          i+=0.1;
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

double xpow( double x, double z ){
    int y =  (int) z;
    double temp;
    if (y == 0)
    return 1;
    temp = xpow (x, y / 2);
    if ((y % 2) == 0) {
        return temp * temp;
    } else {
        if (y > 0)
            return x * temp * temp;
        else
            return (temp * temp) / x;
    }
}

double xfmod(double a, double b)
{
    return (a - b * xfloor(a / b));
}

int xceil(double n){
    return -xfloor(-n);
}


/* Sin e Cos retirados de
   http://forum.arduino.cc/index.php?topic=69723.0
*/

static unsigned int __isinTable16[] = {
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

double __isin(long x);
double __isin(long x)
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

double __icos(long x);
double __icos(long x)
{
    return __isin(x+90);
}

double xsin(double d)
{
    double a = __isin((long) d);
    double b = __isin((long) d+1);
    return a + (d-(int)d) * (b-a);
}

double xcos(double d)
{
    double a = __icos((long) d);
    double b = __icos((long) d+1);
    return a + (d-(int)d) * (b-a);
}

/* Nvidia */
double xacos(double x) {
    double negate = (double)(x < 0);
    x = (x >= 0) ? x : -x;
    double ret = -0.0187293;
    ret = ret * x;
    ret = ret + 0.0742610;
    ret = ret * x;
    ret = ret - 0.2121144;
    ret = ret * x;
    ret = ret + 1.5707288;
    ret = ret * xsqrt(1.0-x);
    ret = ret - 2 * negate * ret;
    return negate * 3.14159265358979 + ret;
}

double xfabs(double f){
    return f < 0 ? -f : f;
}

