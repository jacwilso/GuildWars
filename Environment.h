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

#include "Point.h"
#include "Bezier.h"
#include "BezierSurface.h"
using namespace std;
// Constant Variables
const static float DEG_RAD = 3.14159/180;

class Environment{
		private:
				vector<BezierSurface> surf;
				Bezier track;
				/*
				 * Draw a flat grid
				 */ 
				void drawGrid();
				/*
				 * Draws a flat ground
				 */
				void drawGround();
				/*
				 * Draws a tree
				 */
				void drawTree();
				/*
				 * Draws a Hut
				 */
				void drawHut();
				/*
				 * Draws the Bezier surface
				 */
				void drawSurface();
				/*
				 * Draws the bezier curve	
				 */
				void drawCurve();
				/*
				 * Draws the Box
				 */
				void drawBox();
				/*
				 * Draw the boxes on the track
				 */
				void trackBox();
				/*
				 * Draw the crappy rainbow road
				 */
				void trackRoad();
		public:
				Environment();
				/*
				 * Places tree and hut in environement according to the file
				 */
				void placeObjectsInEnvironment(std::ifstream& inFile);
				/*
				 * Creates the environment
				 */
				void generateEnvironmentDL(std::ifstream& inFile);
				/*
				 * Adds the bezier surface to generate environment
				 */
				void addSurface(vector<BezierSurface> surf);
				/*
				 * Adds the bezier curves to environment
				 */
				void addCurve(Bezier curve);

				static GLUquadric* qobj;
				GLuint environmentDL;

};




#endif	
