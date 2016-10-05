#ifndef BEZIER_H
#define BEZIER_H

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
#include <iostream>
#include <math.h>
#include <map>
#include "Point.h"

using namespace std;

class Bezier{
  private:
    const static int RESOLUTION=100; // resolution of the curve
    vector<Point> p; // vector of control points
    map<float,float> arcParam;
    map<float,float> paramArc;
    void populateTable();
    void popTab(float arc);

  public:
    Bezier(); // constructor of no points
    
    Bezier(Point p0, Point p1, Point p2, Point p3); // constructor setting the points
    
    int resSize() // sets the resolution size of the curve since it can be >4
    {return RESOLUTION*p.size()/4;}
    float arcSize()
    {return paramArc[p.size()/4];}

    Point evaluateCurve(int bez,float t); // evaluate points along the bezier curve
    void renderCurve(); // render the curve by connecting the points
    void renderPoints(); // render the control points
    void renderCage(); // render the cage connecting the control points

    void bezierConnect(Bezier bez); // connect anothe bezier curve to the current curve
    Point parametricCurve(int pos); // track the point along the curve
    Point arcLengthCurve(float arc);

    void operator=(Bezier bez);
};

#endif

