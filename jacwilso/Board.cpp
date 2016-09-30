#include "Board.h"

Board::Board(){
  if(!qobj){ // stop constructing multiple copies
    qobj=gluNewQuadric();
    gluQuadricNormals(qobj,GLU_SMOOTH);
  }

  // initial parameters
  hoverPos=0; objTheta=0; lookAtX=0; lookAtY=0; lookAtZ=0;
  stomp=false; turn=false; bankLeft=false; bankRight=false;
  streakNum=0;
}

// BOARD -- skate board deck
void Board::drawBoard(){
  glColor3f(1,0,0); // red
  //glColor3ub(253,64,92); // color I wanted but lighting forbade me from implementing
  glPushMatrix();
    glTranslatef(-3,.1,0);
    glRotatef(90,1,0,0);
    gluCylinder(qobj,1,1,.2,32,1); // front of board
    glPushMatrix();
      glTranslatef(0,0,.2);
      gluPartialDisk(qobj,0,1,32,1,0,-180); // bottom cap the the front of board
    glPopMatrix();
    glPushMatrix();
      glRotatef(180,1,0,0); // had to roatate an additional time so the color of the cylinder, rectangle, and disks were all the same
      gluPartialDisk(qobj,0,1,32,1,0,-180); // top cap to the front of board
    glPopMatrix();
  glPopMatrix();
  glPushMatrix();
    glScalef(6,.2,2); // streched to size deck
    glutSolidCube(1); // rectangular deck
  glPopMatrix();
  glPushMatrix();
    glTranslatef(3.5,.195,0);
    glRotatef(20,0,0,1);
    glScalef(1.2,.2,2);
    glutSolidCube(1); // back lip/up-curve of board, manipulated into position for angle
  glPopMatrix();
}

// STOMP PAD -- pad on the top which signals the forward/backward movement by pressing up and down
void Board::drawStompPad(){
  glColor3ub(22,135,83);
  glPushMatrix();
    glRotatef(90,1,0,0);
    gluCylinder(qobj,.8,.8,.1,32,1); // cylinder 
    gluDisk(qobj,0,.8,32,1); // cap to cylinder
  glPopMatrix();
}

// BOTTOM BARS -- bars on bottom of board
void Board::drawBars(){
  glColor3f(.4f,.4f,.4f); // gray
  glPushMatrix();
    glRotatef(90,0,1,0);
    gluCylinder(qobj,.08,.08,1.8,32,1); // cylinder/ tube
  glPopMatrix();
  glPushMatrix();
    glRotatef(90,0,1,0);
    gluDisk(qobj,0,.08,32,1); // front (relative to the skateboard) cap to cylinder
  glPopMatrix();
  glPushMatrix();
    glTranslatef(1.8,0,0);
    glRotatef(90,0,1,0);
    gluDisk(qobj,0,.08,32,1); // back cap to cylinder
  glPopMatrix();
}

// HOLDER -- block on bottom of skateboard
void Board::drawHolder(){
  glPushMatrix();
    glColor3ub(154,79,112);
    glScalef(1.2,.2,.8);
    glutSolidCube(1);
  glPopMatrix();
}

// HOVER PAD -- pads on bottom of board 
void Board::drawHoverPad(){
  glPushMatrix();
    glRotatef(90,1,0,0);
    glColor3f(0,0,0); // black
    gluCylinder(qobj,.9,.9,.05,32,1); // base cylinder
    glPushMatrix();
      glTranslatef(0,0,.05);
      gluDisk(qobj,0,.9,32,1); // cap to the base cylinder
    glPopMatrix();
    gluCylinder(qobj,.7,.7,.15,32,1); // center cylinder
    glPushMatrix();
      glColor3ub(199,200,204);
      glTranslatef(0,0,.15);
      gluDisk(qobj,0,.7,32,1); // cap to the center cylinder
    glPopMatrix();
  glPopMatrix();
}

// HOVER ANIMATION -- an disk ring that will oscillate up and down to simulate a hover
void Board::drawHover(){
  glPushMatrix();
    glColor3f(0,0,1); // blue
    glRotatef(90,1,0,0); 
    gluDisk(qobj,.5,.7,32,1); // disk/ ring 
  glPopMatrix();
}

