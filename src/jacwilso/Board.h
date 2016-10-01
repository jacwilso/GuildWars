#ifndef OBJECT_H
#define OBJECT_H

#ifdef __APPLE__			// if compiling on Mac OS
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else					// else compiling on Linux OS
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

class Board{
  private:
    const static int STREAKS=25; // # of streaks to follow the board
    float hoverPos,objTheta,lookAtX,lookAtY,lookAtZ; // the hover animation position, board angle, the x,y, and z position of the board
    bool stomp,turn,bankLeft,bankRight; // whether the board is moving, turning, or turning while moving
    float streak[STREAKS][3]; // the array of positions for the streaks
    int streakNum; // the streak number
  
    void drawBoard(); // draws the deck
    void drawStompPad(); // draws the pad which compresses/ decompresses on the top of the board
    void drawBars(); // draws the bars on the bottom on either sides of the board
    void drawHolder(); // draws the holder in the center of the bottom of the board
    void drawHoverPad(); // draws the hover pads which emenate the hover animation
    void drawHover(); // draws the hover rings to be animated
    void drawStreak(); // draws the hover board but in a translucent color
    void drawHoverBoard(); // combines all the pieces into the board
  
  public:
    Board(); // constructor initializing starting position
    ~Board(){gluDeleteQuadric(qobj);} // destructor

    static GLUquadric* qobj; // static only need one per object
    GLuint objectDL; // for object environment
    void setVars(float lookAtX,float lookAtY,float lookAtZ,float objTheta,float hoverPos,bool stomp,bool turn,bool bankLeft,bool bankRight,float streak[STREAKS][3],int streakNum); // settting all the variables
    void generateObjectDL(); // generate in a list -- not needed to be in a list but I like the structure
};

#endif
