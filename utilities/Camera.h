#ifdef __APPLE__			// if compiling on Mac OS
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else					// else compiling on Linux OS
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "EricCartman.h"
#include <math.h>
class Camera
{
private:
	Camera() {
			pipMode = 0;
			pipDirX = 0;
			pipDirY = 0;
			pipDirZ = 0;

			dirX = 0;
			dirY = 0;
			dirZ = 0;

			cameraRad = 30;
	};
	int pipMode;
	float pipDirX;
	float pipDirY;
	float pipDirZ;

	float dirX;
	float dirY;
	float dirZ;

	float cameraRad;


public:
	// Initialize Singleton
	static Camera& getInstance(){
            static Camera instance; // Guaranteed to be destroyed.
                                  	// Instantiated on first use.
            return instance;
    };

    void ThirdPersonPOV(EricCartman& eric);
    void FirstPersonPOV(EricCartman& eric);
    void ReversePOV(EricCartman& eric);
    void SkyCam (EricCartman& eric);
    void MovableFirstPersonPOV(EricCartman& eric);
    void ArcBall(EricCartman& eric);

    // Getters
    int getPipMode();
    float getPipDirX();
    float getPipDirY();
    float getPipDirZ();
    float getDirX();
    float getDirY();
    float getDirZ();
    float getCameraRad();

    // Setters
    void setPipMode(int);
    void setPipDirX(float);
    void setPipDirY(float);
    void setPipDirZ(float);
    void setDirX(float item);
    void setDirY(float item);
    void setDirZ(float item);
    void setCameraRad(float item);

};