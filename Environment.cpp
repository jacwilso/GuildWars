#include "Environment.h"
/*
 * Constructor
 */
Environment::Environment(){}
/*
 * Used to initially generate the invironment into the environmentDL variable
 */
void Environment::generateEnvironmentDL(std::ifstream& inFile) {
		environmentDL = glGenLists( 1 );

		// Tell openGL to begin displaying lists
		glNewList( environmentDL, GL_COMPILE );
		// Draw the figures
		glPushMatrix(); {
				placeObjectsInEnvironment(inFile);
				drawCurve();
				drawSurface();
				trackBox();
				trackRoad();
		}; glPopMatrix();
		// Tell openGL to end displayiung lists
		glEndList();
}
/*
 * Places the tree and hut in environement according to the the input file
 */
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

				glPushMatrix();
				{
						float uVector = (0.01)* objectX +  1;
						float vVector = (-0.01) * objectZ + 1;
						int bezierListIndex = 2*((int)floor(vVector)) + (int)floor(uVector);
						Point surfPos = surf[bezierListIndex].evaluateSurface(uVector - floor(uVector) ,vVector - floor(vVector)); 
						Point axis=surf[bezierListIndex].rotationAxis(uVector - floor(uVector) ,vVector - floor(vVector));
						float surfAngle=surf[bezierListIndex].rotationAngle(uVector - floor(uVector) ,vVector - floor(vVector));

						glTranslatef(objectX,( surfPos.getY()-1.95)*100.0/12, objectZ);
						glRotatef(surfAngle,axis.getX(), 0, axis.getZ());
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

/*
 * Draws a flat grid. Not used in this project
 */
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
/*
 * Draws a flat ground. Not used in this project
 */
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
/*
 * Draws a tree object
 */
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
/*
 * Draws a hut object
 */
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
/*
 * Adds the bezier surface
 */
void Environment::addSurface(vector<BezierSurface> surf){
		for(unsigned int i=0; i<surf.size(); i++)
				this->surf.push_back(surf[i]);
}
/*
 * Draws the bezier surface
 */
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
/*
 * Adds the track
 */
void Environment::addCurve(Bezier curve){
		this->track=curve;
}
/*
 * Draw Curve
 */
void Environment::drawCurve(){
		glPushMatrix();
		glTranslatef(0,10,0);
		Point surfPos;
		float uVector, vVector;
		glDisable(GL_LIGHTING);
		glColor3f(0,0,1.0f);
		glLineWidth(3.0f);
		glBegin(GL_LINE_STRIP);
		for(unsigned int j=0; j<track.pSize(); j++){ // goes through each bezier curve if multiple joined
				for(int i=0; i<=track.resolution(); i++){ 
						Point temp=track.evaluateCurve(4*j,(float)(i)/track.resolution());

						uVector = (0.01)* temp.getX() +  1;
						vVector = (-0.01) * temp.getZ() + 1;
						int bezierListIndex = 2*((int)floor(vVector)) + (int)floor(uVector);
						surfPos = surf[bezierListIndex].evaluateSurface(uVector - floor(uVector) ,vVector - floor(vVector)); 
						//glVertex3f(surfPos.getX()*100.0/12,(surfPos.getY()-2)*50.0,surfPos.getZ()*100.0/12);
						glVertex3f(surfPos.getX()*100.0/12,(surfPos.getY())*10.0,surfPos.getZ()*100.0/12);
				}
		}
		glEnd();
		glEnable(GL_LIGHTING);
		glPopMatrix();
}
/*
 * Draws a box to be placed on track
 */
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
/*
 * Adds the boxes to the track
 */
void Environment::trackBox(){
		Point tmpC, tmpD, surfPos;
		float uVector, vVector, theta;
		for(int arc=0; arc<track.resSize(); arc+=30){
				tmpC=track.arcLengthCurve(arc);
				uVector = (0.01)* tmpC.getX() +  1;
				vVector = (-0.01) * tmpC.getZ() + 1;
				int bezierListIndex = 2*((int)floor(vVector)) + (int)floor(uVector);

				surfPos = surf[bezierListIndex].evaluateSurface(uVector - floor(uVector) ,vVector - floor(vVector)); 
				//Point tmp(surfPos.getX()*100.0/12,(surfPos.getY()-2)*20.0,surfPos.getZ()*100.0/12);
				Point tmp(surfPos.getX()*100.0/12,(surfPos.getY())*10.0,surfPos.getZ()*100.0/12);
				tmpD=track.arcDerivative(arc);
				theta=atan2(tmpD.getX(),tmpD.getZ())*180/3.1415;
				glPushMatrix();
				glTranslatef(0,10,0);
				glTranslatef(tmp.getX(),(tmp.getY()-2),tmp.getZ());
				glRotatef(theta,0,1,0);
				glScalef(.4,.4,.4);
				drawBox();
				glPopMatrix();
		}
}
/*
 * Draws crappy rainbow road
 */
void Environment::trackRoad(){
		Point tmpC, tmpD, surfPos;
		float uVector, vVector, theta;
		for(int arc=0; arc<track.resSize(); arc++){
				tmpC=track.arcLengthCurve(arc);
				uVector = (0.01)* tmpC.getX() +  1;
				vVector = (-0.01) * tmpC.getZ() + 1;
				int bezierListIndex = 2*((int)floor(vVector)) + (int)floor(uVector);

				surfPos = surf[bezierListIndex].evaluateSurface(uVector - floor(uVector) ,vVector - floor(vVector)); 
				//Point tmp(surfPos.getX()*100.0/12,(surfPos.getY()-2)*20.0,surfPos.getZ()*100.0/12);
				Point tmp(surfPos.getX()*100.0/12,(surfPos.getY())*10.0,surfPos.getZ()*100.0/12);
				Point axis=surf[bezierListIndex].rotationAxis(uVector - floor(uVector) ,vVector - floor(vVector));
				float surfAngle=surf[bezierListIndex].rotationAngle(uVector - floor(uVector) ,vVector - floor(vVector));
				tmpD=track.arcDerivative(arc);
				theta=atan2(tmpD.getX(),tmpD.getZ())*180/3.1415;
				glPushMatrix();
				glColor3f(rand()%10/100.0,rand()%10/100.0,rand()%10/100.0);
				glTranslatef(0,8,0);
				glTranslatef(tmp.getX(),(tmp.getY()-2),tmp.getZ());
				glRotatef(surfAngle,axis.getX(),axis.getY(),axis.getZ());
				glRotatef(90+theta,0,1,0);
				glScalef(1,.1,5);
				glutSolidCube(1);
				glPopMatrix();
		}
}
