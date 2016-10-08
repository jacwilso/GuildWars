/*
 *  CSCI 441, Computer Graphics, Fall 2015
 *
 *  Project: a4
 *  File: main.cpp
 *
 *	Author: Zheming Deng - Fall 2016
 *
 *  Description:
 *      Contains the base code for 3D Bezier Curve visualizer.
 *
 */

// HEADERS /////////////////////////////////////////////////////////////////////

// OpenGL / GLUT Libraries we need
#ifdef __APPLE__			// if compiling on Mac OS
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else					// else compiling on Linux OS
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glui.h>			// include our GLUI header
	
#endif

//#include <glui.h>			// include our GLUI header


// C Libraries we need
#include <time.h>			// for time() to seed our RNG
#include <stdio.h>			// allow to print to terminal
#include <stdlib.h>			// access to rand() and exit()
#include <math.h>			// for cosf(), sinf(), etc.


// C++ Libraries we'll use
#include <fstream>			// we'll use ifstream	
#include <string>			// for, well strings!
#include <vector>			// and vectors (the storage container, not directional)
#include <iostream>
#include <cstring>
#include <sstream>
using namespace std;


// Headers We've Written
#include "Point.h"
#include "Camera.h"

#include "Bezier.h"
#include "BezierSurface.h"


// GLOBAL VARIABLES ////////////////////////////////////////////////////////////

static size_t windowWidth = 640;
static size_t windowHeight = 480;
static float aspectRatio;

GLint leftMouseButton, rightMouseButton;    // status of the mouse buttons
bool leftCtrlMouse = false;                 // store if we are holding control down while we clicked
int mouseX = 0, mouseY = 0;                 // last known X and Y of the mouse

float cameraX, cameraY, cameraZ;            // camera position in cartesian coordinates
float cameraTheta, cameraPhi;               // camera DIRECTION in spherical coordinates
float dirX, dirY, dirZ;                     // camera DIRECTION in cartesian coordinates

GLint menuId;		// handle for our menu

static int numOfConPoints=0;
int** arr=new int*[numOfConPoints];// = new int[3][numOfConPoints]; //store control points

GLuint environmentDL;                       // display list for the 'city'

const int RESOLUTION = 100;
int numPoints;

//variable below are all for our "hero"
static float charPosX = 0;
static float charPosZ = 0;
static int charRotateAngle = 0;
//the index for fairy's position
//static int index = 0;
static float tailRotateAngle = 0.0;

static bool thirdPersonViewOn = false;
static bool controlCageOn = true;
static bool bezierCurveOn = true;

Camera* camera; //create a new camera Object

// PICKING
#define PICK_TOL          10.               // picking tolerance in pixels
#define PICK_BUFFER_SIZE  256               // how big to make the pick buffer
unsigned int PickBuffer[PICK_BUFFER_SIZE];  // picking buffer
int RenderMode;                             // GL_RENDER or GL_SELECT
int Nhits, dx, dy, nitems, zmin, zmax, item, d;
GLint GrWindow;
bool Debug = false;
vector<bool> pick;

BezierSurface surf;

enum {

	MENU_EXIT=1,
	MENU_HIDECONTCAGE,
	MENU_HIDEBEZIER
};

vector<Point> controlPoints;
vector<Point> bezierPoints;
float trackPointVal = 0.0f;



// getRand() ///////////////////////////////////////////////////////////////////
//
//  Simple helper function to return a random number between 0.0f and 1.0f.
//
////////////////////////////////////////////////////////////////////////////////
float getRand() {
    return rand() / (float)RAND_MAX;
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
	glDisable(GL_LIGHTING);

	// draw our grid....what? triple nested for loops!  crazy!  but it works :)
	glColor3f(1, 1, 1);
	glLineWidth(2.0f);	// make our grid lines a little thicker so they are easier to see
	for (int dir = 0; dir < 2; dir++) {
		for (int i = -5; i < 6; i++) {
			glBegin(GL_LINE_STRIP); {
				for (int j = -5; j < 6; j++)
					glVertex3f(dir < 1 ? i : j,
						0,
						dir < 1 ? j : i);
			}; glEnd();
		}
	}
	glLineWidth(1.0f);  // but be sure to set our line width back to its original size so we don't mess up future drawing

						/*
						*	As noted above, we are done drawing with OpenGL Primitives, so we
						*	must turn lighting back on.
						*/
	glEnable(GL_LIGHTING);
}

