#include "Donkey.h"
#include "Point.h"
using namespace std;

Donkey::Donkey() {
	heroPosX = 0;
	heroPosZ = 0;
	heroPosY = 0;
	heroTheta = 0;
	index = 0;
	tailRotateAngle = 0;
}

Donkey::Donkey(float posX, float posZ, int heroAngle, int idx, float tailAngle) {
	heroPosX = posX;
	heroPosZ = posZ;
	heroTheta = heroAngle;
	index = idx;
	tailRotateAngle = tailAngle;
}


void Donkey::drawTail() {
	glColor3f(128, 0, 128);
	GLUquadricObj *tail;
	tail = gluNewQuadric();
	gluCylinder(tail, 0.25, 0.25, 1, 16, 16);
}

void Donkey::drawHead() {
	glColor3f(128, 0, 128);
	GLUquadricObj *head;
	head = gluNewQuadric();
	gluCylinder(head, 0.4, 0.6, 2, 16, 16);
}

void Donkey::drawWheels() {
	glColor3f(255, 0, 255);
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	gluCylinder(quadratic, 0.5, 0.5, 4, 16, 16);
}

void Donkey::drawNeck() {
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

void Donkey::drawBody() {
	glColor3f(255, 255, 255);
	glutSolidCube(2.0);
}

// void Donkey::drawSphere() {
// 	for (int i = 0;i < numOfConPoints;i++) {
// 		glPushMatrix();
// 		glTranslatef(controlPoints.at(i).getX(), controlPoints.at(i).getY(), controlPoints.at(i).getZ());
// 		glutSolidSphere(0.15, 16, 16);
// 		glPopMatrix();
// 	}
// }

// void Donkey::drawLines() {
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

void Donkey::drawHero() {
	glTranslatef(heroPosX, 0, heroPosZ);
	//glTranslatef(20, 0, 20);
	glRotatef(heroTheta, 0, 1, 0);
	glColor3f(0.9, 0.45, 0.1);
	//glutSolidTorus(2,5,10,4);

	//drawing two cubes as heroacter's body
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
	glRotatef(40, 1, 0, 0);
        glRotatef(cos(0.25*tailRotateAngle)*180/3.1415,0,1,0);
	drawTail();
	glPopMatrix();
}

void Donkey::animate(){tailRotateAngle++;}
