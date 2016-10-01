#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#ifdef __APPLE__			// if compiling on Mac OS
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else					// else compiling on Linux OS
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <time.h>
#include <stdlib.h>
#include <math.h>

class Environment{
  private:
    const static float DEG_RAD=3.14159/180; // degree to radian
    const static int BOUNDARY=50; // boundary of the field
    
    float getRand() // random number generator
    {return rand()/(float)RAND_MAX;}

    void drawGrid(); // draws the grid
    void drawRaise(); // draws a change in elevation
    void drawBox(); // draw a hollow box
    void drawRock(); // draws weird rock shape
  public:
    Environment(); // constructor

    static GLUquadric* qobj;
    GLuint environmentDL;
    void generateEnvironmentDL(); // static display list of all functions 
};

#endif
