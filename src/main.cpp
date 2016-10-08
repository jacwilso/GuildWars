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

#include <AL/alut.h>  // OpenAL Headers
#include <AL/al.h>
#include <AL/alc.h>

// Other Libraries
#include <iostream>
#include <sstream>
#include <string.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <map>

// Created Classes
#include "utilities/Camera.h"
#include "utilities/Sound.h"
#include "utilities/Environment.h"
#include "utilities/BezierSurface.h"
#include "utilities/Bezier.h"
#include "utilities/Point.h"

#include "utilities/Sound.h"
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
static size_t windowHeight = 720;
static float aspectRatio;

GLint leftMouseButton; 		   	    // status of the mouse buttons
int mouseX = 0, mouseY = 0;                 // last known X and Y of the mouse
int pipMouseX = 0, pipMouseY = 0;			// Save for Picture in Picture section
float pipTheta, pipPhi;		// Theta and Phi values for PIP

bool isPip = false;
bool ctrlIsPressed = false;

/*** FPS ***/
int frameCount = 0, currentTime = 0, previousTime = 0;
float fps = 0;
void *RasFont = GLUT_BITMAP_HELVETICA_18;
void *StrFont = GLUT_STROKE_ROMAN;
char* cstr;

int pipMode = 1;
map<unsigned char,bool> keyState;

/*** Bezier ***/
const int RESOLUTION=100;
vector<Point> controlPoints;
BezierSurface surf;
Bezier bez[2];
int arc = 0, param = 0;

/*** Models ***/
Environment env;
GLUquadric* Environment::qobj;
/****************** Characters **************************/

Board board;
GLUquadric* Board::qobj;

Bomberman bomberman;
GLUquadric* Bomberman::qobj;

Donkey donkey;

/*** UTILITIES ***/
EricCartman ericCartman;
Camera cam, cam2, cam3;
Sound wav;
ifstream file;
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

void calculateFPS(){
	frameCount++;
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	int timeInterval = currentTime - previousTime;
	if(timeInterval > 1000){
		fps = frameCount/(timeInterval/1000.0f);
		previousTime=currentTime;
		frameCount=0;
	}
}

void bitmapText(const char *string,float x,float y,float z){
	const char* c;
	glRasterPos3f(x,y,z);
	for(c=string; *c!='\0'; c++){
		glutBitmapCharacter(RasFont,*c);
	}
}

char* floatToChar(float i){
	ostringstream ss;
	ss << i;
	string str = ss.str();
	cstr = new char[str.length()-1];
	strcpy(cstr,str.c_str());
	return cstr;
} 

void drawFPS(){
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0,windowWidth,0,windowHeight);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1,1,1);
	bitmapText("FPS: ",20,20,0);
	glColor3f(1,1,1);
	bitmapText(floatToChar(fps),100,20,0);
	delete cstr;
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}

void animationTrack(Hero& hero, Bezier curve, bool parametric){
	Point temp;
	if(parametric){
		temp=curve.parametricCurve(param);
		param++;
		if(param+1>curve.resSize()) param=0;
	}else{
		temp=curve.parametricCurve(arc);
    //temp=curve.arcLengthCurve(arc);
		arc++;
		if(arc+1>curve.resSize()) arc=0;
	}
  //hero.setHeroPos(temp.getX(),0,temp.getZ(),0,0);
}

