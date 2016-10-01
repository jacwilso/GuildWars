#ifndef DONKEY_H
#define DONKEY_H

#include "../utilities/Hero.h"

class Donkey : public Hero{
  private:
      int index;
      float tailRotateAngle;

	void drawBody();
	void drawHead();
	void drawLines();
	void drawNeck();
	void drawSphere();
	void drawTail();
	void drawWheels();
  public:
	//the index for fairy's position

	Donkey();
	Donkey(float, float, int, int, float);

	int getIndex()
	{return index;}
	float getTailRotateAngle()
	{return tailRotateAngle;}
	void setIndex(int i)
	{index = i;}
	void setTailRotateAngle(float angle)
	{charRotateAngle = angle;}

        void drawHero();
        void animate();
};

#endif //
