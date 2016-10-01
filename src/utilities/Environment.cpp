#include "Environment.h"

void drawEnvironment(){
	//drawGround();
	drawGrid();
	drawRoad();
	drawSidewalks();
	drawTrees();
}

// drawGrid() //////////////////////////////////////////////////////////////////
//
//  Function to draw a grid in the XZ-Plane using OpenGL 2D Primitives (GL_LINES)
//
////////////////////////////////////////////////////////////////////////////////
void drawGrid() {
	/*
	 *	We will get to why we need to do this when we talk about lighting,
	 *	but for now whenever we want to draw something with an OpenGL
	 *	Primitive - like a line, quad, point - we need to disable lighting
	 *	and then reenable it for use with the GLUT 3D Primitives.
	 */
	 glDisable( GL_LIGHTING );

	 glColor3f(1,1,1);
	 glBegin(GL_LINES);
	 for(int i = -100; i <= 100; i+=5){
	 	glVertex3f( i, 0, -100);
	 	glVertex3f( i, 0, 100);

	 	glVertex3f(100, 0, i);
	 	glVertex3f(-100, 0, i);
	 }
	 glEnd();
	/*
	 *	As noted above, we are done drawing with OpenGL Primitives, so we
	 *	must turn lighting back on.
	 */
	 glEnable( GL_LIGHTING );
}

void drawGround(){
	glDisable( GL_LIGHTING );
	glColor3f(1,1,1);
	glPushMatrix();
	{

		glBegin(GL_QUADS);
		glVertex3f(-100,0.1,-100);
		glVertex3f(-100,0.1,100);
		glVertex3f(100, 0.1, 100);
		glVertex3f(100, 0.1, -100);
		glEnd();
	}
	glPopMatrix();
	glEnable( GL_LIGHTING);
}

void drawRoad(){
	glPushMatrix();
	{
		glColor3f(0.2, 0.2, 0.2);
		glBegin(GL_QUADS);
		glVertex3f(40,0.2,-100);
		glVertex3f(70,0.2, -100);
		glVertex3f(70, 0.2, 100);
		glVertex3f(40, 0.2, 100);

		glVertex3f(-100, 0.21, 40);
		glVertex3f(-100, 0.21, 70);
		glVertex3f(100, 0.21, 70);
		glVertex3f(100, 0.21, 40);
		glEnd();
	}
	glPopMatrix();
}

void drawSidewalks(){
	glPushMatrix();
	{
	glColor3f(0.7,0.7,0.7);
	glTranslatef(35, 0.5, -30);
	glScalef(10, 1, 140);
	glutSolidCube(1);
	}
	glPopMatrix();

	glPushMatrix();
	{
	glTranslatef(75, 0.5, -30);
	glScalef(10, 1, 140);
	glutSolidCube(1);
	}
	glPopMatrix();

	glPushMatrix();
	{
	glTranslatef(75, 0.5, 85);
	glScalef(10, 1, 30);
	glutSolidCube(1);
	}
	glPopMatrix();

	glPushMatrix();
	{
	glTranslatef(35, 0.5, 85);
	glScalef(10, 1, 30);
	glutSolidCube(1);
	}
	glPopMatrix();


	glPushMatrix();
	{
	glColor3f(0.7,0.7,0.7);
	glTranslatef(-35, 0.5, 35);
	glScalef(130, 1, 10);
	glutSolidCube(1);
	}
	glPopMatrix();

	glPushMatrix();
	{
	glTranslatef(90, 0.5, 35);
	glScalef(20, 1, 10);
	glutSolidCube(1);
	}
	glPopMatrix();

	glPushMatrix();
	{
	glTranslatef(-35, 0.5, 75);
	glScalef(130, 1, 10);
	glutSolidCube(1);
	}
	glPopMatrix();

	glPushMatrix();
	{
	glTranslatef(90, 0.5, 75);
	glScalef(20, 1, 10);
	glutSolidCube(1);
	}
	glPopMatrix();

}

void drawTree(){
	glPushMatrix();
	{
	glPushMatrix();
	glColor3f( 0.647059 , 0.164706 , 0.164706);
	glRotatef(-90,1,0,0);
	GLUquadricObj *trunk;
	trunk = gluNewQuadric();
	gluQuadricDrawStyle(trunk, GLU_FILL);
	gluCylinder(trunk, 1,1,10,50,50);	
	gluDeleteQuadric(trunk);	
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(-90,1,0,0);
	glTranslatef(0, 0, 3);
	glutSolidCone(5,20, 30,10);
	glPopMatrix();
	}
	glPopMatrix();

}
void drawTrees(){
	glPushMatrix();
	glTranslatef(20,0,25);
	drawTree();
	glPopMatrix();

		glPushMatrix();
	glTranslatef(-25,0,-20);
	drawTree();
	glPopMatrix();

		glPushMatrix();
	glTranslatef(-40,0,-30);
	drawTree();
	glPopMatrix();

		glPushMatrix();
	glTranslatef(-50,0,-50);
	drawTree();
	glPopMatrix();

		glPushMatrix();
	glTranslatef(-70,0,-80);
	drawTree();
	glPopMatrix();

		glPushMatrix();
	glTranslatef(-65,0,-93);
	drawTree();
	glPopMatrix();

		glPushMatrix();
	glTranslatef(-15,0,-65);
	drawTree();
	glPopMatrix();	

		glPushMatrix();
	glTranslatef(-82,0,-77);
	drawTree();
	glPopMatrix();

		glPushMatrix();
	glTranslatef(0,0,-77);
	drawTree();
	glPopMatrix();

		glPushMatrix();
	glTranslatef(10,0,-44);
	drawTree();
	glPopMatrix();

			glPushMatrix();
	glTranslatef(22,0,90);
	drawTree();
	glPopMatrix();

			glPushMatrix();
	glTranslatef(90,0,90);
	drawTree();
	glPopMatrix();

			glPushMatrix();
	glTranslatef(-82,0,20);
	drawTree();
	glPopMatrix();

			glPushMatrix();
	glTranslatef(-40,0,-23);
	drawTree();
	glPopMatrix();


}

