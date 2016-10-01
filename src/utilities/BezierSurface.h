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
#include <vector>
#include <math.h>
#include "Point.h"
#include "Bezier.h"

class BezierSurface{
  private:
    const static int RESOLUTION=100; // resolution of the curve
    vector<Bezier> bez;

  public:
    BezierSurface();
    BezierSurface(Bezier b1,Bezier b2,Bezier b3,Bezier b4);
    BezierSurface(Point p0,Point p1,Point p2,Point p3,
                  Point p4,Point p5,Point p6,Point p7,
                  Point p8,Point p9,Point p10,Point p11,
                  Point p12,Point p13,Point p14,Point p15);

    void createSurface(Bezier b1,Bezier b2,Bezier b3,Bezier b4);
    void createSurface(Point p0,Point p1,Point p2,Point p3,
                  Point p4,Point p5,Point p6,Point p7,
                  Point p8,Point p9,Point p10,Point p11,
                  Point p12,Point p13,Point p14,Point p15);

    void renderPoints()
    {for(unsigned int i=0; i<bez.size(); i++) 
       bez[i].renderPoints();
    }
    void renderCage()
    {for(unsigned int i=0; i<bez.size(); i++) 
       bez[i].renderCage();
    }

    Bezier evaluateSurface(float t);
    void renderSurface();
};

#endif
