#ifndef FAIRY_H
#define FAIRY_H

#include "Hero.h"

class Fairy : public Hero{
  private:
  public:
    void drawHero(){
	//glPushMatrix();
	glColor3f(0.28, 0.85, 0.12);
        glTranslatef(heroPosX,heroPosY,heroPosZ);
        glRotatef(heroTheta,0,1,0);
	glutSolidSphere(0.25, 16, 16);
	//glPopMatrix();
  }
};

#endif
