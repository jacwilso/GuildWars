#include "Environment.h"

Environment::Environment(){

}

void Environment::generateEnvironmentDL() {
	environmentDL = glGenLists( 1 );

	// Tell openGL to begin displaying lists
	glNewList( environmentDL, GL_COMPILE );
	// Draw the figures
	glPushMatrix(); {
		drawEnvironment();
	}; glPopMatrix();
	// Tell openGL to end displayiung lists
	glEndList();
}

void Environment::drawEnvironment(){
	drawGrid();
	drawTrees();
}

void Environment::drawGrid() {
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

void Environment::drawGround(){
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

void Environment::drawTree(){
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

void Environment::drawRock(){
  glColor3f(.1,.1,.1); // gray color
  for(int i=0; i<13; i++){ // # of cylinders to stack on one another
    glPushMatrix();
      glTranslatef(0,i+1,0); // translate the cylinder up to new height
      glRotatef(90,1,0,0); // rotate cylinder so it is vertical
      gluCylinder(qobj,2+.75*cos((i+1)*36*DEG_RAD),2+.75*cos(i*36*DEG_RAD),1,32,32); // cylinder with varying base and top radii, with height 1
    glPopMatrix();
  }
}

void Environment::drawBox(){
  glColor3ub(181,166,66); // Brass color
  // BOTTOM SQUARE
  glPushMatrix();
    glTranslatef(0,0,-5);
    glScalef(10,1,1);
    glutSolidCube(1);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(-5,0,0);
    glScalef(1,1,10);
    glutSolidCube(1);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(0,0,5);
    glScalef(10,1,1);
    glutSolidCube(1);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(5,0,0);
    glScalef(1,1,10);
    glutSolidCube(1);
  glPopMatrix();
  // TOP SQUARE
  glPushMatrix();
    glTranslatef(0,10,-5);
    glScalef(10,1,1);
    glutSolidCube(1);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(-5,10,0);
    glScalef(1,1,10);
    glutSolidCube(1);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(0,10,5);
    glScalef(10,1,1);
    glutSolidCube(1);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(5,10,0);
    glScalef(1,1,10);
    glutSolidCube(1);
  glPopMatrix();
  // PILLARS
  glPushMatrix();
    glTranslatef(5,5,-5);
    glScalef(1,11,1);
    glutSolidCube(1);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(-5,5,-5);
    glScalef(1,11,1);
    glutSolidCube(1);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(5,5,5);
    glScalef(1,11,1);
    glutSolidCube(1);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(-5,5,5);
    glScalef(1,11,1);
    glutSolidCube(1);
  glPopMatrix();
}

void Environment::drawTrees(){
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

void generateEnvironmentDL() {
	environmentDL = glGenLists( 1 );

	// Tell openGL to begin displaying lists
	glNewList( environmentDL, GL_COMPILE );
	// Draw the figures
	glPushMatrix(); {
		//drawEnvironment();
	}; glPopMatrix();
	// Tell openGL to end displayiung lists
	glEndList();

}

