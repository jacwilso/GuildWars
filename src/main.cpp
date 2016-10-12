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
const float SPLITSCREEN_HEIGHT_RATIO = 3;
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
vector<BezierSurface> surf;
Bezier track;
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

/*** MENU OPTIONS ***/
int ericMenu, donkeyMenu, boardMenu, screen1Menu, screen2Menu, screen3Menu, mainMenu;
bool screen2On = false;
bool screen3On = false;
bool fpsOn = false;
int screen1SubjectNumber = 0;
int screen2SubjectNumber = 1;
int screen3SubjectNumber = 2;

/*** temporary ***/
Point arcPos, paramPos;
float boardTheta, donkeyTheta;
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

void animationTrack(bool parametric){
		Point tmpC, tmpD;
		Point surfPos;
		float uVector, vVector;
		if(parametric){
				tmpC=track.parametricCurve(param);
				uVector = (0.01)* tmpC.getX() +  1;
				vVector = (-0.01) * tmpC.getZ() + 1;
				int bezierListIndex = 2*((int)floor(vVector)) + (int)floor(uVector);
				surfPos = surf[bezierListIndex].evaluateSurface(uVector - floor(uVector) ,vVector - floor(vVector)); 
				//Point tmp(surfPos.getX()*100.0/12,(surfPos.getY()-2)*20.0,surfPos.getZ()*100.0/12);
				Point tmp(surfPos.getX()*100.0/12,(surfPos.getY())*10.0,surfPos.getZ()*100.0/12);
				tmpD=track.paramDerivative(param);
				donkeyTheta=atan2(tmpD.getX(),tmpD.getZ())*180/3.1415;
				param++;
				if(param+1>track.resSize()) param=0;
				paramPos=tmp;
		}else{
				tmpC=track.arcLengthCurve(arc);
				//cout<<"TEMP: "<<temp.getX()<<", "<<temp.getZ()<<endl<<"ARC++ "<<arc<<endl;
				uVector = (0.01)* tmpC.getX() +  1;
				vVector = (-0.01) * tmpC.getZ() + 1;
				int bezierListIndex = 2*((int)floor(vVector)) + (int)floor(uVector);
				surfPos = surf[bezierListIndex].evaluateSurface(uVector - floor(uVector) ,vVector - floor(vVector)); 
				Point tmp(surfPos.getX()*100.0/12,(surfPos.getY())*10.0,surfPos.getZ()*100.0/12);
				tmpD=track.arcDerivative(arc);
				boardTheta=atan2(tmpD.getX(),tmpD.getZ())*180/3.1415;
				arc++;
				if(arc+1>track.resSize()) arc=0;
				arcPos=tmp;
		}

}

