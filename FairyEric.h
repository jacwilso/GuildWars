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
#include "Hero.h"

class FairyEric : public Hero {
  private:
	//Shapes
	void drawCircle();
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
  public:
// Drawing Functions
	/*
	 * Draws the entire Character
	 */
	void drawHero();
	void animate();
};

#endif
