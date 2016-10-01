#include "Bomberman.h"

// setup the bomberman sprite
Bomberman::Bomberman(){
	fuseLength=1;
	qobj=gluNewQuadric();  
	gluQuadricNormals(qobj,GLU_SMOOTH);
}

// draw the eye -- vertical cylinder
void Bomberman::drawEye(){
	glColor3f(0,0,0);
	glPushMatrix();
	glRotatef(90,1,0,0);
	gluCylinder(qobj,.2,.2,1.6,32,1);
	glPopMatrix();
}

// draw the eye brow -- cube scaled and rotated
void Bomberman::drawEyeBrow(){
	glColor3f(0,0,0);
	glPushMatrix();
	glRotatef(-12,1,0,0);
	glScalef(-.2,.3,1.2);
	glutSolidCube(1);
	glPopMatrix();
}

// draw the head -- the outer hood (white), pony tail (white), face (tan), and pom-pom (pink) in that order
void Bomberman::drawHead(){
	glColor3f(1,1,1);
	glutSolidSphere(2,32,32);
	glPushMatrix();
	glTranslatef(1.6,1,0);
	glRotatef(90,0,1,0);
	glRotatef(-35,1,0,0);
	gluCylinder(qobj,.2,.2,2,32,1);
	glPopMatrix();
	glColor3ub(251,234,191);
	glPushMatrix();
	glTranslatef(-.3,0,0);
	glScalef(1.8,1.82,1.88);
	glutSolidSphere(1,32,32);
	glPopMatrix();
	glColor3ub(255,20,147);
	glPushMatrix();
	glTranslatef(3.2,2.15,0);
	glutSolidSphere(1,32,32);
	glPopMatrix();
}

// draw the torso -- elongated sphere=upper body (blue), down translated sphere=hips (blue), cylinder belt (black), belt buckle (gold), inner belt of buckle (black)
void Bomberman::drawTorso(){
	glColor3ub(51,51,255);
	glPushMatrix();
	glScalef(1.1,2.1,1.1);
	glutSolidSphere(1,32,32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,-1,0);
	glScalef(1.2,1.2,1.2);
	glutSolidSphere(1,32,32);
	glPopMatrix();
	glColor3f(0,0,0);
	glPushMatrix();
	glTranslatef(0,-.4,0);
	glRotatef(90,1,0,0);
	gluCylinder(qobj,1.2,1.2,.6,32,1);
	glPopMatrix();
	glColor3ub(255,215,0);
	glPushMatrix();
	glTranslatef(-1.05,-.7,0);
	glScalef(.4,.75,.9);
	glutSolidCube(1);
	glPopMatrix();
	glColor3f(0,0,0);
	glPushMatrix();
	glTranslatef(-1.1,-.7,0);
	glScalef(.4,.4,.55);
	glutSolidCube(1);
	glPopMatrix();
}

// draw arm and hand -- arm cylinder (white) and hand (pink)
void Bomberman::drawArm(){
	glColor3f(1,1,1);
	glPushMatrix();
	gluCylinder(qobj,.3,.25,4,32,1);
	glPopMatrix();
	glColor3ub(255,20,147);
	glPushMatrix();
	glTranslatef(0,0,4);
	glutSolidSphere(.8,32,32);
	glPopMatrix();
}

// draw leg and foot -- leg cylinder (white) and foot (pink)
void Bomberman::drawLeg(){
	glColor3f(1,1,1);
	glPushMatrix();
	gluCylinder(qobj,.3,.35,4,32,1);
	glPopMatrix();
	glColor3ub(255,20,147);
	glPushMatrix();
	glTranslatef(-.4,0,3.8);
	glRotatef(10,0,1,0);
	glScalef(1.6,1,1);
	glutSolidSphere(.8,32,32);
	glPopMatrix();
}

// draw bomb -- main bomb bulb sphere (black), nozzle up cylinder and disk (black), fuse wire cylinder (white-like), spark/explosion (red/ orange)
void Bomberman::drawBomb(){
	glColor3f(.05,.05,.05);
	glutSolidSphere(1.8,32,32);     
	glPushMatrix();
	glTranslatef(0,2,0);
	glRotatef(90,1,0,0);
	gluCylinder(qobj,.7,.8,1.2,32,1);
	glPushMatrix();
	glRotatef(180,1,0,0);
	gluDisk(qobj,0,.7,32,1);
	glPopMatrix();
	glPopMatrix();

	glColor3f(.9,.9,.9);
	glPushMatrix();
	glTranslatef(0,2,0);
	glRotatef(-90,1,0,0);
	gluCylinder(qobj,.15,.15,1.6*fuseLength,32,1); // shorten fuse according to fuseLength
	glPopMatrix();

	glColor3f(1,0,0);
	for(int i=0; i<4; i++){
		glPushMatrix();
		glTranslatef(0,2.6+.8*fuseLength,0); // move spark down with fuse wire
		glRotatef(35*i,i%2,(i+2)%2,(i+7)%2); // different orientaiton sparks
		if(fuseLength<.15)
			glScalef(.4,3.2,.6);
		else
			glScalef(.2,1.6,.3);
		glutSolidCube(1);
		glPopMatrix();
	}
	glColor3ub(255,153,0);
	glPushMatrix();
	glTranslatef(0,2.6+.8*fuseLength,0);
	if(fuseLength<.15)
		glScalef(2,2,2);
	glutSolidSphere(.4,32,32);
	glPopMatrix();
}

// assemble all the pieces in the correct places
void Bomberman::drawMan(){
	glPushMatrix();
	glTranslatef(0,3.3,0);
	glPushMatrix();
	glTranslatef(-1.99,1.2,.7);
	drawEyeBrow();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.99,1.2,-.7);
	glScalef(1,1,-1);
	drawEyeBrow();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.99,.9,.6);
	drawEye();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.99,.9,-.6);
	drawEye();
	glPopMatrix();
	drawHead();
	glPopMatrix();
	drawTorso();
	glPushMatrix();
	glTranslatef(.3,.7,1);
	glRotatef(20,1,0,0);
	glRotatef(-70,0,1,0);
	drawArm();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,.7,-.8);
	glRotatef(80,0,0,1);
	glRotatef(-50,0,1,0);
	glScalef(1,1,-1);
	drawArm();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,-1,.2);
	glRotatef(70,1,0,0);
	drawLeg();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,-1,-.2);
	glRotatef(110,1,0,0);
	drawLeg();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1,5.3,-3.7);
	drawBomb();
	glPopMatrix();
}

// display list of man -- not necesary since it isn't static
void Bomberman::generateBombermanDL(){
	bombermanDL=glGenLists(1);
	glNewList(bombermanDL,GL_COMPILE);
	drawMan();
	glEndList();
}