// BOARD STREAK -- a transparent version of the board, which is left behind to act as a streak
void Board::drawStreak(){
  // identical to the rectangle 
  glEnable(GL_BLEND); // enable blending
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // the use of the alpha in the color function
  glColor4f(1,1,1,.3); // white and very transparent
  glPushMatrix();
    glScalef(6,.2,2); // streched to size deck
    glutWireCube(1); // rectangular deck
  glPopMatrix();
  glPushMatrix();
    glTranslatef(3.5,.195,0);
    glRotatef(20,0,0,1);
    glScalef(1.2,.2,2);
    glutWireCube(1); // back lip/up-curve of board, manipulated into position for angle
  glPopMatrix();
  glDisable(GL_BLEND);
}

// HOVER BOARD AGGRAGATE -- past function calls compiled together
void Board::drawHoverBoard(){
  drawBoard(); // board is at the center
  glPushMatrix();
    if(stomp) // if the board is moving forward act as if the someone is pushing down the stomp pad
      glTranslatef(2,.12,0);
    else // else the stomp pad should be raised
      glTranslatef(2,.15,0);
    drawStompPad();
  glPopMatrix();
  glPushMatrix();
    glTranslatef(1.9,-.1,0);
    drawHoverPad(); // add the back hoverpad
  glPopMatrix();
  glPushMatrix();
    glTranslatef(-2.4,-.1,0); 
    drawHoverPad(); // add the front hoverpad
  glPopMatrix();
  glPushMatrix();
    glTranslatef(1.9,-.22-hoverPos/10,0);
    drawHover(); // add the hover animation for the back pad, y-position variable
  glPopMatrix();
  glPushMatrix();
    glTranslatef(-2.4,-.22-hoverPos/10,0);
    drawHover(); // add the hover animation for the front pad, y-position variable
  glPopMatrix();
  glPushMatrix();
    glTranslatef(-.2,-.1,0);
    drawHolder(); // add the block center between the hover pads on the bottom
  glPopMatrix();
  glPushMatrix();
    glTranslatef(-1.1,-.16,.7);
    drawBars(); // add the right bar on the bottom of the board
  glPopMatrix();
  glPushMatrix();
    glTranslatef(-1.1,-.16,-.7);
    drawBars(); // add the left bar on the bottom of the board
  glPopMatrix();
}

void Board::setVars(float lookAtX,float lookAtY,float lookAtZ,float objTheta,float hoverPos,bool stomp,bool turn,bool bankLeft,bool bankRight,float streak[STREAKS][3],int streakNum){
  this->lookAtX=lookAtX;
  this->lookAtY=lookAtY;
  this->lookAtZ=lookAtZ;
  this->objTheta=objTheta;
  this->hoverPos=hoverPos;
  this->stomp=stomp;
  this->turn=turn;
  this->bankLeft=bankLeft;
  this->bankRight=bankRight;
  this->streakNum=streakNum;
  for(int i=0; i<STREAKS; i++)
    for(int j=0; j<3; j++)
      this->streak[i][j]=streak[i][j];
}

// generateObjectDL() /////////////////////////////////////////////////////
//
//  This function creates a display list with the code to draw the hoverboard 
//      and the streak that follows the board. This list is called multiple     
//      times throughout the render to change positions.
//
////////////////////////////////////////////////////////////////////////////////
void Board::generateObjectDL(){
    objectDL=glGenLists(1);
    glNewList(objectDL, GL_COMPILE);
      glPushMatrix();
        glTranslatef(lookAtX,lookAtY,lookAtZ); // translate to the center of the arc ball
        glRotatef(objTheta,0,1,0); // the direction of the board
        if(turn){ // if the board is turning in the XZ plane (and not moving), prop the board upwards (like someone is stamping on the back of the board)
          glRotatef(-35,0,0,1);
          glTranslatef(0,2.3,0);
        }
        if(bankLeft){ // if the board is turning right, have the board look like it is banking left 
          glRotatef(-25,1,0,0);
          glTranslatef(0,.4,0);
        }
        if(bankRight){ // if the board is turning left, have the board look like it is banking right 
          glRotatef(25,1,0,0);
          glTranslatef(0,.4,0);
        }
        drawHoverBoard(); // draw the agragate board w/ transforms
      glPopMatrix();
    for(int i=0; i<STREAKS; i++){ // the streak following the board
      glPushMatrix();
        glTranslatef(streak[i][0],lookAtY,streak[i][1]); // translate to the prior locations of the board
        glRotatef(streak[i][2],0,1,0); // rotate the board to the angle of the turn
        drawStreak(); // draw the streak of the board
      glPopMatrix();
    }
    glEndList();
}
