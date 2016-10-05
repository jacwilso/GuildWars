/*
 *  CSCI 441, Computer Graphics, Fall 2015
 *
 *  Project: lab03
 *  File: main.cpp
 *
 *	Author: Dr. Jeffrey Paone - Fall 2015
 *
 *  Description:
 *      Contains the base code for 3D Bezier Curve visualizer.
 *
 */

// HEADERS /////////////////////////////////////////////////////////////////////

// OpenGL / GLUT Libraries we need
#ifdef __APPLE__			// if compiling on Mac OS
    #include <ALUT/alut.h>  // OpenAL Headers
    #include <OpenAL/al.h>
    #include <OpenAL/alc.h>

    #include <GLUT/glut.h>  // OpenGL Headers
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else                       // else compiling on Linux OS
    #include <AL/alut.h>    // OpenAL Headers
    #include <AL/al.h>
    #include <AL/alc.h>

    #include <GL/glut.h>    // OpenGL Headers
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include <GL/glui.h>			// include our GLUI header


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
#include <math.h>
using namespace std;


// Headers We've Written
#include "Point.h"
#include "Bezier.h"
#include "Environment.h"
#include "Board.h"
#include "Bomberman.h"
#include "Camera.h"
#include "Sound.h"

// GLOBAL VARIABLES ////////////////////////////////////////////////////////////

static size_t windowWidth = 640;
static size_t windowHeight = 480;
static float aspectRatio;

GLint leftMouseButton, rightMouseButton;    // status of the mouse buttons
int mouseX = 0, mouseY = 0;                 // last known X and Y of the mouse
int keyState[256];

/******** MENU ********/
GLint menuId;			// handle for our menu
bool displayPoints=true,displayCage=true,displayCurve=true,animateSprite=true,soundOn=true;

/******** ENVIRONMENT AND MOVEMENT ********/
const int BOUNDARY=50,SPEED=1,HEADING=4,STREAKS=25;
const float DEG_RAD=3.14159/180;

/****** BOARD ANIMATION VARIABLES *********/
float hoverPos=0,objTheta=0,lookAtX=0,lookAtY=10,lookAtZ=0;
bool hover=true,stomp=false,turn=false,bankLeft=false,bankRight=false;
float streak[STREAKS][3];
int streakNum=0;

/************ SPRITE POSITION *************/
float spriteX,spriteY,spriteZ;
int spritePos=0;

/****** Camera View ******/
int camera=1;

Environment env;
GLUquadric* Environment::qobj;
Board board;
GLUquadric* Board::qobj;
Bomberman bomber;
GLUquadric* Bomberman::qobj;
Camera cam;
Bezier bez;
Sound wav;

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
    

    env.generateEnvironmentDL(); // setup environment, bomber, board, and camera
    bomber.generateBombermanDL();
    board.setVars(lookAtX,lookAtY,lookAtZ,objTheta,hoverPos,stomp,turn,bankLeft,bankRight,streak,streakNum);
    cam.setCamera(10,10,10,-M_PI / 3.0f,M_PI / 2.8f,15,lookAtX,lookAtY,lookAtZ);
    cam.recomputeOrientation();
}

