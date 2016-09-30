#ifndef BOMBERMAN_H
#define BOMBERMAN_H

#ifdef __APPLE__			// if compiling on Mac OS
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else					// else compiling on Linux OS
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

class Bomberman{
  private:
    float fuseLength; // the fuse length of the bomb wire

    void drawEye(); // draw one eye
    void drawEyeBrow(); // draw one eyebrow
    void drawHead(); // draw the head w/ hood
   
    void drawTorso(); // draw the torso and belt
    void drawArm(); // draw one arm and hand
    void drawLeg(); // draw one leg and foot
    
    void drawBomb(); // draw the bomb

    void drawMan(); // combine all the features together
  public:
    Bomberman(); // constructor
    ~Bomberman(){gluDeleteQuadric(qobj);} // destructor -- leaking memory

    void setFuse(float length) // set the length of the fuse
    {fuseLength=length;}
    void subFuse() // subtract 1/100 from the fuse length
    {fuseLength-=.01;}

    GLuint bombermanDL; 
    
    static GLUquadric* qobj;
    void generateBombermanDL(); // gen list -- not necesary but like the structure
};

#endif
