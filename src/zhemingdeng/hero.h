#ifndef HERO_H
#define HERO_H

class hero {


public:
	float charPosX;
	float charPosZ;
	int charRotateAngle;

	//the index for fairy's position
	int index = 0;

	float tailRotateAngle;

	hero();
	hero(float, float, int, int, float);

	float getCharPosX() {
		return charPosX;
	}

	float getCharPosZ() {
		return charPosZ;
	}

	int getCharRotateAngle() {
		return charRotateAngle;
	}

	int getIndex() {
		return index;
	}

	float getTailRotateAngle() {
		return tailRotateAngle;
	}

	void setCharPosX(float posX) {
		charPosX = posX;
	}

	void setCharPosY(float posY) {
		charPosY = posY;
	}
	void setCharRotateAngle(int angle) {
		charRotateAngle = angle;
	}
	void setIndex(int i) {
		index = i;
	}
	void setTailRotateAngle(float angle) {
		charRotateAngle = angle;
	}

	void drawBezierLine(Point, Point);
	void drawBody();
	void drawCharacter();
	void drawFairy();
	void drawHead();
	void drawLines();
	void drawNeck();
	void drawSphere();
	void drawTail();
	void drawWheels();
	Point evaluateBezierCurve(Point, Point, Point, Point, float);
	void renderBezierCurve(Point p0, Point p1, Point p2, Point p3, int resolution)
	
};

#endif //