// drawCity() //////////////////////////////////////////////////////////////////
//
//  Function to draw a random city using GLUT 3D Primitives
//
////////////////////////////////////////////////////////////////////////////////
void drawCity() {
	// TODO #4: Randomly place buildings of varying heights with random colors


	for (float positionX = -49;positionX <= 50;positionX++) {
		for (float positionZ = -49;positionZ <= 50;positionZ++) {
			float threshold = getRand();
			if (threshold < 0.1) {
				float height = getRand() * 10;
				glBegin(GL_QUADS);
				glColor3f(0.25, 0.3, 0.8);

				//bottom face
				glVertex3f(positionX - 1, 0, positionZ - 1);
				glVertex3f(positionX, 0, positionZ - 1);
				glVertex3f(positionX, 0, positionZ);
				glVertex3f(positionX - 1, 0, positionZ);

				//top face
				glVertex3f(positionX - 1, height, positionZ - 1);
				glVertex3f(positionX, height, positionZ - 1);
				glVertex3f(positionX, height, positionZ);
				glVertex3f(positionX - 1, height, positionZ);

				//right face
				glVertex3f(positionX, 0, positionZ - 1);
				glVertex3f(positionX, 0, positionZ);
				glVertex3f(positionX, height, positionZ);
				glVertex3f(positionX, height, positionZ - 1);

				//front face
				glVertex3f(positionX, 0, positionZ);
				glVertex3f(positionX - 1, 0, positionZ);
				glVertex3f(positionX - 1, height, positionZ);
				glVertex3f(positionX, height, positionZ);

				//left face
				glVertex3f(positionX - 1, 0, positionZ);
				glVertex3f(positionX - 1, 0, positionZ - 1);
				glVertex3f(positionX - 1, height, positionZ - 1);
				glVertex3f(positionX - 1, height, positionZ);

				//back face
				glVertex3f(positionX - 1, 0, positionZ - 1);
				glVertex3f(positionX - 1, height, positionZ - 1);
				glVertex3f(positionX, height, positionZ - 1);
				glVertex3f(positionX, 0, positionZ - 1);

				glEnd();
			}
		}
	}
}

void computeArcballPosition(float theta, float phi, float radius,
	float &x, float &y, float &z) {
	x = radius * sinf(theta)*sinf(phi);
	y = radius * -cosf(phi);
	z = radius * -cosf(theta)*sinf(phi);
}

void drawTail() {
	glColor3f(128, 0, 128);
	GLUquadricObj *tail;
	tail = gluNewQuadric();
	gluCylinder(tail, 0.25, 0.25, 1, 16, 16);
}

void drawHead() {
	glColor3f(128, 0, 128);
	GLUquadricObj *head;
	head = gluNewQuadric();
	gluCylinder(head, 0.4, 0.6, 2, 16, 16);
}
void drawWheels() {
	glColor3f(255, 0, 255);
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	gluCylinder(quadratic, 0.5, 0.5, 4, 16, 16);

}

