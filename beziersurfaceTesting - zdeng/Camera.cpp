#include "Camera.h"
using namespace std;

Camera::Camera() {

	// camera position in cartesian coordinates
	cameraX = 0;
	cameraY = 0;
	cameraZ = 0;

	// camera DIRECTION in spherical coordinates
	cameraTheta = 0; 
	cameraPhi = 0;
	cameraRadius = 0;
	// camera DIRECTION in cartesian coordinates
	dirX = 0;
	dirY = 0;
	dirZ = 0 ;                     

}

Camera::Camera(float CamX, float CamY, float CamZ, float DX, float DY, float DZ, 
	float vectX, float vectY, float vectZ, float CamThe, float CamPhi, float radius) {
	cameraX = CamX;
	cameraY = CamY;
	cameraZ = CamZ;
	dirX = DX;
	dirY = DY;
	dirZ = DZ;
	vectorX = vectX;
	vectorY = vectY;
	vectorZ = vectZ;
	cameraTheta = CamThe;
	cameraPhi = CamPhi;
	cameraRadius = radius;
}