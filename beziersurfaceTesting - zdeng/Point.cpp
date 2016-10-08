//#include <iostream>
#include "Point.h"

Point::Point() {
	x = 0;
	y = 0;
	z = 0;
}

Point::Point(float px, float py, float pz) {
	x = px;
	y = py;
	z = pz;
}

Point operator*(Point p, float f) {
	return Point(p.getX() * f, p.getY() * f, p.getZ() * f);
}

Point operator*(float f, Point p) {
	return Point(f*p.getX(), f*p.getY(), f*p.getZ());
}

Point operator+(Point a, Point b) {
	return Point(a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
}