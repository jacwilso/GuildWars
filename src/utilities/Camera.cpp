#include "Camera.h"

// Getters
int Camera::getPipMode(){
	return pipMode;
}
float Camera::getPipDirX(){
	return pipDirX;
} 
float Camera::getPipDirY(){
	return pipDirY;
}
float Camera::getPipDirZ(){
	return pipDirZ;
}
float Camera::getDirX(){
	return dirX;
}
float Camera::getDirY(){
	return dirY;
}
float Camera::getDirZ(){
	return dirZ;
}
float Camera::getCameraRad(){
	return cameraRad;
}

// Setters
void Camera::setPipMode(int item){
	pipMode = item;
}
void Camera::setPipDirX(float item){
	pipDirX = item;
}
void Camera::setPipDirY(float item){
	pipDirY = item;
}
void Camera::setPipDirZ(float item){
	pipDirZ = item;
}
void Camera::setDirX(float item){
	dirX = item;
}	
void Camera::setDirY(float item){
	dirY = item;
}
void Camera::setDirZ(float item){
	dirZ = item;
}
void Camera::setCameraRad(float item){
	cameraRad = item;
}


void Camera::ThirdPersonPOV(float x, float y, float z, float thetaInRad){
	gluLookAt( -15*cos(thetaInRad*(M_PI/180)) + z, 
			y + Y_OFFSET,
			15*sin(thetaInRad*(M_PI/180)) + z,
			x,
			y,
			z,
			0,1,0);
}
void Camera::FirstPersonPOV(float x, float y, float z, float thetaInRad){
	gluLookAt( x + 4.2*cos(thetaInRad*(M_PI/180)), 
			Y_OFFSET + y, 
			z - 4.2*sin(thetaInRad*(M_PI/180)),
			20*cos(thetaInRad*(M_PI/180)) + x, 
			3.3 + y,
			-20*sin(thetaInRad*(M_PI/180)) +z,
			0,1,0);
}
void Camera::ReversePOV(float x, float y, float z, float thetaInRad){
gluLookAt( 15*cos(thetaInRad*(M_PI/180)) + x,
			y + Y_OFFSET,
			-15*sin(thetaInRad*(M_PI/180)) + z,
			x, 
			y,
			z,
			0,1,0);
}
void Camera::SkyCam (float x, float y, float z, float thetaInRad){
gluLookAt( -cos(thetaInRad*(M_PI/180)) + x,
			y + SKYCAM_HEIGHT, 
			sin(thetaInRad*(M_PI/180)) + z,
			x, 
			y,
			z,
			0,1,0);
}
void Camera::MovableFirstPersonPOV(float x, float y, float z, float thetaInRad){
			gluLookAt( x + 4.2*cos(thetaInRad*(M_PI/180)),
			Y_OFFSET + y,  
			z - 4.2*sin(thetaInRad*(M_PI/180)),
			pipDirX + 20*cos(thetaInRad*(M_PI/180)) + x, 
			pipDirY + 3.3 + y, 
			pipDirZ - 20*sin(thetaInRad*(M_PI/180)) +z,
			0,1,0);
}

void Camera::ArcBall(float x, float y, float z){
	gluLookAt(
		dirZ*cameraRad + x,
		dirY*cameraRad + y, 
		dirX*cameraRad + z,
		x,
		y,
		z,
		0,1,0);
}

void Camera::FreeCam(){
	gluLookAt(
		cameraX,
		cameraY,
		cameraZ,
		dirX + cameraX,
		dirY + cameraY, 
		dirZ + cameraZ,
		0,1,0);
}


