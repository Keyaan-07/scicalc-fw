#include <math.h>
#define pi 3.14158256

float divide(float x, float y){
    if(y==0) return NAN;
    return x/y;
}

float sin_v(float x, bool deg){
    if(deg){
        return sin((float)pi*x/180);
    }
    else{
        return sin(x);
    }
}

float cos_v(float x, bool deg){
    if(deg){
        return cos((float)pi*x/180);
    }
    else{
        return cos(x);
    }
}

float tan_v(float x, bool deg){
    if(deg){
        if(x==90 || x==270) return NAN;
        return tan((float)x*pi/180);
    }
    else{

        if(x==(float)pi/2 || x==(float)3*pi/2) return NAN;
        return tan(x);
    }
}

float sqrt_v(float x){
    if(x<0.0) return NAN;
    else return pow(x, (float)1/2);
}

float power_v(float x, float p){
    return pow(x, p);
}