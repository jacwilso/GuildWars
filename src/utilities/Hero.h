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

class Hero{
  protected:
    float heroPosX, heroPosY, heroPosZ,
      heroTheta, heroPhi;
    bool move;

  public:
	/*
	 * Constructor
	 */
	Hero();
	//Constructor for Hero(float posX,float poxY,float posZ,float theta, float phi)
	Hero(float,float,float,float,float);

	//Getters
	//For Heros
	float getHeroPositionX()
        {return heroPosX;}
	float getHeroPositionY()
        {return heroPosY;}
	float getHeroPositionZ()
        {return heroPosZ;}
	float getHeroTheta()
        {return heroTheta;}
	float getHeroPhi()
        {return heroPhi;}

	//Setters
	//For Heros
	void setHeroPos(float posX,float posY,float posZ,float theta,float phi)
        {heroPosX=posX; heroPosY=posY; heroPosZ=posZ;
         heroTheta=theta; heroPhi=phi;}

    //Drawing Functions
    virtual void drawHero(){};
    virtual void animate() {};
};

#endif
