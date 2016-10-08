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
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

#include "BezierSurface.h"
using namespace std;

class Environment{
private:
	const static float DEG_RAD = 3.14159/180;
        vector<BezierSurface> surf;
	void drawGrid();
	void drawGround();
	void drawTree();
	void drawTrees();
        void drawSurface();
public:
	Environment();
	void placeObjectsInEnvironment(std::ifstream& inFile);
	void generateEnvironmentDL(std::ifstream& inFile);
	void drawEnvironment();
        void addSurface(vector<BezierSurface> surf);

	static GLUquadric* qobj;
    GLuint environmentDL;

};




#endif	
