#include <iostream>
#include <cmath>
#include <GL/glut.h>

#include "box.hpp"
#include "body.hpp"
#include "definitions.h"
#include "loadBitmap.h"

using namespace std ;

int main(int argc, char* argv[]){
 
	//  Initialize GLUT and process user parameters
	glutInit(&argc,argv);
	
	//  Request double buffered true color window with Z-buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	// Create window
	glutInitWindowSize(800, 500);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Music Box");
	
	init() ;
	//  Enable Z-buffer depth test
	glEnable(GL_DEPTH_TEST);
	// Callback functions
	glutDisplayFunc(display);
	glutKeyboardFunc(normalKeys);
	glutSpecialFunc(specialKeys);
	glutReshapeFunc(resize);
	
	//  Pass control to GLUT for events
	glutMainLoop();
	 
	//  Return to OS
	return 0;

}

void init(void) {
	container.handlecolor_.set(130.0, 130.0, 130.0) ;
	container.frontcolor_.set(180.0, 95.0, 4.0) ;
	container.backcolor_.set(255.0, 255.0, 255.0) ;
	container.topcolor_.set(150.0, 255.0, 169.0) ;
	container.leftcolor_.set(255.0, 0.0, 0.0) ;
	container.rightcolor_.set(0.0, 0.0, 128.0) ;
	container.bottomcolor_.set(127.0, 127.0, 128.0) ;

	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL); /* flat shaded */
	gluQuadricNormals(qobj, GLU_FLAT);
	gluQuadricTexture(qobj, GLU_TRUE);

	container.initialise() ;
	man.initialise() ;
	initLists() ;  
}

void display(){
 
	//  Clear screen and Z-buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_LIGHTING);
 	glPushMatrix() ;
		glTranslatef(16.0f, 10.0f, -18.4f) ;
		drawLights() ;
		//container.drawMe() ;
		glPushMatrix() ;
			glScalef(0.3f, 0.3f, 0.3f) ;
			man.draw() ;
		glPopMatrix() ;
	glPopMatrix() ;
	drawScene() ;
	
	glFlush();
	glutSwapBuffers();
	 
}

void specialKeys( int key, int x, int y ) {
 
	switch (key) {
	  case GLUT_KEY_LEFT : angle -= 0.05f; orientMe(angle);break;
	  case GLUT_KEY_RIGHT : angle +=0.05f; orientMe(angle);break;
	  case GLUT_KEY_UP : moveMeFlat(1);break;
	  case GLUT_KEY_DOWN : moveMeFlat(-1);break;
  	}
	 
	//  Request display update
	glutPostRedisplay();
 
}

void normalKeys(unsigned char key, int x, int y) {
	switch(key) {
		case 27 :
			exit(0) ;
		/** Music Box Lid */
		case 'p' :
			container.openLid(0.5) ; break ;
		case 'P' :
			container.closeLid(0.5) ; break ;
		case 32 :
			glutTimerFunc(1000, timer, 0); break ;

		case 'Z' : case 'z' :
			light1 = !light1 ; break ;
	}	
	glutPostRedisplay();
}

void resize(int w, int h) {
  
	if(h == 0) h = 1;

	float ratio = 1.0f * w / h;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);

	gluPerspective(45, ratio, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, x + lx,y + ly,z + lz, 0.0f, 1.0f, 0.0f);
}

void timer(int v) {
	man.torso_->changeAngleZ(0.5) ; 
	man.chest_->changeAngleZ(0.5) ; 
	glutPostRedisplay();
	glutTimerFunc(1000/FPS, timer, v);
}

void moveMeFlat(float i) {
	x = x + i*(lx)*0.1;
	z = z + i*(lz)*0.1;

	glLoadIdentity();
	gluLookAt(x, y, z, x + lx,y + ly,z + lz, 0.0f,1.0f,0.0f);  
}

void orientMe(float ang) {
	lx = sin(ang);
	lz = -cos(ang);
	glLoadIdentity();
	gluLookAt(x, y, z, x + lx,y + ly,z + lz, 0.0f, 1.0f, 0.0f);
}
		

/*********** DRAWING THE ROOM ******************************/

