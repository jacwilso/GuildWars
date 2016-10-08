#ifndef CAMERA_H
#define CAMERA_H

class Camera {
private:
	float cameraX, cameraY, cameraZ;            // camera position in cartesian coordinates
	float vectorX, vectorY, vectorZ;
	float dirX, dirY, dirZ;                     // camera DIRECTION in cartesian coordinates
	float cameraTheta, cameraPhi, cameraRadius;               // camera DIRECTION in spherical coordinates

public:
	

	Camera();
	Camera(float, float, float, float, float, float, float,float,float,float,float,float);
	
	float getCameraX() {
		return cameraX;
	}

	float getCameraY() {
		return cameraY;
	}

	float getCameraZ() {
		return cameraZ;
	}

	float getCameraTheta() {
		return cameraTheta;
	}

	float getCameraPhi() {
		return cameraPhi;
	}

	float getDirX() {
		return dirX;
	}

	float getDirY() {
		return dirY;
	}

	float getDirZ() {
		return dirZ;
	}

	float getVectorX() {
		return vectorX;
	}

	float getVectorY() {
		return vectorY;
	}

	float getVectorZ() {
		return vectorZ;
	}

	float getCameraRadius() {
		return cameraRadius;
	}

	void setCameraX(float camX) {
		cameraX = camX;
	}

	void setCameraY(float camY) {
		cameraY = camY;
	}

	void setCameraZ(float camZ) {
		cameraZ = camZ;
	}

	void setCameraThe(float camThe) {
		cameraTheta = camThe;
	}

	void setCameraPhi(float camPhi) {
		cameraPhi = camPhi;
	}

	void setDirX(float DX) {
		dirX = DX;
	}

	void setDirY(float DY) {
		dirY = DY;
	}

	void setDirZ(float DZ) {
		dirZ = DZ;
	}

	void setVectorX(float vectX) {
		vectorX = vectX;
	}

	void setVectorY(float vectY) {
		vectorY = vectY;
	}

	void setVectorZ(float vectZ) {
		vectorZ = vectZ;
	}

	void setCameraRadius(float radius) {
		cameraRadius = radius;
	}
};

#endif // !CAMERA_H