#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <cstdio>
#include <cstdlib>
#include <cmath>

int random(int low,int high)
{
    int ch=rand()%(high-low) + low;
    return ch;
}
float getDis(float x1,float y1,float x2,float y2)
{
    float distance;
    distance = sqrt(pow(x2-x1,2)+pow(y2-y1,2));
    if(distance<0)
        distance*=-1;
    return distance;
}
#endif // UTIL_H_INCLUDED