float nameAngle(Point pos){
		Point dif=pos-cam.getCameraPos();
		dif.normalize();
		Point camDir=cam.getDir();
		camDir.normalize();
		float dot=dif.getX()*camDir.getX()+dif.getY()*camDir.getY()+dif.getZ()*camDir.getZ();
		return 180-acos(dot)*180/3.1415;
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
void processEricMenu( int value ) {
		screen1SubjectNumber = 0;
		switch (value){
				case 0: // Arcball
						cam.setViewMode(6);
						break;
				case 1: // 1st Person
						cam.setViewMode(2);
						break;
				case 2: // SkyCam
						cam.setViewMode(4);
						break;
						break;
				default:
						break;
		}
}
void processBoardMenu( int value ) {
		screen1SubjectNumber = 1;
		switch (value){
				case 0:
						cam.setViewMode(6);
						break;
				case 1:
						cam.setViewMode(2);
						break;
				case 2:
						cam.setViewMode(4);
						break;
				default:
						break;
		}
}
void processDonkeyMenu( int value ) {
		screen1SubjectNumber = 2;
		switch (value){
				case 0:
						cam.setViewMode(6);
						break;
				case 1:
						cam.setViewMode(2);
						break;
				case 2:
						cam.setViewMode(4);
						break;
				default:
						break;
		}
}

void processScreen1Menu(int value){
		screen1SubjectNumber = value/3;
		switch(value%3){
				case 0:
						cam.setViewMode(6);
						break;
				case 1:
						cam.setViewMode(2);	
						break;
				case 2:
						cam.setViewMode(4);
						break;
				default:
						cam.setViewMode(6);
						break;
		}
}

void processScreen2Menu(int value){
		screen2SubjectNumber = value/3;
		switch(value%3){
				case 0:
						cam2.setViewMode(6);
						break;
				case 1:
						cam2.setViewMode(2);	
						break;
				case 2:
						cam2.setViewMode(4);
						break;
				default:
						cam2.setViewMode(6);
						break;
		}
}

void processScreen3Menu(int value){
		screen3SubjectNumber = value/3;
		switch(value%3){
				case 0:
						cam3.setViewMode(6);
						break;
				case 1:
						cam3.setViewMode(2);	
						break;
				case 2:
						cam3.setViewMode(4);
						break;
				default:
						cam3.setViewMode(6);
						break;
		}
}

void processMainMenu(int value){
		switch (value){
				case 1:
						screen2On = !screen3On;
						screen3On = !screen3On;
						if(screen3On == false){
								glutChangeToMenuEntry(1,"Turn SplitScreen ON",1);
								glutChangeToSubMenu(5,"Eric Cartman", ericMenu);
								glutChangeToSubMenu(6,"Board", boardMenu);
								glutChangeToSubMenu(7,"Donkey", donkeyMenu);
						}else{
								glutChangeToMenuEntry(1,"Turn SplitScreen OFF",1);
								glutChangeToSubMenu(5,"Main Screen", screen1Menu );
								glutChangeToSubMenu(6, "Screen 2", screen2Menu);
								glutChangeToSubMenu(7, "Screen 3", screen3Menu);

						}
						break;
				case 2:
						cam.setViewMode(0);
						break;
				case 3:
						fpsOn = !fpsOn;
						if(fpsOn == false){
								glutChangeToMenuEntry(3,"Turn FPS ON",3);
						}else{
								glutChangeToMenuEntry(3,"Turn FPS OFF",3);
						}
						break;
				case 4:
						exit(0);
						break;
				default:
						break;
		}
}
void createMenus() {
		ericMenu = glutCreateMenu( processEricMenu );
		glutAddMenuEntry( "Eric: ArcBall", 0);
		glutAddMenuEntry( "Eric: 1st Person", 1);
		glutAddMenuEntry( "Eric: SkyCam", 2);

		boardMenu = glutCreateMenu(processBoardMenu);
		glutAddMenuEntry( "Board: ArcBall", 0);
		glutAddMenuEntry( "Board: 1st Person", 1);
		glutAddMenuEntry( "Board: SkyCam", 2);

		donkeyMenu = glutCreateMenu(processDonkeyMenu);
		glutAddMenuEntry( "Donkey: ArcBall", 0);
		glutAddMenuEntry( "Donkey: 1st Person", 1);
		glutAddMenuEntry( "Donkey: SkyCam", 2);	

		screen1Menu = glutCreateMenu(processScreen1Menu);
		glutAddMenuEntry( "Eric: ArcBall", 0);
		glutAddMenuEntry( "Eric: 1st Person", 1);
		glutAddMenuEntry( "Eric: SkyCam", 2);
		glutAddMenuEntry( "Board: ArcBall", 3);
		glutAddMenuEntry( "Board: 1st Person", 4);
		glutAddMenuEntry( "Board: SkyCam", 5);
		glutAddMenuEntry( "Donkey: ArcBall", 6);
		glutAddMenuEntry( "Donkey: 1st Person", 7);
		glutAddMenuEntry( "Donkey: SkyCam", 8);	
		screen2Menu = glutCreateMenu(processScreen2Menu);
		glutAddMenuEntry( "Eric: ArcBall", 0);
		glutAddMenuEntry( "Eric: 1st Person", 1);
		glutAddMenuEntry( "Eric: SkyCam", 2);
		glutAddMenuEntry( "Board: ArcBall", 3);
		glutAddMenuEntry( "Board: 1st Person", 4);
		glutAddMenuEntry( "Board: SkyCam", 5);
		glutAddMenuEntry( "Donkey: ArcBall", 6);
		glutAddMenuEntry( "Donkey: 1st Person", 7);
		glutAddMenuEntry( "Donkey: SkyCam", 8);	
		screen3Menu = glutCreateMenu(processScreen3Menu);
		glutAddMenuEntry( "Eric: ArcBall", 0);
		glutAddMenuEntry( "Eric: 1st Person", 1);
		glutAddMenuEntry( "Eric: SkyCam", 2);
		glutAddMenuEntry( "Board: ArcBall", 3);
		glutAddMenuEntry( "Board: 1st Person", 4);
		glutAddMenuEntry( "Board: SkyCam", 5);
		glutAddMenuEntry( "Donkey: ArcBall", 6);
		glutAddMenuEntry( "Donkey: 1st Person", 7);
		glutAddMenuEntry( "Donkey: SkyCam", 8);	

		mainMenu = glutCreateMenu(processMainMenu);
		glutAddMenuEntry( "Turn SplitScreen ON", 1 );

		glutAddMenuEntry("Free Cam", 2);
		glutAddMenuEntry("Turn FPS ON", 3);
		glutAddMenuEntry( "Quit",4);
		glutAddSubMenu("Eric Cartman", ericMenu);
		glutAddSubMenu("Board", boardMenu);
		glutAddSubMenu("Donkey", donkeyMenu);

		glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void mouseMotion(int x, int y) {
		if(leftMouseButton == GLUT_DOWN) {
				if(screen2On == false || screen3On == false){
						cam.setCameraTheta(cam.getCameraTheta() - (x-mouseX) * 0.005);
						cam.setCameraPhi(fmin(fmax((cam.getCameraPhi() + (y - mouseY) * 0.005),0.01),M_PI));
						mouseX = x;
						mouseY = y;

						cam.recomputeOrientation();     // update camera (x,y,z) based on (radius,theta,phi)


				}else{

						if(mouseX <=(signed int) windowWidth/2 && (windowHeight-mouseY) <= windowHeight/SPLITSCREEN_HEIGHT_RATIO ){
								cam2.setCameraTheta(cam2.getCameraTheta() - (x-mouseX) * 0.005);
								cam2.setCameraPhi(fmin(fmax((cam2.getCameraPhi() + (y - mouseY) * 0.005),0.01),M_PI));
								mouseX = x;
								mouseY = y;
								cam2.recomputeOrientation();

						}else if(mouseX >(signed int) windowWidth/2 && (windowHeight-mouseY) <= windowHeight/SPLITSCREEN_HEIGHT_RATIO ){

								cam3.setCameraTheta(cam3.getCameraTheta() - (x-mouseX) * 0.005);
								cam3.setCameraPhi(fmin(fmax((cam3.getCameraPhi() + (y - mouseY) * 0.005),0.01),M_PI));					
								mouseX = x;
								mouseY = y;
								cam3.recomputeOrientation();

						}else{
								cam.setCameraTheta(cam.getCameraTheta() - (x-mouseX) * 0.005);
								cam.setCameraPhi(fmin(fmax((cam.getCameraPhi() + (y - mouseY) * 0.005),0.01),M_PI));
								mouseX = x;
								mouseY = y;

								cam.recomputeOrientation();     // update camera (x,y,z) based on (radius,theta,phi)

						}
				}
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
				// Use x and z 
				// to get the height at that slope

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
		// FREE CAM
		if(cam.getViewMode()==0){
				if(keyState['i'] || keyState['I']) cam.moveForward();
				if(keyState['k'] || keyState['K']) cam.moveBackward();
				if(keyState['j'] || keyState['J']) cam.setCameraTheta(cam.getCameraTheta() - 0.05);
				if(keyState['l'] || keyState['L']) cam.setCameraTheta(cam.getCameraTheta() + 0.05);
				cam.recomputeOrientation();
		}
		// Which quad is eric in?	
		Point surfPos;
		float uVector, vVector;

		uVector = (0.01)* ericCartman.getHeroPositionX() +  1;
		vVector = (-0.01) * ericCartman.getHeroPositionZ() + 1;
		int bezierListIndex = 2*((int)floor(vVector)) + (int)floor(uVector);
		//std::cout << uVector << " " << bezierListIndex << " " << vVector << std::endl;
		surfPos = surf[bezierListIndex].evaluateSurface(uVector - floor(uVector) ,vVector - floor(vVector)); 
		ericCartman.setHeroPos(ericCartman.getHeroPositionX(), (surfPos.getY()-1.59)*100.0/12  , ericCartman.getHeroPositionZ(), ericCartman.getHeroTheta(), ericCartman.getHeroPhi());


		Point axis=surf[bezierListIndex].rotationAxis(uVector - floor(uVector) ,vVector - floor(vVector));
		float surfAngle=surf[bezierListIndex].rotationAngle(uVector - floor(uVector) ,vVector - floor(vVector));
		ericCartman.setRotAxisX(axis.getX());
		ericCartman.setRotAxisZ(axis.getZ());	
		//std::cout << ericCartman.getHeroPositionX() << " "<< "" << " " << ericCartman.getHeroPositionZ() << std::endl;
		ericCartman.setHeroPos(ericCartman.getHeroPositionX(), (surfPos.getY()-1.59)*100.0/12  , ericCartman.getHeroPositionZ(), ericCartman.getHeroTheta(), surfAngle);
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
		board.animate();
		donkey.animate();

		animationTrack(false);
		animationTrack(true);


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
		glViewport(0,0,windowWidth/2, windowHeight/SPLITSCREEN_HEIGHT_RATIO );


		// Portions within the scissor can now be modified.
		glScissor(0,0,windowWidth/2, windowHeight/SPLITSCREEN_HEIGHT_RATIO );
		glEnable(GL_SCISSOR_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDisable( GL_SCISSOR_TEST);


		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0, (float) (windowWidth/2)/(windowHeight/SPLITSCREEN_HEIGHT_RATIO), 0.1, 100000);
		glMatrixMode(GL_MODELVIEW);

		/*glPushMatrix();
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
		  }*/
		glPopMatrix();
		glLoadIdentity();
}

void View3(){
		glViewport(windowWidth/2, 0, windowWidth/2, windowHeight/SPLITSCREEN_HEIGHT_RATIO );


		// Portions within the scissor can now be modified.
		glScissor(windowWidth/2, 0, windowWidth/2, windowHeight/SPLITSCREEN_HEIGHT_RATIO );
		glEnable(GL_SCISSOR_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDisable( GL_SCISSOR_TEST);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0, (float) (windowWidth/2)/(windowHeight/SPLITSCREEN_HEIGHT_RATIO), 0.1, 100000);
		glMatrixMode(GL_MODELVIEW);



		/*glPushMatrix();
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
		  glMatrixMode(GL_MODELVIEW);*/
		glLoadIdentity();
}

void drawCharacters(){
		const char* c;
		/*
		   Point temp=surf.evaluateSurface(u,v);
		   Point axis=surf.rotationAxis(u,v);
		   float surfAngle=surf.rotationAngle(u,v);
		   Point norm = surf.normal(u,v);
		   */
		glPushMatrix();
		// TRACK
		  glTranslatef(0,10,0);
		  //glScalef(4,4,4);
		  // BOARD
		  glPushMatrix();
		    glTranslatef(arcPos.getX(),arcPos.getY(),arcPos.getZ());
		    glRotatef(boardTheta+90,0,1,0);
		    //glScalef(.25,.25,.25);
		    board.drawHero();
		    glDisable(GL_LIGHTING);
		    glPushMatrix();
		      glColor3f(1,1,1);
		      glTranslatef(-2,1,0);
                      glScalef(.01,.01,.01);
		      for(c="jacwilso"; *c!='\0'; c++)
		    		glutStrokeCharacter(StrFont,*c);
		    glPopMatrix();
		    glEnable(GL_LIGHTING);
		  glPopMatrix();
		  // DONKEY
		  glPushMatrix();
		    glTranslatef(paramPos.getX(),paramPos.getY(),paramPos.getZ());
		    //glScalef(.25,.25,.25);
		    glRotatef(donkeyTheta-180,0,1,0);
		    donkey.drawHero();
		    glDisable(GL_LIGHTING);
		    glPushMatrix();
		      glColor3f(1,1,1);
		      glTranslatef(-4,3.5,0);
		      //glRotatef(nameAngle(paramPos),0,1,0);
		      glScalef(.01,.01,.01);
		      for(c="zhemingdeng"; *c!='\0'; c++)
		    		glutStrokeCharacter(StrFont,*c);
		    glPopMatrix();
		    glEnable(GL_LIGHTING);
		  glPopMatrix();
		glPopMatrix();
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

		if(screen1SubjectNumber == 0){
				cam.setSubjectPosition(ericCartman.getHeroPositionX(),ericCartman.getHeroPositionY(), ericCartman.getHeroPositionZ(), ericCartman.getHeroTheta());
		}else if(screen1SubjectNumber == 1){
				cam.setSubjectPosition(4*arcPos.getX(), 4*arcPos.getY(), 4*arcPos.getZ(), boardTheta);
		}else if(screen1SubjectNumber == 2){
				cam.setSubjectPosition(4*paramPos.getX() + 10,4*paramPos.getY() + 3, 4*paramPos.getZ()+10, donkeyTheta);
		}

		cam.setCamera();

		glPushMatrix();
		glTranslatef(40,0,40);
		glutSolidTeapot(1);
		glPopMatrix();

		ericCartman.drawHero();
		drawCharacters();
		glCallList( env.environmentDL );

		if(fpsOn == true){
				drawFPS();
		}

		if(screen2On == true){
				if(screen2SubjectNumber == 0){
						cam2.setSubjectPosition(ericCartman.getHeroPositionX(),ericCartman.getHeroPositionY(), ericCartman.getHeroPositionZ(), ericCartman.getHeroTheta());
				}else if(screen2SubjectNumber == 1){
						cam2.setSubjectPosition(4*arcPos.getX(), 4*arcPos.getY(), 4*arcPos.getZ(), boardTheta);
				}else if(screen2SubjectNumber == 2){
						cam2.setSubjectPosition(4*paramPos.getX() + 10,4*paramPos.getY() + 3, 4*paramPos.getZ()+10, donkeyTheta);
				}
				/*** Viewport 2 ***/
				View2();
				cam2.setCamera();
				ericCartman.drawHero();
				drawCharacters();
				//surf.renderGrid();
				//surf.renderSurface();
				if(fpsOn == true){
						drawFPS();
				}
				glCallList( env.environmentDL );

		}
		if(screen3On == true){
				if(screen3SubjectNumber == 0){
						cam3.setSubjectPosition(ericCartman.getHeroPositionX(),ericCartman.getHeroPositionY(), ericCartman.getHeroPositionZ(), ericCartman.getHeroTheta());
				}else if(screen2SubjectNumber == 1){
						cam3.setSubjectPosition(4*arcPos.getX(), 4*arcPos.getY(), 4*arcPos.getZ(), boardTheta);
				}else if(screen2SubjectNumber == 2){
						cam3.setSubjectPosition(4*paramPos.getX() + 10,4*paramPos.getY() + 3, 4*paramPos.getZ()+10, donkeyTheta);
				}
				/*** Viewport 3 ***/
				View3();
				cam3.setCamera();
				ericCartman.drawHero();
				drawCharacters();
				glCallList( env.environmentDL );
				//surf.renderGrid();
				//surf.renderSurface();

		}

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
		BezierSurface tempSurf;

		/*** READ SURFACE ***/
		file>>numPoints; // number of points

		for(int i=0; i<numPoints*16; i++){
				file>>tempX>>c>>tempY>>c>>tempZ;
				tempP.push_back(Point(tempX,tempY,tempZ)); // pushes each value into a point into a vector
		}
		for(int i=0; i<numPoints*4; i++){
				tempBez.push_back(Bezier(tempP[4*i],tempP[4*i+1],tempP[4*i+2],tempP[4*i+3])); // pushes each set of 4 points into a bezier vector
		}
		for(int i=0; i<numPoints; i++){
				tempSurf.createSurface(tempBez[4*i],tempBez[4*i+1],tempBez[4*i+2],tempBez[4*i+3]);
				surf.push_back(tempSurf);
		}
		env.addSurface(surf);

		/*** READ TRACKS ***/
		tempP.clear();
		file>>numPoints;
		for(int i=0; i<numPoints; i++){
				file>>tempX>>c>>tempY>>c>>tempZ;
				tempP.push_back(Point(tempX,tempY,tempZ)); // pushes each value into a point into a vector
		}
		for(int i=0; i<numPoints-3; i+=3)
				track.bezierConnect(Bezier(tempP[i],tempP[i+1],tempP[i+2],tempP[i+3])); // pushes each set of 4 points into a bezier vector
		env.addCurve(track);

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