void drawNeck() {
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

void drawBody() {

	glColor3f(255, 255, 255);
	glutSolidCube(2.0);
}

void drawSphere() {
	for (int i = 0;i < numOfConPoints;i++) {

		glPushMatrix();
		glTranslatef(controlPoints.at(i).getX(), controlPoints.at(i).getY(), controlPoints.at(i).getZ());
		glutSolidSphere(0.15, 16, 16);
		glPopMatrix();
	}
}

void drawLines() {
	for (int i = 0;i < numOfConPoints - 1;i++) {
		glLineWidth(3.0);
		glColor3f(255, 255, 0);
		glBegin(GL_LINES);
		glPushMatrix();
		glVertex3f(controlPoints.at(i).getX(), controlPoints.at(i).getY(), controlPoints.at(i).getZ());
		glVertex3f(controlPoints.at(i + 1).getX(), controlPoints.at(i + 1).getY(), controlPoints.at(i + 1).getZ());
		glPopMatrix();
		glEnd();
	}
}

void drawBezierLine(Point p1, Point p2) {
	glColor3f(0, 0, 255);
	glBegin(GL_LINES);
	glVertex3f(p1.getX(), p1.getY(), p1.getZ());
	glVertex3f(p2.getX(), p2.getY(), p2.getZ());
	glEnd();
}

// evaluateBezierCurve() ////////////////////////////////////////////////////////
//
// Computes a location along a Bezier Curve. 
//
////////////////////////////////////////////////////////////////////////////////
Point evaluateBezierCurve(Point p0, Point p1, Point p2, Point p3, float t) {
	// TODO #08: Compute a point along a Bezier curve

	float px = pow((1 - t), 3)*p0.getX() + 3 * t*pow((1 - t), 2)*p1.getX() +
		3 * (1 - t)*pow(t, 2)*p2.getX() + pow(t, 3)*p3.getX();
	float py = pow((1 - t), 3)*p0.getY() + 3 * t*pow((1 - t), 2)*p1.getY() +
		3 * (1 - t)*pow(t, 2)*p2.getY() + pow(t, 3)*p3.getY();
	float pz = pow((1 - t), 3)*p0.getZ() + 3 * t*pow((1 - t), 2)*p1.getZ() +
		3 * (1 - t)*pow(t, 2)*p2.getZ() + pow(t, 3)*p3.getZ();
	Point* p = new Point(px, py, pz);
	return *p;
}

// renderBezierCurve() //////////////////////////////////////////////////////////
//
// Responsible for drawing a Bezier Curve as defined by four control points.
//  Breaks the curve into n segments as specified by the resolution. 
//
////////////////////////////////////////////////////////////////////////////////
void renderBezierCurve(Point p0, Point p1, Point p2, Point p3, int resolution) {
	// TODO #07: Draw a Bezier curve
	Point old = p0;
	bezierPoints.push_back(p0);
	Point last = p0;
	for (float t = 0.0; t <= resolution;t += 0.1) {
		Point p = evaluateBezierCurve(p0, p1, p2, p3, t);

		//push bezier curve points into vector
		bezierPoints.push_back(p);

		//draw line between two bezier points
		drawBezierLine(old, p);
		old = p;
		last = p;
	}
	//
	bezierPoints.push_back(p3);
	//make up the last segment
	drawBezierLine(last, p3);
}

void drawFairy() {
	
	//glPushMatrix();
	glColor3f(0.28, 0.85, 0.12);
	//glTranslatef(bezierPoints[index].getX(), bezierPoints[index]getY(), bezierPoints[index].getZ());
	//glutSolidSphere(0.25, 16, 16);
	//glPopMatrix();
}


void drawCharacter() {
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
	
	if (controlCageOn == true) {
		//draw sphere
		glPushMatrix();
		glColor3f(0.5, 0.8, 0.4);
		drawSphere();
		glPopMatrix();

		// TODO #06: Connect our control points
		glPushMatrix();
		drawLines();
		glPopMatrix();
	}
	
	// TODO #07: Draw the Bezier Curve!
	if (bezierCurveOn == true) {
		glPushMatrix();
		if (numOfConPoints <= 4) {
			renderBezierCurve(controlPoints.at(0), controlPoints.at(1), controlPoints.at(2), controlPoints.at(3), 1);
		}
		else {
			renderBezierCurve(controlPoints.at(0), controlPoints.at(1), controlPoints.at(2), controlPoints.at(3), 1);
			renderBezierCurve(controlPoints.at(3), controlPoints.at(4), controlPoints.at(5), controlPoints.at(6), 1);
		}
		glPopMatrix();
	}

	//Draw the fairy
	glPushMatrix();
	  drawFairy();
	glPopMatrix();
}


// generateEnvironmentDL() /////////////////////////////////////////////////////
//
//  This function creates a display list with the code to draw a simple 
//      environment for the user to navigate through.
//
//  And yes, it uses a global variable for the display list.
//  I know, I know! Kids: don't try this at home. There's something to be said
//      for object-oriented programming after all.
//
////////////////////////////////////////////////////////////////////////////////
void generateEnvironmentDL() {
	// TODO #1 Create a Display List & Call our Drawing Functions

	//request a valid display list handle from OpenGL
	//environmentDL = glGenLists(1);

	//tell OpenGL to begin a display list
	//glNewList(environmentDL, GL_COMPILE);
	//glPushMatrix(); {
		//drawCity();
	//}; glPopMatrix();
	//glPushMatrix();
	//drawGrid();
	//glPopMatrix();

	//glEndList();

}

// recomputeOrientation() //////////////////////////////////////////////////////
//
// This function updates the camera's position in cartesian coordinates based 
//  on its position in spherical coordinates. Should be called every time 
//  cameraTheta, cameraPhi, or cameraRadius is updated. 
//
////////////////////////////////////////////////////////////////////////////////
void recomputeOrientation() {
	dirX = sinf(cameraTheta)*sinf(cameraPhi);
	dirZ = -cosf(cameraTheta)*sinf(cameraPhi);
	dirY = -cosf(cameraPhi);

	//and normalize this directional vector!
	float mag = sqrt(dirX*dirX + dirY*dirY + dirZ*dirZ);
	dirX /= mag;  dirY /= mag;  dirZ /= mag;

	glutPostRedisplay();
}

void recomputePosition() {
	camera->setCameraX((camera->getCameraRadius())*sinf(camera->getCameraTheta())
		*sinf(camera->getCameraPhi()));
	camera->setCameraY((camera->getCameraRadius())*-cosf(camera->getCameraPhi()));
	camera->setCameraZ((camera->getCameraRadius())*-cosf(camera->getCameraTheta())
		*sinf(camera->getCameraPhi()));
}


// resizeWindow() //////////////////////////////////////////////////////////////
//
//  GLUT callback for window resizing. Resets GL_PROJECTION matrix and viewport.
//
////////////////////////////////////////////////////////////////////////////////
void resizeWindow(int w, int h) {
    aspectRatio = w / (float)h;

    windowWidth = w;
    windowHeight = h;

    //update the viewport to fill the window
    glViewport(0, 0, w, h);

    //update the projection matrix with the new window properties
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,aspectRatio,0.1,100000);
}

