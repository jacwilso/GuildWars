#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#ifdef __APPLE__                        // if compiling on Mac OS
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else                                   // else compiling on Linux OS
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

// Other libraries
#include <cmath>
class Environment{
private:
	const static float DEG_RAD = 3.14159/180;
public:
	Environment();
	void generateEnvironmentDL();
	void drawEnvironment();
	void drawGrid();
	void drawGround();
	void drawRock();
	void drawBox();
	void drawTree();
	void drawTrees();

	static GLUquadric* qobj;
    GLuint environmentDL;

};




#endif	