// renderScene() ///////////////////////////////////////////////////////////////
//
//  GLUT callback for scene rendering. Sets up the modelview matrix, renders
//      a scene to the back buffer, and switches the back buffer with the
//      front buffer (what the user sees).
//
////////////////////////////////////////////////////////////////////////////////
void renderScene(void)  {
    // clear the render buffer
    glDrawBuffer( GL_BACK );

    wav.positionListener(lookAtX,lookAtY,lookAtZ,cam.getDirX(),cam.getDirY(),cam.getDirZ(),0,1,0); // position the listener on the board

    wav.positionSource(wav.sources[0],lookAtX,lookAtY,lookAtZ); // position the hover sound on the board
    wav.positionSource(wav.sources[1],lookAtX+spriteX,lookAtY+spriteY,lookAtZ+spriteZ); // position the bomb on the sprite

    ALenum sourceState;
    alGetSourcei(wav.sources[0],AL_SOURCE_STATE,&sourceState);
    if(soundOn){ // if sound menu if on
      if(sourceState!=AL_PLAYING) // and the sound isn't already playing 
        alSourcePlay(wav.sources[0]); // play the sound
    } 
    else
      alSourceStop(wav.sources[0]); // else stop the sound

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


    // update the modelview matrix based on the camera's position
    glMatrixMode( GL_MODELVIEW );                           // make sure we aren't changing the projection matrix!
    glLoadIdentity();

    cam.setLookAt(lookAtX,lookAtY,lookAtZ); // set the camera's look at
    switch(camera){ // switch between the cameras
    case 1:
      cam.arcBall();
      break;
    case 2:
      cam.freeCam();
      break;
    case 3:
      cam.firstPerson(objTheta);
      break;
    case 4:
      cam.skyCam(objTheta);
      break;
    }

    glCallList(env.environmentDL); // generate the environment

    board.setVars(lookAtX,lookAtY,lookAtZ,objTheta,hoverPos,stomp,turn,bankLeft,bankRight,streak,streakNum); // set the board variables

    board.generateObjectDL(); // move and translate the board
    glCallList(board.objectDL); // generate and draw the board

    glPushMatrix(); // sprite/ bezier curve
      glTranslatef(lookAtX+2.4,lookAtY,lookAtZ); // move the sprite to be around the board
      glRotatef(27,0,1,0);
      glRotatef(objTheta,0,1,0); // roate the sprite to be facing the same direction as the board
      //glRotatef(36.8,1,0,1);
      glScalef(1.2,1.2,1.2); // scale the curve and sprite
      if(displayPoints)
        bez.renderPoints(); // control points
      if(displayCage)
        bez.renderCage(); // control cage
      if(displayCurve)
        bez.renderCurve(); // bezier curve
    glColor3f(1,1,1);
      glPushMatrix();
        //glTranslatef(0,6,0);
        glTranslatef(spriteX,spriteY,spriteZ); // sprite to follow the curve
        glScalef(.2,.2,.2); // scale the sprite
        glCallList(bomber.bombermanDL); // draw the sprite
      glPopMatrix();
    glPopMatrix();
  
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
    cam.setMouse(thisX,thisY);

  if(button == GLUT_LEFT_BUTTON)
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
    if(leftMouseButton == GLUT_DOWN){
      if(glutGetModifiers()==GLUT_ACTIVE_CTRL)
        cam.setCamR(x,y); // change the camera radius
      else{
        cam.setCamAngle(x,y); // change the camera angle
        cam.setMouse(x,y); // change the internal mouse position
      }
      cam.recomputeOrientation(); // recompute the camera properties
    }
}

// BoundarCondition() ///////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////////////
// check if the board is on the raised part of the map
void checkRaise(){
  if(lookAtZ>-10 && lookAtZ<10
  && lookAtX>-10 && lookAtX<10) lookAtY=2.5;
  else lookAtY=.8;
}

bool xBoundaryCondition(int dir){ // parameter dir is the direction the board is pointing
  if(dir*cos(objTheta*DEG_RAD)<0 && lookAtX>=BOUNDARY-4) //check the direction the board isn't pointing off the grid and the x isn't  greater than the grid
    return false;
  else if(dir*cos(objTheta*DEG_RAD)>0 && lookAtX<=-BOUNDARY+4) // check the direction the board isn't pointing off the grid and the x isn't less than the grid
    return false;
  return true;
}

// Z BOUNDARY CONDITION -- stop the user from going off the grid, z check
bool zBoundaryCondition(int dir){ // code same for Z as X, just substitue x for z.
  if(dir*sin(objTheta*DEG_RAD)>0 && lookAtZ>=BOUNDARY-4)
    return false;
  else if(dir*sin(objTheta*DEG_RAD)<0 && lookAtZ<=-BOUNDARY+4)
    return false;
  return true;
}

// normalKeysDown() ////////////////////////////////////////////////////////////
//
//  GLUT keyboard callback; gets called when the user presses a key.
//
////////////////////////////////////////////////////////////////////////////////
void normalKeysDown( unsigned char key, int x, int y ) {
    keyState[key]=true; // add the key to the keyState map if it isn't already, and set the value to true
    if( key == 'q' || key == 'Q' || key == 27 )
        exit(0);
    // move forward!
    // Camera type
    if(key=='`'){// cycle through
      if(camera<4) camera++; 
      else camera=1;
    }
    else if(key=='1') camera=1; // arc ball
    else if(key=='2') camera=2; // free cam
    else if(key=='3') camera=3; // first person cam
    else if(key=='4') camera=4; // sky cam
}

void specialKeys(int key, int x, int y){
  if(camera==2){ // if free cam -- change camera movement to arrow keys
    if(key==GLUT_KEY_UP) 
      cam.incCam(); // move forward
    if(key==GLUT_KEY_DOWN)
      cam.decCam(); // move backward
    if(key==GLUT_KEY_LEFT)
      cam.setCamAngle(-4,0); // change angle left
    if(key==GLUT_KEY_RIGHT)
      cam.setCamAngle(4,0); // change angle right
    cam.recomputeOrientation();
  }
}

void normalKeysUp(unsigned char key, int x, int y){
  keyState[key]=false; // add the key to the keyState map (is probably already included), and set the value to false
}

