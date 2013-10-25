#include <vector>
#include <GL/glut.h>

#include "bodyNode.hpp"
#include "body.hpp"
#include "loadBitmap.h"

using namespace std ;

body::body() {
	head_= neck_=  chest_= torso_= hip_= larm_= rarm_= lelbow_= relbow_= lhand_= rhand_= lthigh_= rthigh_= lleg_= rleg_= lfoot_= rfoot_= NULL ;
}

void body::initialise() {
	parts_ = glGenLists (6);		// Lists for symmetric body parts
									// i.e. arms, elbows, hands, thighs, 
									// calves, feet etc.
	
	GLUquadricObj* qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL); /* flat shaded */
	gluQuadricNormals(qobj, GLU_FLAT);
	gluQuadricTexture(qobj, GLU_TRUE);
	
	/* Design of Hip (Torso 3) */
	hip_ = new bodyNode (0.0,0.0,0.0) ;
	glNewList(hip_->displayList_, GL_COMPILE);
		glPushMatrix() ;
			glColor3f(0.f, 0.f, 0.f) ;
			glTranslatef( 0.0f, 0.25f, 0.0f );
			glRotatef( 90.0, 1.0, 0.0, 0.0 );
			gluCylinder(qobj, 0.5f, 0.55f, 0.7f, 15, 5);
		glPopMatrix() ;
	glEndList();
	
	/* Design of Torso (Torso 2) */
	torso_ = new bodyNode (0.0,0.25,0.0) ;
	glNewList(torso_->displayList_, GL_COMPILE);
		glPushMatrix() ;
			glColor3f(0.f, 0.f, 0.f) ;
			glTranslatef( 0.0f, 0.1f, 0.0f );
			glutSolidSphere(0.55f,10,10);
		glPopMatrix() ;
	glEndList();
	hip_->addNode(torso_) ;

	/* Design of Thighs */
	glNewList(parts_, GL_COMPILE);
		glPushMatrix() ;
			glColor3f(0.1f, 0.2f, 0.8f) ;
			glTranslatef( 0.0f, -0.07f, 0.0f );
			glutSolidSphere(0.3f,10,10);
			glPushMatrix() ;
				glTranslatef( 0.0f, -0.12f, 0.0f );
				glRotatef( 90.0, 1.0, 0.0, 0.0 );
				gluCylinder(qobj, 0.25f, 0.18f, 1.2f, 15, 5);
			glPopMatrix() ;

		glPopMatrix() ;
	glEndList();
	
	lthigh_ = new bodyNode (0.26,-0.45,0.0) ;
	lthigh_->displayList_ = parts_ ;
	hip_->addNode(lthigh_) ;

	rthigh_ = new bodyNode (-0.26,-0.45,0.0) ;
	rthigh_->displayList_ = parts_ ;
	hip_->addNode(rthigh_) ;

	lthigh_->llimitZ_ = -5.0; lthigh_->ulimitZ_ = 50.0 ;
	lthigh_->llimitX_ = -120.0; lthigh_->ulimitX_ = 40.0 ;
	lthigh_->llimitY_ = -15.0; lthigh_->ulimitY_ = 15.0 ;
	
	rthigh_->llimitZ_ = -50.0; rthigh_->ulimitZ_ = 5.0 ;
	rthigh_->llimitX_ = -120.0; rthigh_->ulimitX_ = 40.0 ;
	rthigh_->llimitY_ = -15.0; rthigh_->ulimitY_ = 15.0 ;
	

	/* Design of Calves */
	glNewList(parts_+1, GL_COMPILE);
		glPushMatrix() ;
			glColor3f(0.1f, 0.2f, 0.8f) ;
			glTranslatef( 0.0f, -0.07f, 0.0f );
			glutSolidSphere(0.19f,10,10);
			glPushMatrix() ;
				glTranslatef( 0.0f, -0.10f, 0.0f );
				glRotatef( 90.0, 1.0, 0.0, 0.0 );
				gluCylinder(qobj, 0.15f, 0.15f, 1.1f, 15, 5);
			glPopMatrix() ;
			glPushMatrix() ;
				glTranslatef( 0.0f, -1.33f, 0.0f );
				glutSolidSphere(0.16f,10,10);
			glPopMatrix() ;

		glPopMatrix() ;
	glEndList();
	
	lleg_ = new bodyNode (0.0f, -1.44f, 0.0f) ;
	lleg_->displayList_ = parts_ +1;
	lthigh_->addNode(lleg_) ;
	lleg_->llimitZ_ =  lleg_->ulimitZ_ = 0.0 ;
	lleg_->llimitY_ =  lleg_->ulimitY_ = 0.0 ;
	lleg_->llimitX_ = 0.0; lleg_->ulimitX_ = 135.0 ;
	
	rleg_ = new bodyNode (0.0f, -1.44f, 0.0f) ;
	rleg_->displayList_ = parts_ +1;
	rthigh_->addNode(rleg_) ;
	rleg_->llimitZ_ =  rleg_->ulimitZ_ = 0.0 ;
	rleg_->llimitY_ =  rleg_->ulimitY_ = 0.0 ;
	rleg_->llimitX_ = 0.0; rleg_->ulimitX_ = 135.0 ;
	
	
	/* Design of feet */
	glNewList(parts_+2, GL_COMPILE);
		glPushMatrix() ;
			glColor3f(0.25f, 0.2f, 0.15f) ;
			glTranslatef( 0.0f, -0.1f, 0.23f );
			glBegin(GL_QUAD_STRIP) ;
				glVertex3f(  0.13f, 0.02, 0.35 );//fr
				glVertex3f(  0.13f,-0.1, 0.35 ); 
				glVertex3f( -0.13f, 0.02, 0.35 );//fl
				glVertex3f( -0.13f,-0.1, 0.35 );
				glVertex3f( -0.175f, 0.1,-0.35 );//bl
				glVertex3f( -0.175f,-0.1,-0.35 );
				glVertex3f(  0.175f, 0.1,-0.35 );//br
				glVertex3f(  0.175f,-0.1,-0.35 );
				glVertex3f(  0.13f, 0.02, 0.35 );//fr
				glVertex3f(  0.13f,-0.1, 0.35 ); 
			glEnd() ;
			
			glBegin(GL_QUADS) ;
				glVertex3f(  0.13f, 0.02, 0.35 );//Top
				glVertex3f( -0.13f, 0.02, 0.35 );
				glVertex3f( -0.175f, 0.1,-0.35 );
				glVertex3f(  0.175f, 0.1,-0.35 );
				glVertex3f(  0.13f,-0.1, 0.35 ); //Bottom
				glVertex3f( -0.13f,-0.1, 0.35 );
				glVertex3f( -0.175f,-0.1,-0.35 );
				glVertex3f(  0.175f,-0.1,-0.35 );
			glEnd() ;
		glPopMatrix() ;
	glEndList();

	lfoot_ = new bodyNode(0.0f, -1.4f, 0.0f) ;
	lfoot_->displayList_ = parts_+2 ;
	lleg_->addNode(lfoot_) ;
	
	rfoot_ = new bodyNode(0.0f, -1.4f, 0.0f) ;
	rfoot_->displayList_ = parts_+2 ;
	rleg_->addNode(rfoot_) ;

	lfoot_->llimitZ_ = -5.0; lfoot_->ulimitZ_ = 5.0 ;
	lfoot_->llimitX_ = -30.0; lfoot_->ulimitX_ = 60.0 ;
	lfoot_->llimitY_ = -15.0; lfoot_->ulimitY_ = 15.0 ;
	
	rfoot_->llimitZ_ = -5.0; rfoot_->ulimitZ_ = 5.0 ;
	rfoot_->llimitX_ = -30.0; rfoot_->ulimitX_ = 60.0 ;
	rfoot_->llimitY_ = -15.0; rfoot_->ulimitY_ = 15.0 ;
	

	/* Design chest (Torso) */
	chest_ = new bodyNode(0.0, 0.0, 0.0) ;
	GLuint suitTexture = loadBitmap("./img/suit2.bmp");
	glNewList(chest_->displayList_, GL_COMPILE);
		glPushMatrix() ;
			glColor3f(0.8f, 0.8f, 0.8f) ;
			glRotatef( -90.0, 1.0, 0.0, 0.0 );
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, suitTexture);
			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
			glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
			glDisable(GL_TEXTURE_GEN_S);
			glDisable(GL_TEXTURE_GEN_T);
			gluCylinder(qobj, 0.5f, 0.7f, 1.4f, 15, 5);
			glTranslatef( 0.0f, 0.0f, 1.4f);
			glDisable(GL_TEXTURE_2D);
			glColor3f(0.0f, 0.0f, 0.0f) ;
			gluDisk(qobj, 0.0f, 0.7f, 15, 1);
			
		glPopMatrix() ;
	glEndList();
	torso_->addNode(chest_) ;

	/* Design arms */
	glNewList(parts_+3, GL_COMPILE);
		glPushMatrix() ;
			glColor3f(0.f, 0.f, 0.f) ;
			glTranslatef( 0.0f, 0.0f, 0.0f );
			glutSolidSphere(0.15f,10,10);
			glTranslatef( 0.0f, -0.09f, 0.0f );
			glRotatef( 90.0, 1.0, 0.0, 0.0 );
			gluCylinder(qobj, 0.15f, 0.14f, 0.9f, 15, 5);
		glPopMatrix() ;
	glEndList();

	larm_ = new bodyNode (0.75,1.2,0.0) ;
	larm_->displayList_ = parts_ +3;
	chest_->addNode(larm_) ;

	rarm_ = new bodyNode (-0.75,1.2,0.0) ;
	rarm_->displayList_ = parts_ +3;
	chest_->addNode(rarm_) ;
	torso_->llimitZ_ = -20.0; torso_->ulimitZ_ = 20.0 ;
	torso_->llimitX_ = -15.0; torso_->ulimitX_ = 45.0 ;
	torso_->llimitY_ = -15.0; torso_->ulimitY_ = 15.0 ;
	
	chest_->llimitZ_ = -20.0; chest_->ulimitZ_ = 20.0 ;
	chest_->llimitX_ = -15.0; chest_->ulimitX_ = 45.0 ;
	chest_->llimitY_ = -15.0; chest_->ulimitY_ = 15.0 ;
	

	/* Design forearms */
	glNewList(parts_+4, GL_COMPILE);
		glPushMatrix() ;
			glColor3f(0.f, 0.f, 0.f) ;
			glTranslatef( 0.0f, -0.09f, 0.0f );
			glutSolidSphere(0.15f,10,10);
			glTranslatef( 0.0f, 0.0f, 0.0f );
			glRotatef( 90.0, 1.0, 0.0, 0.0 );
			gluCylinder(qobj, 0.14f, 0.12f, 0.9f, 15, 5);
		glPopMatrix() ;
	glEndList();

	lelbow_ = new bodyNode (0.0,-1.0,0.0) ;
	lelbow_->displayList_ = parts_ +4;
	larm_->addNode(lelbow_) ;
	lelbow_->llimitX_ =  lelbow_->ulimitX_ = 0.0 ;
	lelbow_->llimitY_ =  lelbow_->ulimitY_ = 0.0 ;
	lelbow_->ulimitZ_ = 0.0; lelbow_->llimitZ_ = -135.0 ;
	
	relbow_ = new bodyNode (0.0,-1.0,0.0) ;
	relbow_->displayList_ = parts_ +4;
	rarm_->addNode(relbow_) ;
	relbow_->llimitX_ =  relbow_->ulimitX_ = 0.0 ;
	relbow_->llimitY_ =  relbow_->ulimitY_ = 0.0 ;
	relbow_->llimitZ_ = 0.0; relbow_->ulimitZ_ = 135.0 ;
	

	/* Design Hands */
	glNewList(parts_+5, GL_COMPILE);
		glPushMatrix() ;
			glColor3f(0.96f, 0.76f, 0.47f) ;
			glBegin(GL_QUAD_STRIP) ; //base
				glVertex3f(  0.13f, 0.0, 0.1 );//fr
				glVertex3f(  0.16f,-0.3, 0.12 ); 
				glVertex3f( -0.13f, 0.0, 0.1 );//fl
				glVertex3f( -0.16f,-0.3, 0.12 );
				glVertex3f( -0.12f, 0.0,-0.06 );//bl
				glVertex3f( -0.15f,-0.3,-0.04 );
				glVertex3f(  0.12f, 0.0,-0.06 );//br
				glVertex3f(  0.15f,-0.3,-0.04 );
				glVertex3f(  0.13f, 0.0, 0.1 );//fr
				glVertex3f(  0.16f,-0.3, 0.12 ); 
			glEnd() ;
			
			glBegin(GL_QUAD_STRIP) ; //fore
				glVertex3f(  0.16f,-0.3, 0.12 );//fr
				glVertex3f(  0.09f,-0.6, 0.0 );
				glVertex3f( -0.16f,-0.3, 0.12 );//fl
				glVertex3f( -0.09f,-0.6, 0.0 );
				glVertex3f( -0.15f,-0.3,-0.04 );//bl
				glVertex3f( -0.09f,-0.6,-0.1 );
				glVertex3f(  0.15f,-0.3,-0.04 );//br
				glVertex3f(  0.09f,-0.6,-0.1 );
				glVertex3f(  0.16f,-0.3, 0.12 );//fr
				glVertex3f(  0.09f,-0.6, 0.0 );
			glEnd() ;
			
			glBegin(GL_QUADS) ;
				glVertex3f(  0.13f, 0.0, 0.1 );//Top
				glVertex3f( -0.13f, 0.0, 0.1 );
				glVertex3f( -0.12f, 0.0,-0.06 );
				glVertex3f(  0.12f, 0.0,-0.06 );
				glVertex3f(  0.09f,-0.6, 0.0 );//Bottom
				glVertex3f( -0.09f,-0.6, 0.0 );
				glVertex3f( -0.09f,-0.6,-0.1 );
				glVertex3f(  0.09f,-0.6,-0.1 );
			glEnd() ;
		glPopMatrix() ;
	glEndList();

	lhand_ = new bodyNode (0.0,-1.0,0.0) ;
	lhand_->displayList_ = parts_ +5;
	lelbow_->addNode(lhand_) ;
	lhand_->changeAngleY(90.0);
	
	rhand_ = new bodyNode (0.0,-1.0,0.0) ;
	rhand_->displayList_ = parts_ +5;
	relbow_->addNode(rhand_) ;
	rhand_->changeAngleY(-90.0);
	
	lhand_->llimitZ_ = -90.0; lhand_->ulimitZ_ = 90.0 ;
	lhand_->llimitX_ = -45.0; lhand_->ulimitX_ = 45.0 ;
	lhand_->llimitY_ = 0.0; lhand_->ulimitY_ = 180.0 ;
	
	rhand_->llimitZ_ = -90.0; rhand_->ulimitZ_ = 90.0 ;
	rhand_->llimitX_ = -45.0; rhand_->ulimitX_ = 45.0 ;
	rhand_->llimitY_ = -180.0; rhand_->ulimitY_ = 0.0 ;
	
	/* Design Neck */
	neck_ = new bodyNode (0.0, 1.4, 0.0);
	glNewList(neck_->displayList_, GL_COMPILE);
		glPushMatrix() ;
			glColor3f(0.8f, 0.63f, 0.4f) ;
			glTranslatef(0.0,-0.2,0.0);
			glRotatef( -90.0, 1.0, 0.0, 0.0 );
			gluCylinder(qobj, 0.20f, 0.18f, 0.7f, 15, 15);
		glPopMatrix() ;
	glEndList();
	chest_->addNode(neck_) ;
	neck_->llimitZ_ = -30.0; neck_->ulimitZ_ = 30.0 ;
	neck_->llimitX_ = -30.0; neck_->ulimitX_ = 30.0 ;
	neck_->llimitY_ = -35.0; neck_->ulimitY_ = 35.0 ;
	
	/* Design Head */
	head_ = new bodyNode (0.0, 0.3, 0.0);
	glNewList(head_->displayList_, GL_COMPILE);
		glPushMatrix() ;
			glColor3f(0.96f, 0.76f, 0.47f) ;
			glRotatef( -90.0, 1.0, 0.0, 0.0 );
			gluCylinder(qobj, 0.26f, 0.34f, 0.68f, 15, 5);
			gluDisk(qobj, 0.0f, 0.26f, 15, 1);
			
			glColor3f(0.5f, 0.0f, 0.1f) ;
			glPushMatrix() ; //hat
				glTranslatef(0.0,0.0,0.58);
				gluCylinder(qobj, 0.5f, 0.01f, 0.3f, 15,5);
			glPopMatrix() ;
			
			glColor3f(0.0f, 0.1f, 0.2f) ;
			glPushMatrix() ; //left eye
				glTranslatef(0.13,-0.28,0.45);
				glRotatef( 90.0, 1.0, 0.0, 0.4 );
				gluDisk(qobj, 0.0f, 0.1f, 6, 1);
			glPopMatrix() ;
			
			glPushMatrix() ; //right eye
				glTranslatef(-0.13,-0.28,0.45);
				glRotatef( 90.0, 1.0, 0.0, -0.4 );
				gluDisk(qobj, 0.0f, 0.1f, 6, 1);
			glPopMatrix() ;
			
			glColor3f(0.8f, 0.56f, 0.45f) ;
			glPushMatrix() ; //nose
				glTranslatef(0.0,-0.27,0.2);
				glRotatef( 5.0, 1.0, 0.0, 0.0 );
				glutSolidCone(0.06f, 0.3f, 15, 5);
			glPopMatrix() ;
		glPopMatrix() ;
	glEndList();
	neck_->addNode(head_) ;
	head_->llimitZ_ = -18.0; head_->ulimitZ_ = 18.0 ;
	head_->llimitX_ = -18.0; head_->ulimitX_ = 18.0 ;
	head_->llimitY_ = -35.0; head_->ulimitY_ = 35.0 ;

}

void body::draw() {
	if (hip_!=NULL) hip_->draw() ;
}
