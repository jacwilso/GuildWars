#include "Hero.h"

using namespace std;

//constructor for empty object
Hero::Hero(){}

//constructor
Hero::Hero(float posX, float posY,float posZ, float angleTheta, float anglePhi,Bezier bezierCurve){
  heroPosX=posX;
  heroPosY=posY;
  heroPosZ=posZ;
  heroTheta=angleTheta;
  heroPhi=anglePhi;
  heroBezier=bezierCurve;
}
