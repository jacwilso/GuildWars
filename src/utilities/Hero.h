#ifndef HERO_H
#define HERO_H

#ifdef __APPLE__			// if compiling on Mac OS
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else					// else compiling on Linux OS
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include "Bezier.h"

class Hero{
  private:
    float heroPosX;
    float heroPosY;
    float heroPosZ;
		float heroTheta;
		float heroPhi;
    Bezier heroBezier;
    float fairyPosX;
		float fairyPosY;
		float fairyPosZ;
		float fairyTheta;
		float fairyPhi;
		Bezier fairyBezier;


  public:
		/*
		 * Constructor
		 */
		Hero();
		//Constructor for Hero(float posX,float poxY,float posZ,float theta, float phi, Beizer beizer)
		Hero(float,float,float,float,float,heroBezier);

		//Getters
		//For Heros
		float getHeroPositionX();
		float getHeroPositionY();
		float getHeroPositionZ();
		float getHeroTheta();
		float getHeroPhi();
		float getHeroBezier();
		//For Fairy
		float getFairyPositionX();
		float getFairyPositionY();
		float getFairyPositionZ();
		float getFairyTheta();
		float getFairyPhi();
		float getFairyBezier();

		//Setters
		//For Heros
		void setHeroPositionX(float posX);
		void setHeroPositionY(float posY);
		void setHeroPositionZ(float posZ);
    void setHeroTheta(float theta);
		void setHeroPhi(float phi);
    void setHeroBezier(Bezier bezier);
		//For FairyEric
		void setFairyPositionX(float posX);
		void setFairyPositionY(float posY);
		void setFairyPositionZ(float posZ);
		void setFairyTheta(float theta);
		void setFairyPhi(float phi);
		void setFairyBezier(Bezier bezier);

    //Drawing Functions
    void drawHero();
    void drawFairy();
