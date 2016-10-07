#ifndef POINT_H
#define POINT_H

#include <math.h>
#include <iostream>
class Point{
  private:
    float x,y,z;

  public:
    Point();
    Point(float x,float y,float z);

    float getX();
    float getY();
    float getZ();

    float distance(Point p);

    void operator=(Point p);
    void operator+=(Point p);
    void operator-=(Point p);
};

Point operator*(Point p,float f);
Point operator*(float f,Point p);
Point operator+(Point p1,Point p2);
Point operator-(Point p1,Point p2);
//std::ostream& operator<<(std::ostream& os, Point p2);
#endif
