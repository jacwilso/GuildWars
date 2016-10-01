#include "hero.h"
#include "../utilities/Point.h"
using namespace std;

hero::hero() {
	charPosX = 0;
	charPosZ = 0;
	charRotateAngle = 0;
	index = 0;
	tailRotateAngle = 0;
}

hero::hero(float posX, float posZ, int charAngle, int idx, float tailAngle) {
	charPosX = posX;
	charPosZ = posZ;
	charRotateAngle = charAngle;
	index = idx;
	tailRotateAngle = tailAngle;
}


void hero::drawTail() {
	glColor3f(128, 0, 128);
	GLUquadricObj *tail;
	tail = gluNewQuadric();
	gluCylinder(tail, 0.25, 0.25, 1, 16, 16);
}

void hero::drawHead() {
	glColor3f(128, 0, 128);
	GLUquadricObj *head;
	head = gluNewQuadric();
	gluCylinder(head, 0.4, 0.6, 2, 16, 16);
}
void hero::drawWheels() {
	glColor3f(255, 0, 255);
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	gluCylinder(quadratic, 0.5, 0.5, 4, 16, 16);

}

void hero::drawNeck() {
	glColor3f(255, 255, 255);
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	gluCylinder(quadratic, 0.25, 0.25, 4, 16, 16);

	//draw head
	glPushMatrix();
	glTranslatef(0, -1.3, 0);
	glRotatef(-80, 1, 0, 0);
	drawHead();
	glPopMatrix();
}

void hero::drawBody() {

	glColor3f(255, 255, 255);
	glutSolidCube(2.0);
}

// void hero::drawSphere() {
// 	for (int i = 0;i < numOfConPoints;i++) {

// 		glPushMatrix();
// 		glTranslatef(controlPoints.at(i).getX(), controlPoints.at(i).getY(), controlPoints.at(i).getZ());
// 		glutSolidSphere(0.15, 16, 16);
// 		glPopMatrix();
// 	}
// }

// void hero::drawLines() {
// 	for (int i = 0;i < numOfConPoints - 1;i++) {
// 		glLineWidth(3.0);
// 		glColor3f(255, 255, 0);
// 		glBegin(GL_LINES);
// 		glPushMatrix();
// 		glVertex3f(controlPoints.at(i).getX(), controlPoints.at(i).getY(), controlPoints.at(i).getZ());
// 		glVertex3f(controlPoints.at(i + 1).getX(), controlPoints.at(i + 1).getY(), controlPoints.at(i + 1).getZ());
// 		glPopMatrix();
// 		glEnd();
// 	}
// }

// void hero::drawBezierLine(Point p1, Point p2) {
// 	glColor3f(0, 0, 255);
// 	glBegin(GL_LINES);
// 	glVertex3f(p1.getX(), p1.getY(), p1.getZ());
// 	glVertex3f(p2.getX(), p2.getY(), p2.getZ());
// 	glEnd();
// }

// evaluateBezierCurve() ////////////////////////////////////////////////////////
//
// Computes a location along a Bezier Curve. 
//
////////////////////////////////////////////////////////////////////////////////
// Point hero::evaluateBezierCurve(Point p0, Point p1, Point p2, Point p3, float t) {
// 	// TODO #08: Compute a point along a Bezier curve

// 	float px = pow((1 - t), 3)*p0.getX() + 3 * t*pow((1 - t), 2)*p1.getX() +
// 		3 * (1 - t)*pow(t, 2)*p2.getX() + pow(t, 3)*p3.getX();
// 	float py = pow((1 - t), 3)*p0.getY() + 3 * t*pow((1 - t), 2)*p1.getY() +
// 		3 * (1 - t)*pow(t, 2)*p2.getY() + pow(t, 3)*p3.getY();
// 	float pz = pow((1 - t), 3)*p0.getZ() + 3 * t*pow((1 - t), 2)*p1.getZ() +
// 		3 * (1 - t)*pow(t, 2)*p2.getZ() + pow(t, 3)*p3.getZ();
// 	Point* p = new Point(px, py, pz);
// 	return *p;
// }

