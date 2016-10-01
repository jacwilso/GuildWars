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

Point BezierSurface::evaluateSurface(float u,float v){
  return (
    pow(1-v,3)*bez[0].evaluateCurve(0,u)+
    3*pow(1-v,2)*v*bez[1].evaluateCurve(0,u)+
    3*pow(v,2)*(1-v)*bez[2].evaluateCurve(0,u)+
    pow(v,3)*bez[3].evaluateCurve(0,u));

}

void BezierSurface::renderSurface(){
  renderPoints();
  glDisable(GL_LIGHTING);
  glColor3f(0,0,1.0f);
  glLineWidth(3.0f);
  for(int u=0; u<RESOLUTION; u++){
  glBegin(GL_LINE_STRIP);
    for(int v=0; v<RESOLUTION; v++){
      Point temp=evaluateSurface((float)(u)/RESOLUTION,(float)(v)/RESOLUTION); 
      glVertex3f(temp.getX(),temp.getY(),temp.getZ());
    } 
  glEnd();
  }
  for(int v=0; v<RESOLUTION; v++){
  glBegin(GL_LINE_STRIP);
    for(int u=0; u<RESOLUTION; u++){
      Point temp=evaluateSurface((float)(u)/RESOLUTION,(float)(v)/RESOLUTION); 
      glVertex3f(temp.getX(),temp.getY(),temp.getZ());
    } 
  glEnd();
  }
  glEnable(GL_LIGHTING);
}