// renderScene() ///////////////////////////////////////////////////////////////
//
//  GLUT callback for scene rendering. Sets up the modelview matrix, renders
//      a scene to the back buffer, and switches the back buffer with the
//      front buffer (what the user sees).
//
////////////////////////////////////////////////////////////////////////////////
void renderScene(void) {
	// clear the render buffer
	glDrawBuffer(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// update the modelview matrix based on the camera's position
	//glMatrixMode( GL_MODELVIEW );                           // make sure we aren't changing the projection matrix!
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	dx = glutGet(GLUT_WINDOW_WIDTH);
	dy = glutGet(GLUT_WINDOW_HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (RenderMode == GL_SELECT) {
		gluPickMatrix(double(mouseX), (double)(dy - mouseY), PICK_TOL, PICK_TOL, viewport);
	}

	gluPerspective(45.0, aspectRatio, 0.1, 100000);

	glMatrixMode(GL_MODELVIEW);                           // make sure we aren't changing the projection matrix!
	glLoadIdentity();

	gluLookAt(cameraX, cameraY, cameraZ,                  // camera is located at (x,y,z)
		0, 0, 0,   // camera is looking at at (x,y,z) + (dx,dy,dz) -- straight ahead
		0.0f, 1.0f, 0.0f);                            // up vector is (0,1,0) (positive Y)

	if (RenderMode == GL_SELECT) {
		glInitNames();
	}

	//gluLookAt(camera->getCameraX(), camera->getCameraY(), camera->getCameraZ(),                  // camera is located at (x,y,z)
	//camera->getCameraX() + camera->getDirX(), camera->getCameraY() + camera->getDirY()
	//, camera->getCameraZ() + camera->getDirZ(),   // camera is looking at at (x,y,z) + (dx,dy,dz) -- straight ahead
	//camera->getVectorX(), camera->getVectorY(), camera->getVectorZ());  // up vector is (0,1,0) (positive Y)

	//draw grid and city
	//glCallList(environmentDL);

	//draw character
	//drawCharacter();

	//start from below copied from Jacob bezierDemo
	//DRAW HERE
	surf.renderGrid();
	surf.renderSurface();

	float u = (float)(0) / 100, v = (float)(10) / 100;
	Point temp = surf.evaluateSurface(u, v);
	Point axis = surf.rotationAxis(u, v);
	float surfAngle = surf.rotationAngle(u, v);
	//float surfTheta=surf.rotationTheta(u,v);
	//float surfPhi = surf.rotationPhi(u,v);

	Point norm = surf.normal(u, v);
	//cout<<surfAngle<<endl;
	glDisable(GL_LIGHTING);

	glPushMatrix();
	glColor3f(1, 1, 1);

	glTranslatef(temp.getX(), temp.getY(), temp.getZ());
	glRotatef(surfAngle, axis.getX(), axis.getY(), axis.getZ());
	//glRotatef(surfPhi, 0,1,0);
	//glRotatef(surfTheta,0,0,1);
	//glRotatef(surfAngle, 0,0,1);	
	//glutSolidSphere(0.1,20,20);
	//glScalef(.25,2,.25);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);

	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	//glVertex3f(surf.normal(u,v).getX(),surf.normal(u,v).getY(),surf.normal(u,v).getZ());
	//glVertex3f(surf.normal(u,v).getX()*2,-surf.normal(u,v).getY()*2,surf.normal(u,v).getZ()*2);
	glEnd();
	//glutSolidCube(1);

	glPopMatrix();
	glEnable(GL_LIGHTING);

	glPushMatrix(); {
		//drawGrid();
	}; glPopMatrix();

	// TODO #05: Draw our control points


	//push the back buffer to the screen
	glutSwapBuffers();
}

// mouseCallback() /////////////////////////////////////////////////////////////
//
//  GLUT callback for mouse clicks. We save the state of the mouse button
//      when this is called so that we can check the status of the mouse
//      buttons inside the motion callback (whether they are up or down).
//
////////////////////////////////////////////////////////////////////////////////
void mouseCallback(int button, int state, int thisX, int thisY) {
	//and update the last seen X and Y coordinates of the mouse
	mouseX = thisX;
	mouseY = thisY;

	if (button == GLUT_LEFT_BUTTON && glutGetModifiers() == GLUT_ACTIVE_SHIFT && state == GLUT_DOWN) {
		RenderMode = GL_SELECT;
		glRenderMode(RenderMode);
		renderScene();
		renderScene();
		RenderMode = GL_RENDER;
		Nhits = glRenderMode(RenderMode);
#ifdef BUG_KLUDGE
		if (Nhits == 0) {
			RenderMode = GL_SELECT;
			glRenderMode(RenderMode);
			renderScene();
			RenderMode = GL_RENDER;
			Nhits = glRenderMode(RenderMode);
		}
#endif 
		if (Debug)
			fprintf(stderr, "# pick hits = %d\n", Nhits);
		if (Nhits == 0)
			for (int k = 0; k<numPoints; k++)
				pick[k] = false;
		bool picked = false;
		for (int i = 0, index = 0; i<Nhits; i++) {
			//printf("\n");
			nitems = PickBuffer[index++];
			zmin = PickBuffer[index++];
			zmax = PickBuffer[index++];
			if (Debug && nitems != 0) {
				fprintf(stderr, "Hit # %2d: found %2d items on the name stack\n", i, nitems);
				fprintf(stderr, "\tZmin = 0x%0x, Zmax = 0x%0x\n", zmin, zmax);
			}
			for (int j = 0; j<nitems; j++) {
				picked = true;
				item = PickBuffer[index++];
				for (int k = 0; k<numPoints; k++)
					pick[k] = false;
				pick[item - 1] = true;
				if (Debug)
					fprintf(stderr, "\t%2d: %6d\n", j, item);
			}
			if (!picked)
				for (int k = 0; k<numPoints; k++)
					pick[k] = false;
		}
		glutSetWindow(GrWindow);
		glutPostRedisplay();
	}

	//update the left and right mouse button states, if applicable
	else if (button == GLUT_LEFT_BUTTON)
		leftMouseButton = state;
}

// mouseMotion() ///////////////////////////////////////////////////////////////
//
//  GLUT callback for mouse movement. We update cameraPhi, cameraTheta, and/or
//      cameraRadius based on how much the user has moved the mouse in the
//      X or Y directions (in screen space) and whether they have held down
//      the left or right mouse buttons. If the user hasn't held down any
//      buttons, the function just updates the last seen mouse X and Y coords.
//
////////////////////////////////////////////////////////////////////////////////
void mouseMotion(int x, int y) {
	if (leftMouseButton == GLUT_DOWN && !leftCtrlMouse) {
		camera->setCameraThe(camera->getCameraTheta() + (x - mouseX)*0.005);
		camera->setCameraPhi(camera->getCameraPhi() + (mouseY - y)*0.005);

		// make sure that phi stays within the range (0, M_PI)
		if (camera->getCameraPhi() <= 0)
			camera->setCameraPhi(0 + 0.001);
		if (camera->getCameraPhi() >= M_PI)
			camera->setCameraPhi(M_PI - 0.001);

		recomputeOrientation();   //update camera (x,y,z) based on (radius,theta,phi)
	}
	else if (leftMouseButton == GLUT_DOWN && leftCtrlMouse) {
		if (leftMouseButton == GLUT_DOWN) {
			cameraTheta += (x - mouseX)*0.005;
			cameraPhi += (mouseY - y)*0.005;

			// make sure that phi stays within the range (0, M_PI)
			if (cameraPhi <= 0)
				cameraPhi = 0 + 0.001;
			if (cameraPhi >= M_PI)
				cameraPhi = M_PI - 0.001;

			recomputeOrientation();     //update camera (x,y,z) based on (radius,theta,phi)
		}

		mouseX = x;
		mouseY = y;
	}
}


// initScene() /////////////////////////////////////////////////////////////////
//
//  A basic scene initialization function; should be called once after the
//      OpenGL context has been created. Doesn't need to be called further.
//
////////////////////////////////////////////////////////////////////////////////
void initScene()  {
	glEnable(GL_DEPTH_TEST);

	//******************************************************************
	// this is some code to enable a default light for the scene;
	// feel free to play around with this, but we won't talk about
	// lighting in OpenGL for another couple of weeks yet.
	float lightCol[4] = { 1, 1, 1, 1 };
	float ambientCol[4] = { 0.0, 0.0, 0.0, 1.0 };
	float lPosition[4] = { 10, 10, 10, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, lPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightCol);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientCol);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// tell OpenGL not to use the material system; just use whatever we 
	// pass with glColor*()
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	//******************************************************************

	// PICKING
	glInitNames();
	RenderMode = GL_RENDER;

	glShadeModel(GL_FLAT);

	srand(time(NULL));	// seed our random number generator

						// give the camera a scenic starting point.
	cameraX = 9;
	cameraY = 14;
	cameraZ = 8;
	cameraTheta = -M_PI / 3.0f;
	cameraPhi = M_PI / 2.8f;
	recomputeOrientation();
}




// normalKeysDown() ////////////////////////////////////////////////////////////
//
//  GLUT keyboard callback; gets called when the user presses a key.
//
////////////////////////////////////////////////////////////////////////////////
void normalKeysDown( unsigned char key, int x, int y ) {
	if (key == 'q' || key == 'Q' || key == 27)
		exit(0);

	// because the direction vector is unit length, and we probably don't want
	// to move one full unit every time a button is pressed, just create a constant
	// to keep track of how far we want to move at each step. you could make
	// this change w.r.t. the amount of time the button's held down for
	// simple scale-sensitive movement!
	float movementConstant = 0.3f;

	// move forward!
	if (key == 'w' || key == 'W') {
		//that's as simple as just moving along the direction.
		cameraX += dirX*movementConstant;
		cameraY += dirY*movementConstant;
		cameraZ += dirZ*movementConstant;
	}

	// move backwards!
	else if (key == 's' || key == 'S') {
		//just move BACKWARDS along the direction.
		cameraX -= dirX*movementConstant;
		cameraY -= dirY*movementConstant;
		cameraZ -= dirZ*movementConstant;
	}
}

void specialKeysDown(int key, int x, int y) {
	int point = -1;
	for (int i = 0; i<numPoints; i++)
		if (pick[i] == true) point = i;
	if (point != -1) {
		if (key == GLUT_KEY_UP) {
			controlPoints[point] += Point(0, 1, 0);
		}
		if (key == GLUT_KEY_DOWN)
			controlPoints[point] -= Point(0, 1, 0);
		if (key == GLUT_KEY_LEFT && glutGetModifiers() == GLUT_ACTIVE_CTRL)
			controlPoints[point] += Point(0, 0, 1);
		else if (key == GLUT_KEY_LEFT)
			controlPoints[point] -= Point(1, 0, 0);
		if (key == GLUT_KEY_RIGHT && glutGetModifiers() == GLUT_ACTIVE_CTRL)
			controlPoints[point] -= Point(0, 0, 1);
		else if (key == GLUT_KEY_RIGHT)
			controlPoints[point] += Point(1, 0, 0);
	}
}

// myTimer() ////////////////////////////////////////////////////////////////////
//
//  GLUT timer callback; gets called when a timer expires
//
////////////////////////////////////////////////////////////////////////////////
void myTimer( int value ) {
	// redraw our display
	glutPostRedisplay();
	// register a new timer callback
	glutTimerFunc(1000.0f / 60.0f, myTimer, 0);
}

// myMenu() /////////////////////////////////////////////////////////////////////
//
//  Handles our Menu events
//
////////////////////////////////////////////////////////////////////////////////
void myMenu( int value ) {
	// TODO #02: handle our menu options
	switch (value) {
	case 0: exit(0);
	}
}

// createMenus() ///////////////////////////////////////////////////////////////
//
//  Handles creating a menu, adding menu entries, and attaching the menu to
//  a mouse button
//
////////////////////////////////////////////////////////////////////////////////
void createMenus() {
	// TODO #01: Create a Simple Menu
	glutCreateMenu(myMenu);
	glutAddMenuEntry("Quit", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	//return menuId;
}

// registerCallbacks() /////////////////////////////////////////////////////////
//
//  Register all of our callbacks for GLUT.
//
////////////////////////////////////////////////////////////////////////////////
void registerCallbacks() {
    // keyboard callbacks
    glutSetKeyRepeat(   GLUT_KEY_REPEAT_ON );
    glutKeyboardFunc(   normalKeysDown     );
	glutSpecialFunc(specialKeysDown);

    // mouse callbacks
    glutMouseFunc(      mouseCallback      );
    glutMotionFunc(     mouseMotion        );

    // display callbacks
    glutDisplayFunc(    renderScene        );
    glutReshapeFunc(    resizeWindow       );

    // timer callback
	glutTimerFunc(1000.0f / 60.0f, myTimer, 0);
}

// loadControlPoints() /////////////////////////////////////////////////////////
//
//  Load our control points from file and store them in a global variable.
//
////////////////////////////////////////////////////////////////////////////////
bool loadControlPoints(char* filename) {
	string str = string(filename);
	//cout << str;
	ifstream file(filename);
	string line;
	//get the first line for the number of control points
	getline(file, line);
	stringstream convert(line);
	convert >> numPoints;
	cout << "Num of control Points " << numPoints << endl;

	//char c;
	float tempX, tempY, tempZ;
	//Bezier Bezier;
	vector<Point> tempP;
	vector<Bezier> tempBez;

	while (getline(file, line) ){
		stringstream ss(line);
		float i;
		vector<float> vect;
		while (ss >> i) {
			vect.push_back(i);
			if (ss.peek() == ',')
				ss.ignore();
		}
		tempX = vect.at(0);
		tempY = vect.at(1);
		tempZ = vect.at(2);
		tempP.push_back(Point(tempX, tempY, tempZ));
	}

	for (int i = 0; i<numPoints * 4; i++)
		tempBez.push_back(Bezier(tempP[4 * i], tempP[4 * i + 1], tempP[4 * i + 2], tempP[4 * i + 3])); // pushes each set of 4 points into a bezier vector
	for (int i = 0; i<numPoints; i++)
		surf.createSurface(tempBez[4 * i], tempBez[4 * i + 1], tempBez[4 * i + 2], tempBez[4 * i + 3]);

	return true; // was able to read the file
}

// main() //////////////////////////////////////////////////////////////////////
//
//  Program entry point. Takes a single command line argument for our 
//    control points file.
//
////////////////////////////////////////////////////////////////////////////////
int main( int argc, char **argv ) {

    // TODO #03: make sure a control point CSV file was passed in.  Then read the points from file
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <CSV_NAME>" << endl;
		return 0;
	}
	loadControlPoints(argv[1]);

	
	
	//delete[] writable;// don't forget to free the string after finished using it

    // create a double-buffered GLUT window at (50, 50) with predefined window size
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowPosition( 50, 50 );
    glutInitWindowSize( windowWidth, windowHeight );
    glutCreateWindow( "Lab03 - Bezier Curves" );
	glSelectBuffer(PICK_BUFFER_SIZE, PickBuffer);

    fprintf(stdout, "[INFO]: /--------------------------------------------------------\\\n");
    fprintf(stdout, "[INFO]: | OpenGL Information                                     |\n");
    fprintf(stdout, "[INFO]: |--------------------------------------------------------|\n");
    fprintf(stdout, "[INFO]: |   OpenGL Version:  %35s |\n", glGetString(GL_VERSION));
    fprintf(stdout, "[INFO]: |   OpenGL Renderer: %35s |\n", glGetString(GL_RENDERER));
    fprintf(stdout, "[INFO]: |   OpenGL Vendor:   %35s |\n", glGetString(GL_VENDOR));
    //fprintf(stdout, "[INFO]: |   GLUI Version:    %35.2f |\n", GLUI_VERSION);
    fprintf(stdout, "[INFO]: \\--------------------------------------------------------/\n");

    // do some basic OpenGL setup
    initScene();

    // create our menu options and attach to mouse button
    createMenus();
	//glutAttachMenu(GLUT_RIGHT_BUTTON);

    // register callback functions...
    registerCallbacks();

    // and enter the GLUT loop, never to exit.
    glutMainLoop();

    return(0);
}
