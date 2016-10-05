#ifdef __APPLE__			// if compiling on Mac OS
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else					// else compiling on Linux OS
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <math.h>
class Camera
{
private:
	int pipMode;
	float pipDirX,pipDirY,pipDirZ;

	float dirX,dirY,dirZ;

    float cameraX,cameraY,cameraZ,cameraRad;

// Constant Variables
    const static float X_OFFSET = 0, Y_OFFSET = 3.3, Z_OFFSET = 0, SKYCAM_HEIGHT = 30;

public:
    Camera() {
        pipMode = 0;
        pipDirX = 0;
        pipDirY = 0;
        pipDirZ = 0;

        dirX = -10;
        dirY = -10;
        dirZ = -10;

	cameraX = 10;
	cameraY = 10;
	cameraZ = 10;
        cameraRad = 30;
    };

        void ThirdPersonPOV(float x, float y, float z, float thetaInRad);
        void FirstPersonPOV(float x, float y, float z, float thetaInRad);
        void ReversePOV(float x, float y, float z, float thetaInRad);
        void SkyCam (float x, float y, float z, float thetaInRad);
        void MovableFirstPersonPOV(float x, float y, float z, float thetaInRad);
        void ArcBall(float x, float y, float z);
        void FreeCam();


        void ZoomInArcball();
        void ZoomOutArcball();



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
