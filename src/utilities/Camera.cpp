#include "Camera.h"

/*
 * Constructor
 */
Camera::Camera(){
	    viewMode = 0;


        cameraTheta = -M_PI / 3.0f;
        cameraPhi = M_PI / 2.8f;

        recomputeOrientation();
        cameraX = 10;
        cameraY = 10;
        cameraZ = 10;
        cameraRad = 30;
}


// Setters
void Camera::setViewMode(int item){
	viewMode = item;
}

void Camera::setCameraX(float item){
	cameraX = item;
}

void Camera::setCameraY(float item){
	cameraY = item;
}

void Camera::setCameraZ(float item){
	cameraZ = item;
}

void Camera::setCameraTheta(float item){
	cameraTheta = item;
}
void Camera::setCameraPhi(float item){
	cameraPhi = item;
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

void Camera::moveForward(){
	switch(viewMode){
		case 0: //Free Cam Mode
			cameraX += dirX;
			cameraY += dirY;
			cameraZ += dirZ;
			break;
		case 6: //ArcBall Mode 
			cameraRad += 2;
			break;
		default:
			break;
	}
}

void Camera::moveBackward(){
	switch(viewMode){
		case 0: //Free Cam Mode
			cameraX -= dirX;
			cameraY -= dirY;
			cameraZ -= dirZ;
			break;
		case 6: //ArcBall Mode 
			cameraRad -= 2;
			break;
		default:
			break;
	}
}
void Camera::recomputeOrientation(){
	dirX = sin(cameraTheta)*sin(cameraPhi) ; 
	dirY = -cos(cameraPhi);
	dirZ = -cos(cameraTheta)*sin(cameraPhi);

	float w = sqrt((dirX * dirX) + (dirY*dirY) + (dirZ*dirZ));
	dirX = dirX/w;
	dirY = dirY/w;
	dirZ = dirZ/w;
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


