#include "BezierSurface.h"

BezierSurface::BezierSurface(){}

BezierSurface::BezierSurface(Bezier b1,Bezier b2,Bezier b3,Bezier b4){
  bez.push_back(b1);
  bez.push_back(b2);
  bez.push_back(b3);
  bez.push_back(b4);
}

BezierSurface::BezierSurface(
  Point p0,Point p1,Point p2,Point p3,
  Point p4,Point p5,Point p6,Point p7,
  Point p8,Point p9,Point p10,Point p11,
  Point p12,Point p13,Point p14,Point p15){
  bez.push_back(Bezier(p0,p1,p2,p3));
  bez.push_back(Bezier(p4,p5,p6,p7));
  bez.push_back(Bezier(p4,p5,p6,p7));
  bez.push_back(Bezier(p4,p5,p6,p7));
}

void BezierSurface::createSurface(Bezier b1,Bezier b2,Bezier b3,Bezier b4){
  bez.push_back(b1);
  bez.push_back(b2);
  bez.push_back(b3);
  bez.push_back(b4);
}
void BezierSurface::createSurface(
  Point p0,Point p1,Point p2,Point p3,
  Point p4,Point p5,Point p6,Point p7,
  Point p8,Point p9,Point p10,Point p11,
  Point p12,Point p13,Point p14,Point p15){
  bez.push_back(Bezier(p0,p1,p2,p3));
  bez.push_back(Bezier(p4,p5,p6,p7));
  bez.push_back(Bezier(p4,p5,p6,p7));
  bez.push_back(Bezier(p4,p5,p6,p7));
}

Bezier BezierSurface::evaluateSurface(float t){
  vector<Point> tmp;
  for(int i=0; i<4; i++)
    tmp.push_back(bez[i].evaluateCurve(0,t));
  return Bezier(tmp[0],tmp[1],tmp[2],tmp[3]);
}

void BezierSurface::renderSurface(){
  renderPoints();
  for(int i=0; i<4; i++)
  bez[i].renderCurve();
 for(int i=0; i<RESOLUTION; i++)
    evaluateSurface(i/RESOLUTION).renderCurve();
  
}
