#ifndef POINT_H
#define POINT_H

class Point {
//private:
	
	
public:
	float x;
	float y;
	float z;

	Point();
	Point(float, float, float);
	
	float getX() {
		return x;
	}
	float getY() {
		return y;
	}
	float getZ() {
		return z;
	}

	void setX(float px) {
		x = px;
	}

	void setY(float py) {
		y = py;
	}

	void setZ(float pz) {
		z = pz;
	}
};


Point operator*(Point p, float f); // multiplies a Point by a float
Point operator*(float f, Point p); // multiplies a float by a Point
Point operator+(Point a, Point b); // adds two Points together

#endif // !POINT_H
