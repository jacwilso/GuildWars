#pragma once
#ifndef FAIRY_ERIC_H
#define FAIRY_ERIC_H

#ifdef __APPLE__                        // if compiling on Mac OS
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else                                   // else compiling on Linux OS
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <cmath>
#include "../../NC_files/Hero.h"

class FairyEric : public Hero {
private:
	// Private Global Variables
	float fairyEricPositionX = 0;
	float fairyEricPositionY = 4;
	float fairyEricPositionZ = 0;
	float fairyEricPositionTheta = 0;


public:

	/*
	 * Constructor
	 */
	FairyEric();

	//Shapes
	void drawCircle();

	// Getters
	float getFairyEricPositionX();
	float getFairyEricPositionY();
	float getFairyEricPositionZ();
	float getFairyEricPositionTheta();

	// Setters
	void setFairyEricPositionX(float item);
	void setFairyEricPositionY(float item);
	void setFairyEricPositionZ(float item);
	void setFairyEricPositionTheta(float item);

// Drawing Functions
	/*
	 * Draws the entire Character
	 */
	void drawFairy();
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
	 * Draws the fake wings
	 */
	void drawWing();
	/*
	 * Draws the Arms and Hands
	 */
	void drawHands();
	/*
	 * Draws entire Head
	 */
	void drawHead();


};

#endif