// renderBezierCurve() //////////////////////////////////////////////////////////
//
// Responsible for drawing a Bezier Curve as defined by four control points.
//  Breaks the curve into n segments as specified by the resolution. 
//
////////////////////////////////////////////////////////////////////////////////
// void hero::renderBezierCurve(Point p0, Point p1, Point p2, Point p3, int resolution) {
// 	// TODO #07: Draw a Bezier curve
// 	Point old = p0;
// 	bezierPoints.push_back(p0);
// 	Point last = p0;
// 	for (float t = 0.0; t <= resolution;t += 0.1) {
// 		Point p = evaluateBezierCurve(p0, p1, p2, p3, t);

// 		//push bezier curve points into vector
// 		bezierPoints.push_back(p);

// 		//draw line between two bezier points
// 		drawBezierLine(old, p);
// 		old = p;
// 		last = p;
// 	}
// 	//
// 	bezierPoints.push_back(p3);
// 	//make up the last segment
// 	drawBezierLine(last, p3);
// }

// void hero::drawFairy() {

// 	//glPushMatrix();
// 	glColor3f(0.28, 0.85, 0.12);
// 	glTranslatef(bezierPoints.at(index).getX(), bezierPoints.at(index).getY(), bezierPoints.at(index).getZ());
// 	glutSolidSphere(0.25, 16, 16);
// 	//glPopMatrix();
// }


void hero::drawCharacter() {
	glTranslatef(charPosX, 0, charPosZ);
	//glTranslatef(20, 0, 20);
	glRotatef(charRotateAngle, 0, 1, 0);
	glColor3f(0.9, 0.45, 0.1);
	//glutSolidTorus(2,5,10,4);

	//drawing two cubes as character's body
	glPushMatrix();
	glTranslatef(0, 2, 0);
	drawBody();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 2, 2);
	drawBody();
	glPopMatrix();

	//drawing a neck
	glPushMatrix();
	glTranslatef(0, 6, -2);
	glRotatef(60, 1, 0, 0);
	drawNeck();
	glPopMatrix();

	//drawing front wheel
	glPushMatrix();
	glTranslatef(-2, 0, 0);
	glRotatef(90, 0, 1, 0);
	drawWheels();
	glPopMatrix();

	//drawing rear wheel
	glPushMatrix();
	glTranslatef(-2, 0, 2);
	glRotatef(90, 0, 1, 0);
	drawWheels();
	glPopMatrix();

	//drawing tail
	glPushMatrix();
	glTranslatef(0, 3, 3);
	glRotatef(-40 + tailRotateAngle, 1, 0, 0);
	drawTail();
	glPopMatrix();

	//draw bezier curve components

	// if (controlCageOn == true) {
	// 	//draw sphere
	// 	glPushMatrix();
	// 	glColor3f(0.5, 0.8, 0.4);
	// 	drawSphere();
	// 	glPopMatrix();

	// 	// TODO #06: Connect our control points
	// 	glPushMatrix();
	// 	drawLines();
	// 	glPopMatrix();
	// }

	// // TODO #07: Draw the Bezier Curve!
	// if (bezierCurveOn == true) {
	// 	glPushMatrix();
	// 	if (numOfConPoints <= 4) {
	// 		renderBezierCurve(controlPoints.at(0), controlPoints.at(1), controlPoints.at(2), controlPoints.at(3), 1);
	// 	}
	// 	else {
	// 		renderBezierCurve(controlPoints.at(0), controlPoints.at(1), controlPoints.at(2), controlPoints.at(3), 1);
	// 		renderBezierCurve(controlPoints.at(3), controlPoints.at(4), controlPoints.at(5), controlPoints.at(6), 1);
	// 	}
	// 	glPopMatrix();
	// }

	//Draw the fairy
	// glPushMatrix();
	// drawFairy();
	// glPopMatrix();
}
