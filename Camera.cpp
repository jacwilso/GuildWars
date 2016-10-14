#include "Camera.h"

/*
 * Constructor
 */
Camera::Camera(){
	  viewMode = 5;


        cameraTheta = M_PI;
        cameraPhi = 5*M_PI/8;

        recomputeOrientation();
        cameraX = 0;
        cameraY = 10;
        cameraZ = 0;
        cameraRad = 30;

        subjectPosX = 0;
        subjectPosY = 0;
        subjectPosZ = 0;
        subjectPosTheta = 0;
	cameraPitch = 0;
	cameraRoll = 0;
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
void Camera::setSubjectPosX(float item){
	subjectPosX = item;
}
void Camera::setSubjectPosY(float item){
	subjectPosY = item;
}
void Camera::setSubjectPosZ(float item){
	subjectPosZ = item;
}

void Camera:: setSubjectPosTheta(float item){
	subjectPosTheta = item;
}

void Camera::setSubjectPosPhi(float item){
	subjectPosPhi = item;
}

void Camera::setCameraPitch(float item){
		cameraPitch = item;
}

void Camera::setCameraRoll(float item){
		cameraRoll = item;
}
void Camera::moveForward(){
	switch(viewMode){
		case 0: //Free Cam Mode
			cameraX += dirX;
			cameraY += dirY;
			cameraZ += dirZ;
			break;
		case 5: //ArcBall Mode 
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
		case 5: //ArcBall Mode 
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
 void Camera::setSubjectPosition(float x, float y, float z, float theta){
 	setSubjectPosX(x);
 	setSubjectPosY(y);
 	setSubjectPosZ(z);
 	setSubjectPosTheta(theta);
 }

void Camera::setCamera(){
	switch(viewMode){
		case 0:
			FreeCam();
		break;
		case 1:
			ThirdPersonPOV();
		break;
		case 2:
			FirstPersonPOV();
		break;
		case 3:
			ReversePOV();
		break;
		case 4:
			SkyCam();
		break;
		case 5:
			ArcBall();
		break;
		default:
			ArcBall();
			break;
	}
}
void Camera::ThirdPersonPOV(  ){
		gluLookAt( -15*cos(subjectPosTheta*(M_PI/180)) + subjectPosX, 
			subjectPosY + Y_OFFSET,
			15*sin(subjectPosTheta*(M_PI/180)) + subjectPosZ,
			subjectPosX,
			subjectPosY ,
			subjectPosZ,
			0,1,0);
}
void Camera::FirstPersonPOV( ){
	gluLookAt( subjectPosX + 4.2*cos(subjectPosTheta*(M_PI/180)), 
			Y_OFFSET + subjectPosY, 
			subjectPosZ - 4.2*sin(subjectPosTheta*(M_PI/180)),
			20*cos(subjectPosTheta*(M_PI/180)) + subjectPosX, 
			3.3+ subjectPosY,
			-20*sin(subjectPosTheta*(M_PI/180)) + subjectPosZ,
			0,1,0);
	
}
void Camera::ReversePOV( ){
gluLookAt( 15*cos(subjectPosTheta*(M_PI/180)) + subjectPosX,
			subjectPosY + Y_OFFSET,
			-15*sin(subjectPosTheta*(M_PI/180)) + subjectPosZ,
			subjectPosX, 
			subjectPosY,
			subjectPosZ,
			0,1,0);
}
void Camera::SkyCam (){
gluLookAt( -cos(subjectPosTheta*(M_PI/180)) + subjectPosX,
			subjectPosY + SKYCAM_HEIGHT, 
			sin(subjectPosTheta*(M_PI/180)) + subjectPosZ,
			subjectPosX, 
			subjectPosY,
			subjectPosZ,
			0,1,0);
}

void Camera::ArcBall( ){
	gluLookAt(
		dirZ*cameraRad + subjectPosX,
		dirY*cameraRad + subjectPosY, 
		dirX*cameraRad + subjectPosZ,
		subjectPosX,
		subjectPosY,
		subjectPosZ,
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
