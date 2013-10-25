#include <cstdlib>
#include <GL/glut.h>
#include <iostream>

#include "box.hpp"
#include "color.hpp"
#include "loadBitmap.h"


void box::drawLid() {
	glBegin(GL_POLYGON);
	topcolor_.gradientUp().color() ;
	glVertex3f(  side_,  side_,  side_ );
	topcolor_.color() ;
	glVertex3f(  side_,  side_, -1.0*side_ );
	glVertex3f( -1.0*side_,  side_, -1.0*side_ );
	topcolor_.gradientDown().color() ;
	glVertex3f( -1.0*side_,  side_,  side_ );
	glEnd();
}

void box::drawMe() {
	
	glCallList(onlyBox);
	glPushMatrix();
		glTranslatef(-1.0*side_,side_,-1.0*side_);
		glRotatef(angle_,-1.0,0.0,0.0);
		glTranslatef(side_,-1.0*side_,side_);
		glCallList(onlyLid);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(side_, 0.0, 0.0);
		glRotatef(angle_*15.0,-1.0,0.0,0.0);
		glCallList(handle);
	glPopMatrix();
}

void box::drawBox() {	
	
	GLuint Texture = loadBitmap("./img/wood.bmp");

	glEnable(GL_TEXTURE_2D);
	// glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, Texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); 
	glVertex3f(  side_, -1.0*side_, -1.0*side_ ); 
	glTexCoord2f(0.0, 1.0); 
	glVertex3f(  side_,  side_, -1.0*side_ );
	glTexCoord2f(1.0, 1.0); 
	glVertex3f( -1.0*side_,  side_, -1.0*side_ );
	glTexCoord2f(1.0, 0.0); 
	glVertex3f( -1.0*side_, -1.0*side_, -1.0*side_ );
	 
	glEnd();
	
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); 
	glVertex3f(  side_, -1.0*side_, side_ );
	glTexCoord2f(0.0, 1.0); 
	glVertex3f(  side_,  side_, side_ );
	glTexCoord2f(1.0, 1.0); 
	glVertex3f( -1.0*side_,  side_, side_ );
	glTexCoord2f(1.0, 0.0); 
	glVertex3f( -1.0*side_, -1.0*side_, side_ );
	glEnd();
	glDisable(GL_TEXTURE_2D);
 
	glBegin(GL_POLYGON);
	rightcolor_.gradientUp().color() ;
	glVertex3f( side_, -1.0*side_, -1.0*side_ );
	rightcolor_.color() ;
	glVertex3f( side_,  side_, -1.0*side_ );
	glVertex3f( side_,  side_,  side_ );
	rightcolor_.gradientDown().color() ;
	glVertex3f( side_, -1.0*side_,  side_ );
	glEnd();
	 
	glBegin(GL_POLYGON);
	leftcolor_.gradientUp().color() ;
	glVertex3f( -1.0*side_, -1.0*side_,  side_ );
	leftcolor_.color() ;
	glVertex3f( -1.0*side_,  side_,  side_ );
	glVertex3f( -1.0*side_,  side_, -1.0*side_ );
	leftcolor_.gradientDown().color() ;
	glVertex3f( -1.0*side_, -1.0*side_, -1.0*side_ );
	glEnd();
	 
	glBegin(GL_POLYGON);
	bottomcolor_.gradientUp().color() ;
	glVertex3f(  side_, -1.0*side_, -1.0*side_ );
	bottomcolor_.color() ;
	glVertex3f(  side_, -1.0*side_,  side_ );
	glVertex3f( -1.0*side_, -1.0*side_,  side_ );
	bottomcolor_.gradientDown().color() ;
	glVertex3f( -1.0*side_, -1.0*side_, -1.0*side_ );
	glEnd();

}

void box::drawHandle() {
	GLUquadricObj* qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL); /* flat shaded */
	gluQuadricNormals(qobj, GLU_FLAT);
	gluQuadricTexture(qobj, GLU_TRUE);

	glPushMatrix() ;
		glRotatef( 90.0, 0.0, 1.0, 0.0 );
		handlecolor_.gradientDown().color() ;
		gluCylinder(qobj, 0.05*side_, 0.05*side_, 0.4*side_, 15, 5);
		glPushMatrix() ;
			glTranslatef(0.0, 0.0, 0.4*side_) ;
			glRotatef( 90.0, 1.0, 0.0, 0.0 );
			handlecolor_.color() ;
			gluCylinder(qobj, 0.05*side_, 0.05*side_, 0.4*side_, 15, 5);
		glPopMatrix() ;
		glTranslatef(0.0, -0.4*side_, 0.4*side_) ;
		handlecolor_.gradientUp().color() ;
		gluCylinder(qobj, 0.05*side_, 0.05*side_, 1.0*side_, 15, 5);
		
	glPopMatrix() ;
}

void box::closeLid(double step) {
	double angle = angle_ - step ;
	if (angle >= 0 && angle <= 135) angle_ = angle ;
	else angle_ = 0.0 ;
}

void box::openLid(double step) {
	double angle = angle_ + step ;
	if (angle >= 0 && angle <= 135) angle_ = angle ;
	else angle_ = 135.0 ;
}

double box::getAngle() { return angle_ ;}

box::box(double side, double angle) :
	handlecolor_(0.0,0.0,0.0),
	frontcolor_(0.0,0.0,0.0),
	backcolor_(0.0,0.0,0.0) ,
	leftcolor_(0.0,0.0,0.0) ,
	rightcolor_(0.0,0.0,0.0) ,
	topcolor_(0.0,0.0,0.0) ,
	bottomcolor_(0.0,0.0,0.0) {
		side_ = side ;
		angle_ = angle ;
}

void box::initialise() {		
		onlyBox = glGenLists (1);
		glNewList(onlyBox, GL_COMPILE);
			drawBox() ;
		glEndList();
		
		onlyLid = glGenLists (1);
		glNewList(onlyLid, GL_COMPILE);
			drawLid() ;
		glEndList();
		
		handle = glGenLists (1);
		glNewList(handle, GL_COMPILE);
			drawHandle() ;
		glEndList();
			
}

