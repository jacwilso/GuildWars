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

//Getters
//For Heros
float Hero::getHeroPositionX(){
  return heroPosX;
}
float Hero::getHeroPositionY(){
  return heroPosY;
}
float Hero::getHeroPositionZ(){
  return heroPosZ;
}
float Hero::getHeroTheta(){
  return heroTheta;
}
float Hero::getHeroPhi(){
  return heroPhi;
}
float Hero::getHeroBezier(){
  return heroBezier;
}
//For Fairy
float Hero::getFairyPositionX(){
  return fairyPosX;
}
float Hero::getFairyPositionY(){
  return fairyPosY;
}
float Hero::getFairyPositionZ(){
  return fairyPosZ;
}
float Hero::getFairyTheta(){
  return fairyTheta;
}
float Hero::getFairyPhi(){
  return fairyPhi;
}
float Hero::getFairyBezier(){
  return fairyBezier;
}

//Setters
//For Heros
void Hero::setHeroPositionX(float posX){
  heroPosX=posX;
}
void Hero::setHeroPositionY(float posY){
  heroPosY=posY;
}
void Hero::setHeroPositionZ(float posZ){
  heroPosZ=posZ;
}
void Hero::setHeroTheta(float theta){
  heroTheta=theta;
}
void Hero::setHeroPhi(float phi){
  heroPhi=phi;
}
void Hero::setHeroBezier(Bezier item){
  heroBezier=item;
}
//For Fairy
void Hero::setFairyPositionX(float posX){
  fairyPosX=posX;
}
void Hero::setFairyPositionY(float posY){
  fairyPosY=posY;
}
void Hero::setFairyPositionZ(float posZ){
  fairyPosZ=posZ;
}
void Hero::setFairyTheta(float theta){
  fairyTheta=theta;
}
void Hero::setFairyPhi(float phi){
  fairyPhi=phi;
}
void Hero::setFairyBezier(Bezier bezier){
  fairyBezier=bezier;
}

//Drawing Functions
void Hero::drawHero(){}

void Hero::drawFairy(){}
