#include "Environment.h"

Environment::Environment(){
  srand( time(NULL) );	// seed our random number generator
  qobj=gluNewQuadric();  
  gluQuadricNormals(qobj,GLU_SMOOTH);
}

// drawGrid() //////////////////////////////////////////////////////////////////
//
//  Function to draw a grid in the XZ-Plane using OpenGL 2D Primitives (GL_LINES)
//
////////////////////////////////////////////////////////////////////////////////
void Environment::drawGrid() {
    glDisable( GL_LIGHTING );

    glColor3f(1,1,1);
    glLineWidth(2);
    for(int i=-BOUNDARY; i<=BOUNDARY; i+=2){
        glBegin(GL_LINES);
          glVertex3f(-BOUNDARY,0,i);
          glVertex3f(BOUNDARY,0,i);
          
          glVertex3f(i,0,-BOUNDARY);
          glVertex3f(i,0,BOUNDARY);
        glEnd();
    }
    glLineWidth(1.0f);
    glEnable( GL_LIGHTING );
}

// draw a box raise for elevation change
void Environment::drawRaise(){
  glColor3f(.15,.15,.15);
  glPushMatrix();
    glScalef(20,.6,20);
    glutSolidCube(1);
  glPopMatrix();
}

// drawBox() //////////////////////////////////////////////////////////////////
//
//  Function to draw a hollow cube (box) using GLUT 3D Primitives
//
////////////////////////////////////////////////////////////////////////////////
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

// drawRock() //////////////////////////////////////////////////////////////////
//
//  Function to draw a rock formation (weird shape) using GLUT 3D Primitives
//
////////////////////////////////////////////////////////////////////////////////
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

// generateEnvironmentDL() /////////////////////////////////////////////////////
//
//  This function creates a display list with the code to draw a simple 
//      environment for the user to navigate through. Called once, because
//      they are stationary objects.
//
//
////////////////////////////////////////////////////////////////////////////////
void Environment::generateEnvironmentDL() {
    environmentDL=glGenLists(1);
    glNewList(environmentDL, GL_COMPILE);
      drawGrid(); // draw the grid
      drawRaise();
      for(int i=2; i<=12; i++){ // add some sudo random boxes throughout the scene, of different sizes at different locations 
        glPushMatrix();
          glTranslatef((BOUNDARY-4)*(1-getRand()*2),float(i)/20,(BOUNDARY-4)*(1-getRand()*2)); // random position with the bottom touching the bottom of the grid
          glScalef((float)(i)/12,(float)(i)/12,(float)(i)/12); // scale it down based on the number of box
          drawBox();
        glPopMatrix();
      }
      for(int i=2; i<=12; i++){ // add some sudo random rock formations throughout the scene, of different sizes at different locations -- same code as the boxes
        glPushMatrix();
          glTranslatef((BOUNDARY-4)*(1-getRand()*2),float(i)/20,(BOUNDARY-4)*(1-getRand()*2));
          glScalef((float)(i)/12,(float)(i)/12,(float)(i)/12);
          drawRock();
        glPopMatrix();
      }
    glEndList();
}
