#include "FairyEric.h"

// Constant Variables
const float PI = 3.14159;
const float RAD = PI/180;

FairyEric::FairyEric(){}

// Basic Circle
void FairyEric::drawCircle(){
	glPushMatrix();
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0,0);
	for(int i = 0; i < 361; i++){
		float angle = i*RAD;
		glVertex3f(50*cos(angle),50*sin(angle),0);
	}

	glEnd();
	glPopMatrix();
}


// Getters
float FairyEric::getFairyEricPositionX(){
	return fairyEricPositionX;
}
float FairyEric::getFairyEricPositionY(){
	return fairyEricPositionY;
}
float FairyEric::getFairyEricPositionZ(){
	return fairyEricPositionZ;
}
float FairyEric::getFairyEricPositionTheta(){
	return fairyEricPositionTheta;
}

// Setters
void FairyEric::setFairyEricPositionX(float item){
	fairyEricPositionX = item;
}
void FairyEric::setFairyEricPositionY(float item){
	fairyEricPositionY = item;
}
void FairyEric::setFairyEricPositionZ(float item){
	fairyEricPositionZ = item;
}
void FairyEric::setFairyEricPositionTheta(float item){
	fairyEricPositionTheta = item;
}

// Drawing Functions
/*
* Draws the entire Character
*/
void FairyEric::drawFairy(){
	glPushMatrix();
	{
		glTranslatef(fairyEricPositionX, fairyEricPositionY, fairyEricPositionZ);
		glRotatef(fairyEricPositionTheta, 0,1,0);
		glScalef(0.8,0.8,0.8);
		drawBody();
	}
	glPopMatrix();
}

/*
 * Draws a foot
 * This includes the legs and foot
 */
 void FairyEric::drawFeet(){
 	glPushMatrix();
 	{
 		glColor3ub(255,105,180);
 		glRotatef(90,1,0,0);
 		GLUquadricObj *leg;
 		leg = gluNewQuadric();
 		gluQuadricDrawStyle(leg, GLU_FILL);
 		gluCylinder(leg, 1.7,1.5,2,100,100);
 		gluDeleteQuadric(leg);
 	}
 	glPopMatrix();

 	glPushMatrix();
 	{
 		glColor3f(0,0,0);
 		glTranslatef(0.3,-2,0);
 		glScalef(0.6,0.1,0.6);
 		glutSolidSphere(3,50,50);
 	}
 	glPopMatrix();
 }
/*
 * Draws the body:
 * Includes:
 * Body, Arm, Legs
 */
 void FairyEric::drawBody(){
	// Draw the line and buttons
 	glPushMatrix();
 	{

 		glPushMatrix();
 		glTranslatef(-4.5,0,0);
 		drawWing();
 		glPopMatrix();

 		glColor3ub(255,105,180);
 		glPushMatrix();
 		glScalef(1.5,1,1.5);
 		glutSolidSphere(3,50,50);
 		glPopMatrix();

 	}
 	glPopMatrix();

	// Draw the feet
 	glPushMatrix();
 	{
 		glPushMatrix();
 		glTranslatef(0,-1.5,1.5);
 		drawFeet();
 		glPopMatrix();

 		glPushMatrix();
 		glTranslatef(0,-1.5,-1.5);
 		drawFeet();
 		glPopMatrix();
 	}
 	glPopMatrix();

	// Draw Hands
 	glPushMatrix();
 	{
 		glPushMatrix();
 		glRotatef(-35,1,0,0);
 		glTranslatef(0,-0.8,3.5);
 		drawHands();
 		glPopMatrix();

 		glPushMatrix();
 		glRotatef(35,1,0,0);
 		glTranslatef(0,-0.8,-3.5);
 		drawHands();
 		glPopMatrix();
 	}
 	glPopMatrix();

	// Draw Head
 	glPushMatrix();
 	{
 		glTranslatef(0,3.3,0);
 		drawHead();
 	}
 	glPopMatrix();

 }
 void FairyEric::drawWing(){
 	glPushMatrix();
 	{
 		glDisable(GL_LIGHTING);
 		glPushMatrix();
 		glColor3f(1,1,1);
 		glRotatef(90,0,1,0);
 		glRotatef(45,0,0,1);
 		glScalef(.1,.05,.05);
 		drawCircle();
 		glPopMatrix();

 		glPushMatrix();
 		glColor3f(1,1,1);
		glRotatef(90,0,1,0);
		glRotatef(-45,0,0,1);
 		glScalef(.1,.05,.05);
 		drawCircle();
 		glPopMatrix();
 		glEnable(GL_LIGHTING);
 	}
 	glPopMatrix();

 }
/*
 * Draws the Arms and Hands
 */
 void FairyEric::drawHands(){
 	glPushMatrix();
 	glColor3ub(255,105,180);
 	glRotatef(90,1,0,0);
 	GLUquadricObj *arm;
 	arm = gluNewQuadric();
 	gluQuadricDrawStyle(arm, GLU_FILL);
 	gluCylinder(arm, 0.8,1,2.5,100,100);
 	gluDeleteQuadric(arm);
 	glPopMatrix();

 	glPushMatrix();
 	glColor3f(1,1,0);
 	glTranslatef(0,-2.5,0);
 	glutSolidSphere(1.2,50,50);
 	glPopMatrix();
 }
/*
 * Draws entire Head
 */
 void FairyEric::drawHead(){
 	glPushMatrix();
	glColor3f(0,0,0);
	glRotatef(90,1,0,0);
	glTranslatef(3,0,1);
	glutSolidTorus(0.1,1,50,50);
	glPopMatrix();

	glPushMatrix();
	glScalef(1.4,1,1.4);
	{
	//Draw face
	glPushMatrix();
	glColor3f(0.99 , 0.85 , 0.69);
	glutSolidSphere(3,50,50);
	glPopMatrix();
	}
	glPopMatrix();

	// Draw the Fairy Hat
	glPushMatrix();
	{
		glColor3ub(255,105,180);
		glRotatef(20,0,0,1);
		glRotatef(-90,1,0,0);
		glTranslatef(0,0,2.8);
		glutSolidCone(2, 4, 10,10 );

	}
	glPopMatrix();
	glDisable( GL_LIGHTING );
	glPushMatrix();
	{
	// Right Eye
	glPushMatrix();
	glColor3f(1,1,1);
	glRotatef(90,0,1,0);
	glTranslatef(0.6,0.05,4.2);
	glScalef(0.013,0.015,0.013);
	drawCircle();
	glPopMatrix();

	// Right Pupil
	glPushMatrix();
	glColor3f(0,0,0);
	glRotatef(90,0,1,0);
	glTranslatef(0.35,0.05,4.21);
	glScalef(0.002,0.002,0.002);
	drawCircle();
	glPopMatrix();

	// Left Eye
	glPushMatrix();
	glColor3f(1,1,1);
	glRotatef(90,0,1,0);
	glTranslatef(-0.6,0.05,4.2);
	glScalef(0.013,0.015,0.013);
	drawCircle();
	glPopMatrix();

	// Left Pupil
	glPushMatrix();
	glColor3f(0,0,0);
	glRotatef(90,0,1,0);
	glTranslatef(-0.35,0.05,4.21);
	glScalef(0.002,0.002,0.002);
	drawCircle();
	glPopMatrix();
	}
	glPopMatrix();
	glEnable( GL_LIGHTING );
 }