void mouseCallback(int button, int state, int thisX, int thisY) {
		// update the left mouse button states, if applicable
	if(button == GLUT_LEFT_BUTTON){
		leftMouseButton = state;
		if(leftMouseButton == GLUT_DOWN){
			mouseX = thisX;
			mouseY = thisY;
		}
	}

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
	glutAddMenuEntry( "Toggle Eric 1st Person POV", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void mouseMotion(int x, int y) {
	if(leftMouseButton == GLUT_DOWN) {
		if(mouseX <= windowWidth/2 && (windowHeight-mouseY) <= windowHeight/2.5){
			cam2.setCameraTheta(cam2.getCameraTheta() - (x-mouseX) * 0.005);
			cam2.setCameraPhi(fmin(fmax((cam2.getCameraPhi() + (y - mouseY) * 0.005),0.01),M_PI));
		}else if(mouseX > windowWidth/2 && (windowHeight-mouseY) <= windowHeight/2.5){
			cam3.setCameraTheta(cam3.getCameraTheta() - (x-mouseX) * 0.005);
			cam3.setCameraPhi(fmin(fmax((cam3.getCameraPhi() + (y - mouseY) * 0.005),0.01),M_PI));					
		}else{
			cam.setCameraTheta(cam.getCameraTheta() - (x-mouseX) * 0.005);
			cam.setCameraPhi(fmin(fmax((cam.getCameraPhi() + (y - mouseY) * 0.005),0.01),M_PI));
		}
		mouseX = x;
		mouseY = y;
				cam.recomputeOrientation();     // update camera (x,y,z) based on (radius,theta,phi)
				cam2.recomputeOrientation();
				cam3.recomputeOrientation();
			}


		glutPostRedisplay();	    // redraw our scene from our new camera POV
	}


	void normalKeysDown(unsigned char key, int x, int y) {
		keyState[key]=true;
		if(key <= 57 && key >= 48){
			cam.setViewMode((int)key - 48);
		}

		if(key == 'q' || key == 'Q' || key == 27){
			exit(0);
		}		glutPostRedisplay();		// redraw our scene from our new camera POV
	}

	void normalKeysUp(unsigned char key, int x, int y){
		keyState[key]=false;
		if( !keyState['w'] || !keyState['W'] ||
			!keyState['s'] || !keyState['S'] ||
			!keyState['a'] || !keyState['A'] ||
			!keyState['d'] || !keyState['D']  )
			alSourcePause( wav.sources[1] );
	}

	void normalKeys(){
		if( keyState['w'] || keyState['W']){
			ericCartman.moveEricForward();
			ALenum sourceState;
			alGetSourcei( wav.sources[1], AL_SOURCE_STATE, &sourceState );
			if(sourceState != AL_PLAYING){
				alSourcePlay( wav.sources[1] );
			}
		}
		if(keyState['s'] || keyState['S']){
			ericCartman.moveEricBackward();
			ALenum sourceState;
			alGetSourcei( wav.sources[1], AL_SOURCE_STATE, &sourceState );
			if(sourceState != AL_PLAYING)
				alSourcePlay( wav.sources[1] );
		}
		if(keyState['a'] || keyState['A']){
			ericCartman.turnEricLeft();
			ALenum sourceState;
			alGetSourcei( wav.sources[1], AL_SOURCE_STATE, &sourceState );
			if(sourceState != AL_PLAYING)
				alSourcePlay( wav.sources[1] );
		}
		if(keyState['d'] || keyState['D']){
			ericCartman.turnEricRight();
			ALenum sourceState;
			alGetSourcei( wav.sources[1], AL_SOURCE_STATE, &sourceState );
			if(sourceState != AL_PLAYING)
				alSourcePlay( wav.sources[1] );
		}

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
		normalKeys();
		calculateFPS();
		ericCartman.animate();
		animationTrack(board,bez[0],false);
		animationTrack(donkey,bez[1],true);

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
	env.generateEnvironmentDL(file);
}
void View2(){
	glViewport(0,0,windowWidth/2, windowHeight/2);


		// Portions within the scissor can now be modified.
	glScissor(0,0,windowWidth/2, windowHeight/2);
	glEnable(GL_SCISSOR_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable( GL_SCISSOR_TEST);


	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	{
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glColor3f(1,1,1);
		glLineWidth(5);
		glBegin(GL_LINE_LOOP);
		glVertex3f(-1,-1,0);
		glVertex3f(-1,1,0);
		glVertex3f(1,1,0);
		glVertex3f(1,-1,0);
		glEnd();
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}
	glPopMatrix();
	glLoadIdentity();
}

void View3(){
	glViewport(windowWidth/2, 0, windowWidth, windowHeight/2);


		// Portions within the scissor can now be modified.
	glScissor(windowWidth/2, 0, windowWidth, windowHeight/2);
	glEnable(GL_SCISSOR_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable( GL_SCISSOR_TEST);


	glMatrixMode(GL_MODELVIEW);


	glPushMatrix();
	{
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glColor3f(1,1,1);
		glLineWidth(5);
		glBegin(GL_LINE_LOOP);
		glVertex3f(-1,-1,0);
		glVertex3f(-1,1,0);
		glVertex3f(1,1,0);
		glVertex3f(1,-1,0);
		glEnd();
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void drawCharacters(){
	for(int i=0; i<2; i++){
		glPushMatrix();
		glTranslatef(-40+80*i,2,20*i);
		glScalef(4,4,4);
		bez[i].renderPoints();
		bez[i].renderCage();
		bez[i].renderCurve();
		if(i==0){
            //cout<<board.getHeroPositionZ()<<endl;
			glPushMatrix();
                //glTranslatef(board.getHeroPositionX(),board.getHeroPositionY(),board.getHeroPositionZ());
			glRotatef(board.getHeroTheta(),0,1,0);
			glScalef(.25,.25,.25);
			board.drawHero();
			glDisable(GL_LIGHTING);
			glPushMatrix();
			glColor3f(1,1,1);
			glTranslatef(-2,1,0);
			glScalef(.01,.01,.01);
			const char* c;
			for(c="jacwilso"; *c!='\0'; c++)
				glutStrokeCharacter(StrFont,*c);
			glPopMatrix();
			glEnable(GL_LIGHTING);
			glPopMatrix();
		}else{
			glPushMatrix();
			glTranslatef(donkey.getHeroPositionX(),donkey.getHeroPositionY(),donkey.getHeroPositionZ());
			glRotatef(donkey.getHeroTheta(),0,1,0);
			glScalef(.25,.25,.25);
			donkey.drawHero();
			glDisable(GL_LIGHTING);
			glPushMatrix();
			glColor3f(1,1,1);
			glTranslatef(-4,3.5,0);
			glScalef(.01,.01,.01);
			const char* c;
			for(c="zhemingdeng"; *c!='\0'; c++)
				glutStrokeCharacter(StrFont,*c);
			glPopMatrix();
			glEnable(GL_LIGHTING);
			glPopMatrix();
		}
		glPopMatrix();
	}
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
	wav.positionListener(ericCartman.getHeroPositionX(),ericCartman.getHeroPositionY(), ericCartman.getHeroPositionZ(),cam.getDirX(),cam.getDirY(),cam.getDirZ(),0,1,0);		
	wav.positionSource(wav.sources[1],ericCartman.getHeroPositionX(),ericCartman.getHeroPositionY(), ericCartman.getHeroPositionZ());
	cam.ArcBall(ericCartman.getHeroPositionX(),ericCartman.getHeroPositionY(), ericCartman.getHeroPositionZ());


	glPushMatrix();
	glTranslatef(40,0,40);
	glutSolidTeapot(1);
	glPopMatrix();


	ericCartman.drawHero();
	drawCharacters();
 //    surf.renderGrid();
 //    surf.renderSurface();
	glCallList( env.environmentDL );
	// Viewport 2
	//View2();
	//cam2.FreeCam();
	//ericCartman.drawHero();
	// drawCharacters();
 //    //surf.renderGrid();
 //    surf.renderSurface();
 //    drawFPS();
	//glCallList( env.environmentDL );
	// Viewport 3
	// View3();
	
	//  cam3.FreeCam();
	//  ericCartman.drawHero();
	// drawCharacters();
	glCallList( env.environmentDL );
	// //surf.renderGrid();
 //    surf.renderSurface();
	//push the back buffer to the screen
	glutSwapBuffers();
}

// loadControlPoints() /////////////////////////////////////////////////////////
//
//  Load our control points from file and store them in a global variable.
//
////////////////////////////////////////////////////////////////////////////////
bool loadControlPoints( char* filename ) {
	file.open(filename);
	if(!file.is_open()){
		cerr<<"ERROR. Could not find/ read file. Check spelling."<<endl;
		return false;
	}
	int numPoints;
	char c;
	float tempX,tempY,tempZ;
	vector<Point> tempP;
	vector<Bezier> tempBez;

  /*** READ SURFACE ***/
  file>>numPoints; // number of points

  for(int i=0; i<numPoints*16; i++){
  	file>>tempX>>c>>tempY>>c>>tempZ;
    tempP.push_back(Point(tempX,tempY,tempZ)); // pushes each value into a point into a vector
}
for(int i=0; i<numPoints*4; i++)
    tempBez.push_back(Bezier(tempP[4*i],tempP[4*i+1],tempP[4*i+2],tempP[4*i+3])); // pushes each set of 4 points into a bezier vector
for(int i=0; i<numPoints; i++)
	surf.createSurface(tempBez[4*i],tempBez[4*i+1],tempBez[4*i+2],tempBez[4*i+3]);

  /*** READ TRACKS ***/
for(int k=0; k<2; k++){
	tempP.clear();
	file>>numPoints;
	for(int i=0; i<numPoints; i++){
		file>>tempX>>c>>tempY>>c>>tempZ;
      tempP.push_back(Point(tempX,tempY,tempZ)); // pushes each value into a point into a vector
  }
  for(int i=0; i<numPoints-3; i+=3)
      bez[k].bezierConnect(Bezier(tempP[i],tempP[i+1],tempP[i+2],tempP[i+3])); // pushes each set of 4 points into a bezier vector
}


  /*** READ OBJECTS ***/
  // Pass file to environment class
  return true; // was able to read the file
}

void cleanSound(){
	wav.cleanupOpenAL();
}
// main() //////////////////////////////////////////////////////////////////////
//
//  Program entry point. Does not process command line arguments.
//
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
	
	if(argc!=2){
		cerr<<"Usage: "<<argv[0]<<" <CSV_NAME>"<<endl;
		return 0;
	}
	loadControlPoints(argv[1]);
	// create a double-buffered GLUT window at (50,50) with predefined windowsize
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(windowWidth,windowHeight);
	glutCreateWindow("GuildWars");
	wav.initializeOpenAL(argc,argv);
		// give the camera a scenic starting point.
	pipTheta = M_PI/1.25;
	pipPhi = M_PI*0.7;

		// register callback functions...
	glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);
	glutKeyboardFunc(normalKeysDown);
	glutKeyboardUpFunc( normalKeysUp);
	glutDisplayFunc(renderScene);
	glutReshapeFunc(resizeWindow);
	glutMouseFunc(mouseCallback);
	glutMotionFunc(mouseMotion);
	glutTimerFunc( 1000/60, myTimer, 0);
		// Special Function for Arrow Keys
	glutSpecialFunc(SpecialKeys);

	wav.positionSource(wav.sources[0],40,0,40);
		// do some basic OpenGL setup
		//env.placeObjectsInEnvironment(inFile);

	initScene();

	atexit( cleanSound);
	alSourcePlay( wav.sources[0] );

	createMenus();
				// and enter the GLUT loop, never to exit.
	glutMainLoop();

	return(0);
}