void normalKeys(){
  if(keyState['s']||keyState['w']){ // if 'w' or 's' are being pressed, compress the stomp pad (set true)
    stomp=true;
  }
  else stomp=false;

  if((keyState['a']||keyState['d'])&&!(keyState['s']||keyState['w'])) // if 'a' or 'd' and neither 'w' or 's' are being pressed the board is stationary turning
    turn=true;
  else turn=false;

  if(keyState['a']&&(keyState['s']||keyState['w'])) // if 'a' and forward/ backward movement occur, bank the board right
    bankRight=true;
  else bankRight=false;

  if(keyState['d']&&(keyState['s']||keyState['w'])) // if 'd' and forward/ backward movement occur, bank the board left
    bankLeft=true;
  else bankLeft=false;


  if(keyState['a']) // rotate the board 8 degrees left
    objTheta+=HEADING;
  if(keyState['d']) // rotate the board 8 degrees right
   objTheta-=HEADING;

  if(keyState['w']){ // move the board foward if board won't go out of x or z bounds
    if(xBoundaryCondition(1)) // x bound check
      lookAtX-=SPEED*cos(objTheta*DEG_RAD); // go the direction of the board not just 4 in the x, hence cos
    if(zBoundaryCondition(1)) // z bound check
      lookAtZ+=SPEED*sin(objTheta*DEG_RAD); // go the direction of the board not just 4 in the z, hence sin
  }

  if(keyState['s']){ // move the board backward if the board won't go out of x or z bounds
    if(xBoundaryCondition(-1))
      lookAtX+=SPEED*cos(objTheta*DEG_RAD);
    if(zBoundaryCondition(-1))
      lookAtZ-=SPEED*sin(objTheta*DEG_RAD);
  }
}

// myTimer() ////////////////////////////////////////////////////////////////////
//
//  GLUT timer callback; gets called when a timer expires
//
////////////////////////////////////////////////////////////////////////////////
void myTimer( int value ) {
  normalKeys(); // run the keys function, to see which keys are being pressed

  checkRaise(); // check if the board is on the raise

  // STREAK
  if(streakNum==STREAKS) streakNum=0; // earse the oldest elements in the array
  streak[streakNum][0]=lookAtX; // add the current x, z, and angle orientation to the streak array
  streak[streakNum][1]=lookAtZ;
  streak[streakNum][2]=objTheta;
  streakNum++; // increment streak

  // HOVER ANIMATION
  if(hover && hoverPos<15) // move the hover disks up
    hoverPos++; 
  else if(hoverPos>0){ // move the hover disks down
    hoverPos--;
    hover=false;
  }
  else hover=true;

  if(animateSprite){ // if the user has said the sprite should move
    Point temp=bez.trackCurve(spritePos); // track the curve with sprite position
    spriteX=temp.getX(); // sprite x,y,z position
    spriteY=temp.getY();
    spriteZ=temp.getZ();
    spritePos++; // increase the sprite position on the curve
    bomber.subFuse(); // shorten the fuse
  }
  if(bez.resSize()<spritePos){ // if the sprite reaches the end of the curve
    bomber.setFuse(1); // reset the fuse
    spritePos=0; // reset the sprite position on the curve
    Point temp=bez.trackCurve(spritePos); // reset the position on the curve 
    spriteX=temp.getX();
    spriteY=temp.getY();
    spriteZ=temp.getZ();
    if(soundOn) // if the sound if on
      alSourcePlay(wav.sources[1]); // play the bomb sound at the reset of the sprite
  }
  if(!soundOn) // stop the sound if it reaches the user turns it off
    alSourceStop(wav.sources[1]);

    // redraw our display
    glutPostRedisplay();
    // register a new timer callback
    glutTimerFunc( 1000.0f / 60.0f, myTimer, 0 );
}

// myMenu() /////////////////////////////////////////////////////////////////////
//
//  Handles our Menu events
//
////////////////////////////////////////////////////////////////////////////////
void myMenu( int value ) {
  switch(value){
  case 0: exit(0); break;
  // toggle display control points on/ off -- changes menu option
  case 1: displayPoints=!displayPoints;
    if(displayPoints)
     glutChangeToMenuEntry(1,"Hide Control Points",1);
    else
     glutChangeToMenuEntry(1,"Display Control Points",1);
  break;
  // toggle display control cage on/ off -- changes menu option
  case 2: displayCage=!displayCage; 
    if(displayCage)
     glutChangeToMenuEntry(2,"Hide Control Cage",2);
    else
     glutChangeToMenuEntry(2,"Display Control Cage",2);
  break;
  // toggle display bezier curve on/ off -- changes menu option
  case 3: displayCurve=!displayCurve;
    if(displayCurve)
     glutChangeToMenuEntry(3,"Hide Bezier Curve",3);
    else
     glutChangeToMenuEntry(3,"Display Bezier Curve",3);
  break;
  // toggle sound on/ off -- changes menu option
  case 4: soundOn=!soundOn; 
    if(soundOn)
     glutChangeToMenuEntry(4,"Turn OFF Sound",4);
    else
     glutChangeToMenuEntry(4,"Turn ON Sound",4);
  break;
  // toggle sprite animation on/ off -- changes menu option
  case 5: animateSprite=!animateSprite; 
    if(animateSprite)
     glutChangeToMenuEntry(5,"Turn OFF Sprite Movement",5);
    else
     glutChangeToMenuEntry(5,"Turn ON Sprite Movement",5);
  break;
  }
}

