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

void BezierSurface::renderGrid(){
	renderPoints();
	glDisable(GL_LIGHTING);
	glColor3f(0,0,1.0f);
	glLineWidth(3.0f);
	for(int u=0; u<RESOLUTION; u+=STEP){
		glBegin(GL_LINE_STRIP);
		for(int v=0; v<RESOLUTION; v+=STEP){
			Point temp=evaluateSurface((float)(u)/RESOLUTION,(float)(v)/RESOLUTION); 
			glVertex3f(temp.getX(),temp.getY(),temp.getZ());
		} 
		glEnd();
	}
	for(int v=0; v<RESOLUTION; v+=STEP){
		glBegin(GL_LINE_STRIP);
		for(int u=0; u<RESOLUTION; u+=STEP){
			Point temp=evaluateSurface((float)(u)/RESOLUTION,(float)(v)/RESOLUTION); 
			glVertex3f(temp.getX(),temp.getY(),temp.getZ());
		} 
		glEnd();
	}
	glEnable(GL_LIGHTING);
}

void BezierSurface::renderSurface(){
	Point temp;
	glColor3f(1.0f,0,0);
	glLineWidth(3.0f);
	for(int v=0; v<RESOLUTION-1; v+=STEP){
		glBegin(GL_QUAD_STRIP);
		temp=evaluateSurface(0,(float)(v)/RESOLUTION); 
		glVertex3f(temp.getX(),temp.getY(),temp.getZ());
		temp=evaluateSurface(0,(float)(v+STEP)/RESOLUTION); 
		glVertex3f(temp.getX(),temp.getY(),temp.getZ());
		for(int u=0; u<RESOLUTION-1; u+=STEP){
			temp=evaluateSurface((float)(u+STEP)/RESOLUTION,(float)(v+STEP)/RESOLUTION); 
			glVertex3f(temp.getX(),temp.getY(),temp.getZ());
			temp=evaluateSurface((float)(u+STEP)/RESOLUTION,(float)(v)/RESOLUTION); 
			glVertex3f(temp.getX(),temp.getY(),temp.getZ());
		}
		glEnd();
	}
}

Point BezierSurface::normal(float u,float v){
	Point du=
		pow(1-v,3)*bez[0].derivative(0,u)+
		3*pow(1-v,2)*v*bez[1].derivative(0,u)+
		3*pow(v,2)*(1-v)*bez[2].derivative(0,u)+
		pow(v,3)*bez[3].derivative(0,u);
	Point dv=
		-3*pow(1-v,2)*bez[0].evaluateCurve(0,u)+
		-6*(1-v)*v*bez[1].evaluateCurve(0,u)+
		3*pow(1-v,2)*bez[1].evaluateCurve(0,u)+
		6*v*(1-v)*bez[2].evaluateCurve(0,u)
		-3*pow(v,2)*bez[2].evaluateCurve(0,u)+
		3*pow(v,2)*bez[3].evaluateCurve(0,u);
        //cout<<"DU "<<du.getX()<<" "<<du.getY()<<" "<<du.getZ()<<endl;
        //cout<<"DV "<<dv.getX()<<" "<<dv.getY()<<" "<<dv.getZ()<<endl;
	float Nx,Ny,Nz,mag;
	Nx=du.getY()*dv.getZ()-du.getZ()*dv.getY();
	Ny=du.getZ()*dv.getX()-du.getX()*dv.getZ();
	Nz=du.getX()*dv.getY()-du.getY()*dv.getX();
	mag=pow(pow(Nx,2)+pow(Ny,2)+pow(Nz,2),.5);
	Nx/=mag; Ny/=mag; Nz/=mag;
	return Point(Nx,Ny,Nz); 
}

float BezierSurface::rotationAngle(float u,float v){
        Point N=normal(u,v);
        return acos(N.getY())*float(180)/3.14159;
}
Point BezierSurface::rotationAxis(float u,float v){
	Point N=normal(u,v);
	float Rx,Rz,mag;
	Rx= N.getZ();
	Rz= -N.getX();
        //cout<<"R "<<Rx<<" "<<Rz<<endl;
        mag=pow(pow(Rx,2)+pow(Rz,2),.5);
        //cout<<"MAG "<<mag<<endl;
        Rx/=mag; Rz/=mag;
        //cout<<"R "<<Rx<<" "<<Rz<<endl;
	return Point(Rx,0,Rz);
}