void drawRoom() {
	
	GLuint brickTexture = loadBitmap("./img/bricks.bmp");
	GLuint stoneTexture = loadBitmap("./img/stones.bmp");
	GLuint floorTexture = loadBitmap("./img/carpet.bmp");
	GLuint roofTexture = loadBitmap("./img/roof.bmp");
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, brickTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); 
	glVertex3f(  20.0f, 0.0f, -20.0f ); 
	glTexCoord2f(0.0f, 1.0f); 
	glVertex3f(  20.0f,  25.0f, -20.0f );
	glTexCoord2f(1.0f, 1.0f); 
	glVertex3f( -20.0f,  25.0f, -20.0f );
	glTexCoord2f(1.0f, 0.0f); 
	glVertex3f( -20.0f, 0.0f, -20.0f );
	glEnd() ;
	
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); 
	glVertex3f(  20.0f, 0.0f, 20.0f ); 
	glTexCoord2f(0.0f, 1.0f); 
	glVertex3f(  20.0f,  25.0f, 20.0f );
	glTexCoord2f(1.0f, 1.0f); 
	glVertex3f( -20.0f,  25.0f, 20.0f );
	glTexCoord2f(1.0f, 0.0f); 
	glVertex3f( -20.0f, 0.0f, 20.0f );
	glEnd() ;

	glBindTexture(GL_TEXTURE_2D, stoneTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); 
	glVertex3f(  20.0f, 0.0f, -20.0f ); 
	glTexCoord2f(1.0f, 1.0f); 
	glVertex3f(  20.0f,  0.0f, 20.0f );
	glTexCoord2f(1.0f, 0.0f); 
	glVertex3f( 20.0f,  25.0f, 20.0f );
	glTexCoord2f(0.0f, 0.0f); 
	glVertex3f( 20.0f, 25.0f, -20.0f );
	glEnd() ;
	
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); 
	glVertex3f( -20.0f, 0.0f, -20.0f ); 
	glTexCoord2f(1.0f, 1.0f); 
	glVertex3f( -20.0f,  0.0f, 20.0f );
	glTexCoord2f(1.0f, 0.0f); 
	glVertex3f( -20.0f,  25.0f, 20.0f );
	glTexCoord2f(0.0f, 0.0f); 
	glVertex3f( -20.0f, 25.0f, -20.0f );
	glEnd() ;
	

	glBindTexture(GL_TEXTURE_2D, floorTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); 
	glVertex3f(  -20.0f, 0.0f, -20.0f ); 
	glTexCoord2f(0.0f, 1.0f); 
	glVertex3f(  -20.0f,  0.0f, 20.0f );
	glTexCoord2f(1.0f, 1.0f); 
	glVertex3f( 20.0f,  0.0f, 20.0f );
	glTexCoord2f(1.0f, 0.0f); 
	glVertex3f( 20.0f, 0.0f, -20.0f );
	glEnd() ;
	
	glBindTexture(GL_TEXTURE_2D, roofTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); 
	glVertex3f(  -20.0f, 25.0f, -20.0f ); 
	glTexCoord2f(0.0f, 1.0f); 
	glVertex3f(  -20.0f,  25.0f, 20.0f );
	glTexCoord2f(1.0f, 1.0f); 
	glVertex3f( 20.0f,  25.0f, 20.0f );
	glTexCoord2f(1.0f, 0.0f); 
	glVertex3f( 20.0f, 25.0f, -20.0f );
	glEnd() ;
	
	glDeleteTextures(1, &stoneTexture);
	glDeleteTextures(1, &brickTexture);
	glDeleteTextures(1, &floorTexture);
	glDeleteTextures(1, &roofTexture);
	glDisable(GL_TEXTURE_2D) ;
	
}
void drawFurniture() {
	GLuint woodTexture = loadBitmap("./img/wood.bmp");

	GLUquadricObj* qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL); /* flat shaded */
	gluQuadricNormals(qobj, GLU_FLAT);
	gluQuadricTexture(qobj, GLU_TRUE);

	
	glDeleteTextures(1, &stoneTexture);
}


void drawLights() {
	
	GLfloat mat_amb_diff[] = { 0.5f, 0.5f, 0.5f, 0.5f };
	GLfloat light_position1[] = { 0.0f, 1.0f, -0.5f, 0.0f };
	GLfloat light_position[] = { 0.0f, 0.0f, 2.4f };
	GLfloat color_white[] = { 0.23f, 0.23f, 0.23f };
	glShadeModel (GL_SMOOTH);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, color_white);
	glLightfv(GL_LIGHT1, GL_AMBIENT, color_white);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, color_white);
	glLightfv(GL_LIGHT1, GL_SPECULAR, color_white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff);
	
	glEnable(GL_LIGHTING);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	if (light1) {
		glEnable(GL_LIGHT1);
	}
	else {
		glDisable(GL_LIGHT1);
	}
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	
}
void drawScene() {
	glCallList(roomList);
}

void initLists() {
	roomList = glGenLists (1);
	glNewList(roomList, GL_COMPILE);
		drawRoom() ;
	glEndList();

}
