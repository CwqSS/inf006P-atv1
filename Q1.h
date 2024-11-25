#include <math.h>
#ifndef Q1_H
#define Q1_H
#define MAX_POINT 5

typedef struct point {
    double x;
    double y;
    double euclidianDistanceToOrigin;
} point;

int strStr(char * str, char * Str);
double euclidianDistanceToTheOrigin(point p);
double euclidianDistanceBtw2Points(point p1, point p2);
void distance_insertion_sort(point * p, int size);

#endif