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


void Camera::ThirdPersonPOV(EricCartman& eric){
	gluLookAt( -15*cos(eric.getEricPositionTheta()*(M_PI/180)) + eric.getEricPositionX(), 
			eric.getEricPositionY() + 3.3,
			15*sin(eric.getEricPositionTheta()*(M_PI/180)) + eric.getEricPositionZ(),
			eric.getEricPositionX(),
			eric.getEricPositionY(),
			eric.getEricPositionZ(),
			0,1,0);
}
void Camera::FirstPersonPOV(EricCartman& eric){
	gluLookAt( eric.getEricPositionX() + 4.2*cos(eric.getEricPositionTheta()*(M_PI/180)), 
			3.3 + eric.getEricPositionY() + 0.2*sin(eric.getEricHeadBobAngle()*M_PI/180), 
			eric.getEricPositionZ() - 4.2*sin(eric.getEricPositionTheta()*(M_PI/180)),
			20*cos(eric.getEricPositionTheta()*(M_PI/180)) + eric.getEricPositionX(), 
			3.3 + eric.getEricPositionY(),
			-20*sin(eric.getEricPositionTheta()*(M_PI/180)) +eric.getEricPositionZ(),
			0,1,0);
}
void Camera::ReversePOV(EricCartman& eric){
gluLookAt( 15*cos(eric.getEricPositionTheta()*(M_PI/180)) + eric.getEricPositionX(),
			eric.getEricPositionY() ,
			-15*sin(eric.getEricPositionTheta()*(M_PI/180)) + eric.getEricPositionZ(),
			eric.getEricPositionX(), 
			eric.getEricPositionY(),
			eric.getEricPositionZ(),
			0,1,0);
}
void Camera::SkyCam (EricCartman& eric){
gluLookAt( -cos(eric.getEricPositionTheta()*(M_PI/180)) + eric.getEricPositionX(),
			eric.getEricPositionY() + 30, 
			sin(eric.getEricPositionTheta()*(M_PI/180)) + eric.getEricPositionZ(),
			eric.getEricPositionX(), 
			eric.getEricPositionY(),
			eric.getEricPositionZ(),
			0,1,0);
}
void Camera::MovableFirstPersonPOV(EricCartman& eric){
			gluLookAt( eric.getEricPositionX() + 4.2*cos(eric.getEricPositionTheta()*(M_PI/180)),
			3.3 + eric.getEricPositionY() + 0.2*sin(eric.getEricHeadBobAngle()*M_PI/180),  
			eric.getEricPositionZ() - 4.2*sin(eric.getEricPositionTheta()*(M_PI/180)),
			pipDirX + 20*cos(eric.getEricPositionTheta()*(M_PI/180)) + eric.getEricPositionX(), 
			pipDirY + 3.3 + eric.getEricPositionY(), 
			pipDirZ - 20*sin(eric.getEricPositionTheta()*(M_PI/180)) +eric.getEricPositionZ(),
			0,1,0);
}

void Camera::ArcBall(EricCartman& eric){
	gluLookAt(
		dirZ*cameraRad + eric.getEricPositionX(),
		dirY*cameraRad + eric.getEricPositionY(), 
		dirX*cameraRad+ eric.getEricPositionZ(),
		eric.getEricPositionX(),
		eric.getEricPositionY(),
		eric.getEricPositionZ(),
		0,1,0);

}