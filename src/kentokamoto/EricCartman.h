#pragma once
#ifndef ERIC_CARTMAN_H
#define ERIC_CARTMAN_H

#ifdef __APPLE__                        // if compiling on Mac OS
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else                                   // else compiling on Linux OS
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "FairyEric.h"

class EricCartman : public Hero{
private:
	// Private Global Variables
	float ericPositionX = 0;
	float ericPositionY = 4;
	float ericPositionZ = 0;
	float ericPositionTheta = 0;

	// Angle is specified for foot and hand swing angle. Change variable name later.
	float swingAngle = 0;
	float ericHeadBobAngle = 0;

	int BezierPointVectorIndex = 0;
	bool showControlCage = true;
	bool showBezierCurve = true;

public:
	/*
	 * Constructor
	 */
	EricCartman();

	//Shapes
	void drawCircle();

	// Getters
	float getEricPositionX();
	float getEricPositionY();
	float getEricPositionZ();
	float getEricPositionTheta();
	float getSwingAngle();
	float getEricHeadBobAngle();

	// Setters
	void setEricPositionX(float item);
	void setEricPositionY(float item);
	void setEricPositionZ(float item);
	void setEricPositionTheta(float item);
	void setSwingAngle(float item);
	void setEricHeadBobAngle(float item);

	// Drawing Functions
	/*
	 * Draws the entire Character
	 * We can call the drawHero() insead of this method
	 */
	void drawHero();


	/*
	 * Draws a foot
	 * This includes the legs and foot
	 */
	void drawFeet();
	/*
	 * Draws the body:
	 * Includes:
	 * Body, Arm, Legs
	 */
	void drawBody();
	/*
	 * Draws the Arms and Hands
	 */
	void drawHands();
	/*
	 * Draws entire Head
	 */
	void drawHead();

	// Movement functions
	/*
	 *	Moves eric forward depending on which direction he's facing
	 */
	void moveEricForward();
	/*
	 *	Moves eric backward depending on which direction he's facing
	 */
	void moveEricBackward();
	/*
	 *	Turns Eric left depending on which direction he's facing
	 */
	void turnEricLeft();
	/*
	 *	Turns Eric Right depending on which direction he's facing
	 */
	void turnEricRight();

	/*
	 * Responsible for Bobbing Eric's head up and down.
	 */
	void bobHead();

	/*
	 * Move the Bezier Index up one
	 */
	void MoveFairyEric();

	/*
	 * Toggle Options
	 */
	void toggleControlCage();
	void toggleBezierCurve();


};

#endif
