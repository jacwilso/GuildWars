#include "Environment.h"

Environment::Environment(){}

void Environment::generateEnvironmentDL(std::ifstream& inFile) {
	environmentDL = glGenLists( 1 );

	// Tell openGL to begin displaying lists
	glNewList( environmentDL, GL_COMPILE );
	// Draw the figures
	glPushMatrix(); {
		placeObjectsInEnvironment(inFile);
		//drawGrid();
                drawSurface();
                drawCurve();
	}; glPopMatrix();
	// Tell openGL to end displayiung lists
	glEndList();
}

void Environment::placeObjectsInEnvironment(std::ifstream& inFile){
	if(inFile.is_open() == false){
		std::cout << "Couldn't read in File" << std::endl;
		exit(1);
	}

	int numObjects = 0;
	int objType = 0;
	float objectX = 0, objectY = 0, objectZ = 0;
	float orientX = 0, orientY = 0, orientZ = 0;
	float objSize = 0;
	//char comments;
	inFile >> numObjects;
	for(int i = 0; i < numObjects ; i++){
		std::string inValue;
		
		getline(inFile, inValue, ',');
		objType = atoi(inValue.c_str());
		
		getline(inFile, inValue, ',');
		objectX = atof(inValue.c_str());
		
		getline(inFile, inValue, ',');
		objectY = atof(inValue.c_str());
		
		getline(inFile, inValue, ',');
		objectZ = atof(inValue.c_str());
		
		getline(inFile, inValue, ',');
		orientX = atof(inValue.c_str());
		
		getline(inFile, inValue, ',');
		orientY = atof(inValue.c_str());
		
		getline(inFile, inValue, ',');
		orientZ = atof(inValue.c_str());
		
		getline(inFile,inValue, '\n');
		objSize = atof(inValue.c_str());
		
		// std::cout << "Start" << i << std::endl;
		// std::cout << objType << " ";
		// std::cout << objectX << " ";
		// std::cout << objectY << " ";
		// std::cout << objectZ << " ";
		// std::cout << orientX << " ";
		// std::cout << orientY << " ";
		// std::cout << orientZ << " ";
		// std::cout << objSize << std::endl;
		// Debugging
		//
		glPushMatrix();
		{
			glTranslatef(objectX, objectY, objectZ);
			glRotatef(orientX, 0,0,1);
			glRotatef(orientY, 0,1,0);
			glRotatef(orientZ, 1,0,0);
			glScalef(objSize, objSize, objSize);

			switch(objType){
				case 0:
					drawTree();
					break;	
                                case 1:
                                        drawHut();
                                        break;
				default:
					drawTree();
					break;
			}
		}
		glPopMatrix();
	}

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
	glLineWidth(1);
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

void Environment::drawHut() {
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glColor3f(0.55, 0.55, 0.57);
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	gluCylinder(quadratic, 2, 2, 4, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 0, -7);
	glColor3f(0.5, 0.5, 0);
	gluCylinder(quadratic, 0, 3, 4, 32, 32);
	glPopMatrix();
}

void Environment::addSurface(vector<BezierSurface> surf){
  for(unsigned int i=0; i<surf.size(); i++)
    this->surf.push_back(surf[i]);
}

void Environment::drawSurface(){
  for(unsigned int i=0; i<surf.size(); i++){
          glPushMatrix();
          float scale=100.0/12;
          glScalef(scale,scale,scale);
          glTranslatef(0,-1.95,0);
          surf[i].renderGrid();
          surf[i].renderSurface();
          glPopMatrix();
  }
}

void Environment::addCurve(Bezier curve){
  this->track=curve;
}

void Environment::drawCurve(){
  glPushMatrix();
	glTranslatef(0,3,0);
        glScalef(4,4,4);
        track.renderPoints();
	track.renderCage();
	track.renderCurve();
  glPopMatrix();
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
