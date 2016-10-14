#include "Point.h"

//Constuctor
Point::Point(){
  x=0;
  y=0;
  z=0;
}

//Constuctor
Point::Point(float x,float y,float z){
  this->x=x;
  this->y=y;
  this->z=z;
}

//getter
float Point::getX(){
  return x;
}

float Point::getY(){
  return y;
}

float Point::getZ(){
  return z;
}

//distance calculation
float Point::distance(Point p){
  return pow(pow(x-p.getX(),2)+pow(y-p.getY(),2)+pow(z-p.getZ(),2),.5);
}

//normalize method
void Point::normalize(){
  float mag=pow(pow(x,2)+pow(y,2)+pow(z,2),0.5);
  x/=mag; y/=mag; z/=mag;
}

//operator * for two points
Point operator*(Point p,float f){
  return Point(p.getX()*f, p.getY()*f, p.getZ()*f);
}

//operator * for two points
Point operator*(float f,Point p){
  return Point(p.getX()*f, p.getY()*f, p.getZ()*f);
}

//operator / for two points
Point operator/(Point p,float f){
  return Point(p.getX()/f, p.getY()/f, p.getZ()/f);
}

//operartor / for two points
Point operator/(float f,Point p){
  return Point(p.getX()/f, p.getY()/f, p.getZ()/f);
}

//operator + to two points
Point operator+(Point p1, Point p2){
  return Point(p1.getX()+p2.getX(), p1.getY()+p2.getY(), p1.getZ()+p2.getZ());
}

//operator - for two points
Point operator-(Point p1, Point p2){
  return Point(p1.getX()-p2.getX(), p1.getY()-p2.getY(), p1.getZ()-p2.getZ());
}

//operator ++
void Point::operator+=(Point p){
  this->x+=p.getX();
  this->y+=p.getY();
  this->z+=p.getZ();
}

//operator "--"
void Point::operator-=(Point p){
  this->x-=p.getX();
  this->y-=p.getY();
  this->z-=p.getZ();
}

//operator "equal"
void Point::operator=(Point p){
  this->x=p.getX();
  this->y=p.getY();
  this->z=p.getZ();
}

//Operator stream method
std::ostream& operator<<(std::ostream& os,Point p2){
	os << "x: " << p2.getX();
	os << " y: " << p2.getY();
	os << " z: " << p2.getZ();
	return os;
}
