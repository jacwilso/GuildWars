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
#include "Point.h"
class Camera
{
private:
	int viewMode;

	float dirX,dirY,dirZ;
    float cameraTheta, cameraPhi;
    float cameraX,cameraY,cameraZ,cameraRad;

// Constant Variables
    const static float X_OFFSET = 0, Y_OFFSET = 3.3, Z_OFFSET = 0, SKYCAM_HEIGHT = 30;

public:
    Camera();

    /*
     * Camera Movement: Forward
     */
    void moveForward();

    /*
     * Camera Movement: Backward
     */
    void moveBackward();

    /*
     * Change camera angle
     */
    void recomputeOrientation();
    /*
     * Mode 0: FreeCam
     */
    void FreeCam();

    /*
     * Mode 1: 3rd Person
     */
    void ThirdPersonPOV(float x, float y, float z, float thetaInRad); 
    
    /*
     * Mode 2: 1st Person
     */
    void FirstPersonPOV(float x, float y, float z, float thetaInRad);
    
    /*
     * Mode 3: Reverse 3rd Person
     */
    void ReversePOV(float x, float y, float z, float thetaInRad);
    
    /*
     * Mode 4: SkyCam
     */
    void SkyCam (float x, float y, float z, float thetaInRad);
    
    /*
     * Mode 6: ArcBall
     */
    void ArcBall(float x, float y, float z);



    // Getters
    int getViewMode()
    {return viewMode;}
    float getCameraX()
    {return cameraX;}
    float getCameraY()
    {return cameraY;}
    float getCameraZ()
    {return cameraZ;}
    Point getCameraPos()
    {return Point(cameraX,cameraY,cameraZ);}
    float getCameraTheta()
    {return cameraTheta;}
    float getCameraPhi()
    {return cameraPhi;}
    float getCameraRad()
    {return cameraRad;}
    float getDirX()
    {return dirX;}
    float getDirY()
    {return dirY;}
    float getDirZ()
    {return dirZ;}
    Point getDir()
    {return Point(dirX,dirY,dirZ);}

    // Setters
    void setViewMode(int);
    void setCameraTheta(float);
    void setCameraPhi(float);
    void setDirX(float item);
    void setDirY(float item);
    void setDirZ(float item);
    void setCameraRad(float item);

};
