#include "Bezier.h"

Bezier::Bezier(){};

// push the points onto the control point vector
Bezier::Bezier(Point p0, Point p1, Point p2, Point p3){
  p.push_back(p0);
  p.push_back(p1);
  p.push_back(p2);
  p.push_back(p3);
}

// evaluates points along the curve with the specified bezier curve, with the percentage along the curve
Point Bezier::evaluateCurve(int bez,float t) {
  return pow(1-t,3)*p[bez]+3*pow(1-t,2)*t*p[bez+1]+3*(1-t)*pow(t,2)*p[bez+2]+pow(t,3)*p[bez+3];
}

// render the curve -- same code as lab03
void Bezier::renderCurve() {
  glDisable(GL_LIGHTING);
  glColor3f(0,0,1.0f);
  glLineWidth(3.0f);
  glBegin(GL_LINE_STRIP);
  for(unsigned int j=0; j<p.size()/4; j++){ // goes through each bezier curve if multiple joined
    for(int i=0; i<=RESOLUTION; i++){ 
      Point temp=evaluateCurve(4*j,(float)(i)/RESOLUTION);
      glVertex3f(temp.getX(),temp.getY(),temp.getZ());
    }
  }
  glEnd();
  glEnable(GL_LIGHTING);
}

// render the control points -- same code as lab03
void Bezier::renderPoints(){
  glColor3f(0,1,0);
  for(unsigned int i=0; i<p.size(); i++){
    glPushMatrix();
      glTranslatef(p[i].getX(),p[i].getY(),p[i].getZ());
      glutSolidSphere(.3,32,32);
    glPopMatrix();
  }
}

// render the control cage -- same code as lab03
void Bezier::renderCage(){
  glColor3f(1.0f,1.0f,0);
  glLineWidth(3.0f);
  glDisable(GL_LIGHTING);
  glBegin(GL_LINE_STRIP);
  for(unsigned int i=0; i<p.size(); i++)
      glVertex3f(p[i].getX(),p[i].getY(),p[i].getZ());
    glEnd();
    glEnable(GL_LIGHTING);
}

// connect another bezier curve onto the current -- add the control points to the vector
void Bezier::bezierConnect(Bezier bez){
  for(unsigned int i=0; i<bez.p.size(); i++)
    this->p.push_back(bez.p[i]);
}

// track the point on the curve the pos is currently at
Point Bezier::trackCurve(int pos){
  return evaluateCurve(4*(pos/RESOLUTION),(float)(pos%RESOLUTION)/RESOLUTION);
}
