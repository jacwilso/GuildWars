#include "Point.h"

Point::Point(){
  x=0;
  y=0;
  z=0;
}

Point::Point(float x,float y,float z){
  this->x=x;
  this->y=y;
  this->z=z;
}

float Point::getX(){
  return x;
}

float Point::getY(){
  return y;
}

float Point::getZ(){
  return z;
}

float Point::distance(Point p){
  return pow(pow(x-p.getX(),2)+pow(y-p.getY(),2)+pow(z-p.getZ(),2),.5);
}

Point operator*(Point p,float f){
  return Point(p.getX()*f, p.getY()*f, p.getZ()*f);
}

Point operator*(float f,Point p){
  return Point(p.getX()*f, p.getY()*f, p.getZ()*f);
}

Point operator+(Point p1, Point p2){
  return Point(p1.getX()+p2.getX(), p1.getY()+p2.getY(), p1.getZ()+p2.getZ());
}

void Point::operator+=(Point p){
  this->x+=p.getX();
  this->y+=p.getY();
  this->z+=p.getZ();
}

void Point::operator-=(Point p){
  this->x-=p.getX();
  this->y-=p.getY();
  this->z-=p.getZ();
}

void Point::operator=(Point p){
  this->x=p.getX();
  this->y=p.getY();
  this->z=p.getZ();
}