// createMenus() ///////////////////////////////////////////////////////////////
//
//  Handles creating a menu, adding menu entries, and attaching the menu to
//  a mouse button
//
////////////////////////////////////////////////////////////////////////////////
void createMenus() {
  glutCreateMenu(myMenu);
  glutAddMenuEntry("Hide Control Points",1);
  glutAddMenuEntry("Hide Control Cage",2);
  glutAddMenuEntry("Hide Bezier Curve",3);
  glutAddMenuEntry("Turn OFF Sound",4);
  glutAddMenuEntry("Turn OFF Sprite Movement",5);
  glutAddMenuEntry("Quit",0);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
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
    glutKeyboardUpFunc( normalKeysUp       );
    glutSpecialFunc(    specialKeys   );

    // mouse callbacks
    glutMouseFunc(      mouseCallback      );
    glutMotionFunc(     mouseMotion        );

    // display callbacks
    glutDisplayFunc(    renderScene        );
    glutReshapeFunc(    resizeWindow       );

    // timer callback
    glutTimerFunc( 1000.0f / 60.0f, myTimer, 0 );
}

// loadControlPoints() /////////////////////////////////////////////////////////
//
//  Load our control points from file and store them in a global variable.
//
////////////////////////////////////////////////////////////////////////////////
bool loadControlPoints( char* filename ) {
  ifstream file(filename);
  if(!file.is_open()){
    cerr<<"ERROR. Could not find/ read file. Check spelling."<<endl;
    return false;
  }
 
  int numPoints;
  file>>numPoints; // number of points

  char c;
  float tempX,tempY,tempZ;
  vector<Point> tempP;
  vector<Bezier> tempBez;
  for(int i=0; i<numPoints; i++){
    file>>tempX>>c>>tempY>>c>>tempZ;
    tempP.push_back(Point(tempX,tempY,tempZ)); // pushes each value into a point into a vector
  }
  for(int i=0; i<numPoints-3; i+=3)
    bez.bezierConnect(Bezier(tempP[i],tempP[i+1],tempP[i+2],tempP[i+3])); // pushes each set of 4 points into a bezier vector
  
  return true; // was able to read the file
}

// main() //////////////////////////////////////////////////////////////////////
//
//  Program entry point. Takes a single command line argument for our 
//    control points file.
//
////////////////////////////////////////////////////////////////////////////////
int main( int argc, char **argv ) {

    if(argc!=2){
      cerr<<"Usage: "<<argv[0]<<" <CSV_NAME>"<<endl;
      return 0;
    }
    if(!loadControlPoints(argv[1])) return 0; // wasn't able to read the file
    
    wav.initializeOpenAL(argc,argv); // initialize the sound -- openAL

    // create a double-buffered GLUT window at (50, 50) with predefined window size
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowPosition( 50, 50 );
    glutInitWindowSize( windowWidth, windowHeight );
    glutCreateWindow( "Assn 4 - How to Train Your Pegasus" );

    fprintf(stdout, "[INFO]: /--------------------------------------------------------\\\n");
    fprintf(stdout, "[INFO]: | OpenGL Information                                     |\n");
    fprintf(stdout, "[INFO]: |--------------------------------------------------------|\n");
    fprintf(stdout, "[INFO]: |   OpenGL Version:  %35s |\n", glGetString(GL_VERSION));
    fprintf(stdout, "[INFO]: |   OpenGL Renderer: %35s |\n", glGetString(GL_RENDERER));
    fprintf(stdout, "[INFO]: |   OpenGL Vendor:   %35s |\n", glGetString(GL_VENDOR));
    fprintf(stdout, "[INFO]: |   GLUI Version:    %35.2f |\n", GLUI_VERSION);
    fprintf(stdout, "[INFO]: \\--------------------------------------------------------/\n");

    // do some basic OpenGL setup
    initScene();

    // create our menu options and attach to mouse button
    createMenus();

    // register callback functions...
    registerCallbacks();

    //atexit(wav.cleanupOpenAL);
      

    // and enter the GLUT loop, never to exit.
    glutMainLoop();

    return(0);
}
