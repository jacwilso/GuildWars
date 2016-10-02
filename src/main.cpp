/*
*  CSCI 441, Computer Graphics, Fall 2015
*
*  Project: GuildWars
*  File: main.cpp
*/

#ifdef __APPLE__			// if compiling on Mac OS
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else					// else compiling on Linux OS
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

// Other Libraries
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <map>

// Created Classes
#include "utilities/Camera.h"
#include "utilities/Environment.h"
#include "jacwilso/Board.h"
#include "jacwilso/Bomberman.h"
#include "kentokamoto/EricCartman.h"
#include "kentokamoto/FairyEric.h"
#include "zhemingdeng/Donkey.h"
#include "zhemingdeng/Fairy.h"

// Namespaces

using namespace std;

// GLOBAL VARIABLES ////////////////////////////////////////////////////////////
static size_t windowWidth  = 640;
static size_t windowHeight = 480;
static float aspectRatio;

GLint leftMouseButton; 		   	    // status of the mouse buttons
int mouseX = 0, mouseY = 0;                 // last known X and Y of the mouse
int pipMouseX = 0, pipMouseY = 0;			// Save for Picture in Picture section
float pipTheta, pipPhi;		// Theta and Phi values for PIP

bool isPip = false;
bool ctrlIsPressed = false;


int pipMode = 1;
map<unsigned char,bool> keyState;

Environment env;
GLUquadric* Environment::qobj;

Board board;
GLUquadric* Board::qobj;

Bomberman bomberman;
GLUquadric* Bomberman::qobj;
/********************* Functions ****************************/

void recomputeOrientation() {

}

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


void mouseCallback(int button, int state, int thisX, int thisY) {
	// update the left mouse button states, if applicable

}
void myMenu( int value ) {
	switch (value){
		case 0:
			exit(0);
			break;
		case 1:
			break;
		case 2:
			break;
		default:
			break;
	}
}

void createMenus() {
	glutCreateMenu( myMenu );
	glutAddMenuEntry( "Quit", 0 );
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void mouseMotion(int x, int y) {

	glutPostRedisplay();	    // redraw our scene from our new camera POV
}


void normalKeysDown(unsigned char key, int x, int y) {
        keyState[key]=true;
	if(key <= 57 && key >= 48){
		pipMode = (int)key - 48;
	}

	if(key == 'q' || key == 'Q' || key == 27){
		exit(0);
	}else if( key == 'w'){
	}else if( key == 's'){
	}else if(key == 'a'){
	}else if(key == 'd'){
	}
	glutPostRedisplay();		// redraw our scene from our new camera POV
}

void normalKeysUp(unsigned char key, int x, int y){
  keyState[key]=false;
}

// Special key being pressed like arrowkeys

void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_LEFT:
		break;
		case GLUT_KEY_RIGHT:
		break;
		case GLUT_KEY_UP:
		break;
		case GLUT_KEY_DOWN:
		break;
	}
	glutPostRedisplay();
}

// Timer function
void myTimer( int value ){

	glutPostRedisplay();
	glutTimerFunc( 1000/60, myTimer, 0);
}

void initScene()  {
	glEnable(GL_DEPTH_TEST);

	//******************************************************************
	// this is some code to enable a default light for the scene;
	// feel free to play around with this, but we won't talk about
	// lighting in OpenGL for another couple of weeks yet.
	float lightCol[4] = { 1, 1, 1, 1};
	float ambientCol[4] = { 0.0, 0.0, 0.0, 1.0 };
	float lPosition[4] = { 10, 10, 10, 1 };
	glLightfv( GL_LIGHT0, GL_POSITION,lPosition );
	glLightfv( GL_LIGHT0, GL_DIFFUSE,lightCol );
	glLightfv( GL_LIGHT0, GL_AMBIENT, ambientCol );
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );

	// tell OpenGL not to use the material system; just use whatever we 
	// pass with glColor*()
	glEnable( GL_COLOR_MATERIAL );
	glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
	//******************************************************************

	glShadeModel(GL_FLAT);

	srand( time(NULL) );	// seed our random number generator
	env.generateEnvironmentDL();
}

// renderScene() ///////////////////////////////////////////////////////////////
//
//  GLUT callback for scene rendering. Sets up the modelview matrix, renders
//      a scene to the back buffer, and switches the back buffer with the
//      front buffer (what the user sees).
//
////////////////////////////////////////////////////////////////////////////////
void renderScene(void)  {
	//clear the render buffer
	glDrawBuffer( GL_BACK );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//First Viewport: Take up the entire screen
	glViewport(0,0,windowWidth,windowHeight);
	//update the modelview matrix based on the camera's position
	glMatrixMode(GL_MODELVIEW);              //make sure we aren't changing the projection matrix!
	glLoadIdentity();

	// Viewport 2
	//PictureInPicture();

	//push the back buffer to the screen
	glutSwapBuffers();
}

// main() //////////////////////////////////////////////////////////////////////
//
//  Program entry point. Does not process command line arguments.
//
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
	
	// create a double-buffered GLUT window at (50,50) with predefined windowsize
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(windowWidth,windowHeight);
	glutCreateWindow("GuildWars");

	// give the camera a scenic starting point.
	pipTheta = M_PI/1.25;
	pipPhi = M_PI*0.7;

	// register callback functions...
	glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);
	glutKeyboardFunc(normalKeysDown);
	glutDisplayFunc(renderScene);
	glutReshapeFunc(resizeWindow);
	glutMouseFunc(mouseCallback);
	glutMotionFunc(mouseMotion);
	glutTimerFunc( 1000/60, myTimer, 0);
	// Special Function for Arrow Keys
	glutSpecialFunc(SpecialKeys);

	// do some basic OpenGL setup
	initScene();

	createMenus();
	// and enter the GLUT loop, never to exit.
	glutMainLoop();

	return(0);
}
