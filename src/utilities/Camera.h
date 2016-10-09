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


// Constant Variables
    const static float X_OFFSET = 0, Y_OFFSET = 3.3, Z_OFFSET = 0, SKYCAM_HEIGHT = 30;

class Camera
{
private:
	int viewMode;

	float dirX,dirY,dirZ;
    float cameraTheta, cameraPhi;
    float cameraX,cameraY,cameraZ,cameraRad;
    float subjectPosX, subjectPosY, subjectPosZ, subjectPosTheta;


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
    
    void setSubjectPosition(float x, float y, float z, float theta);

    /*
     * Encompasses all camera angles and displays based on what view mode is selected.
     */
    void setCamera();

    /*
     * Mode 0: FreeCam
     */
    void FreeCam();

    /*
     * Mode 1: 3rd Person
     */
    void ThirdPersonPOV(); 
    
    /*
     * Mode 2: 1st Person
     */
    void FirstPersonPOV();
    
    /*
     * Mode 3: Reverse 3rd Person
     */
    void ReversePOV();
    
    /*
     * Mode 4: SkyCam
     */
    void SkyCam ();
    
    /*
     * Mode 5: ArcBall
     */
    void ArcBall();



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

    float getSubjectPosX()
    { return subjectPosX; }

    float getSubjectPosY()
    { return subjectPosY; }

    float getSubjectPosZ()
    { return subjectPosZ; }

    float getsubjectPosTheta()
    { return subjectPosTheta;}    

    // Setters
    void setViewMode(int);
    void setCameraX(float);
    void setCameraY(float);
    void setCameraZ(float);
    void setCameraTheta(float);
    void setCameraPhi(float);
    void setDirX(float item);
    void setDirY(float item);
    void setDirZ(float item);
    void setCameraRad(float item);
    void setSubjectPosX(float item);
    void setSubjectPosY(float item);
    void setSubjectPosZ(float item);
    void setsubjectPosTheta(float item);

};
