#include <iostream>
#include <cmath>
#include <algorithm>
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
	glutMouseFunc(mouseClick);
	
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

	flyover.push_back(point(-18.f,10.f,-18.f)) ;
}

void display(){
 
	//  Clear screen and Z-buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_LIGHTING);
 	drawLights() ;
	glPushMatrix() ;
		glTranslatef(px, py, pz) ;
		glPushMatrix() ;
			glScalef(2.f, 2.f, 2.f) ;
			container.drawMe() ;
		glPopMatrix() ;
		glPushMatrix() ;
			glTranslatef(0.f,1.1f,0.f) ;
			glScalef(0.3f, 0.3f, 0.3f) ;
			man.draw() ;
		glPopMatrix() ;
	glPopMatrix() ;
	drawScene() ;

	if (showcurve && compcurve) drawCurve() ;
	if (showpoints) drawPoints() ;

	glFlush();
	glutSwapBuffers();
	 
}

void specialKeys( int key, int x, int y ) {
 	if (!animate) {
		switch (key) {		// Move around
		  case GLUT_KEY_LEFT : angle += 0.05f; orientMe(angle);break;
		  case GLUT_KEY_RIGHT : angle -=0.05f; orientMe(angle);break;
		  case GLUT_KEY_UP : moveMeFlat(1);break;
		  case GLUT_KEY_DOWN : moveMeFlat(-1);break;
	  	}
	}
	glutPostRedisplay();
 
}

void normalKeys(unsigned char key, int x, int y) {
	if (key==27) exit(0) ;
	if (!animate) {
		switch(key) {
			case 32 :		// Begin animation
				anime_step=0 ; animate = true ;
				glutTimerFunc(1000, timer, 0); break ;

			case 'Z' : case 'z' :	// Light 1
				light1 = !light1 ; break ;
			case 'X' : case 'x' :	// Light 2
				light2 = !light2 ; break ;
			case 'D' : case 'd' :	// Delete last entered point
				flyover.pop_back() ; break ;
			case '+' : case '=' :	// Increase click depth
				clickDepth = min(clickDepth+0.2f,10.f) ; break ;
			case '-' : case '_' :	// Decrease click depth
				clickDepth = max(clickDepth-0.2f,1.f) ; break ;
			case 'P' : case 'p' :	// Show/hide points
				showpoints = !showpoints ; break ;
			case 'V' : case 'v' :	// Show/hide points
				showcurve = !showcurve ; break ;
			case 'C' : case 'c' :	// Create/show curve
				computeCurve() ; break ;
			case 'R' : case 'r' :	// Delete all points, reset animation
				compcurve = showcurve = false ;
				flyover.reset() ;
		}	
	}
	glutPostRedisplay();
}

void resize(int w, int h) {
  
	if(h == 0) h = 1;
	height = h; width = w ;
	ratio = 1.0f * w / h;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);

	gluPerspective(45, ratio, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, x + lx,y + ly,z + lz, 0.0f, 1.0f, 0.0f);
}

void timer(int v) {
	if (!compcurve) computeCurve() ;
	showpoints= showcurve = false ;
	if (anime_step < steps) {
		glLoadIdentity();
		gluLookAt(curve[anime_step].x, curve[anime_step].y, curve[anime_step].z, 
			px, py, pz, 0.0f, 1.0f, 0.0f);
		anime_step++ ;
		glutPostRedisplay();
		glutTimerFunc(1000/FPS, timer, v);
	}
	else {
		animate = false ;
		showpoints= showcurve = true ;
	}
}

void moveMeFlat(float i) {
	x = min(max(x + i*(lx)*0.1, -19.0), 19.0);
	z = min(max(z + i*(lz)*0.1, -19.0), 19.0);

	glLoadIdentity();
	gluLookAt(x, y, z, x + lx,y + ly,z + lz, 0.0f,1.0f,0.0f);  
}

void orientMe(float ang) {
	lx = sin(ang);
	lz = cos(ang);
	glLoadIdentity();
	gluLookAt(x, y, z, x + lx,y + ly,z + lz, 0.0f, 1.0f, 0.0f);
}
		

/*********** DRAWING THE ROOM ******************************/

void drawRoom() {
	
	GLuint brickTexture = loadBitmap("./img/bricks.bmp");
	GLuint stoneTexture = loadBitmap("./img/stones.bmp");
	GLuint floorTexture = loadBitmap("./img/carpet.bmp");
	GLuint roofTexture = loadBitmap("./img/roof.bmp");
	GLuint doorTexture = loadBitmap("./img/door.bmp");
	
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
	
	glBindTexture(GL_TEXTURE_2D, doorTexture);
	glPushMatrix() ;
		glTranslatef(-12.5f, 0.f, -19.5f) ;
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); 
		glVertex3f(  -4.0f, 0.0f, -0.0f ); 
		glTexCoord2f(0.0f, 1.0f); 
		glVertex3f(  -4.0f,  19.0f, 0.0f );
		glTexCoord2f(1.0f, 1.0f); 
		glVertex3f( 4.0f,  19.0f, 0.0f );
		glTexCoord2f(1.0f, 0.0f); 
		glVertex3f( 4.0f, 0.0f, -0.0f );
		glEnd() ;
	glPopMatrix() ;
	
	glDeleteTextures(1, &stoneTexture);
	glDeleteTextures(1, &brickTexture);
	glDeleteTextures(1, &floorTexture);
	glDeleteTextures(1, &roofTexture);
	glDeleteTextures(1, &doorTexture);
	glDisable(GL_TEXTURE_2D) ;
	
}

void drawFurniture() {
	GLuint woodTexture = loadBitmap("./img/wood.bmp");
	GLuint marbleTexture = loadBitmap("./img/marble.bmp");

	/* Draw Main Table */
	glPushMatrix() ;
		glTranslatef(15.0f, 0.f, -15.5f) ;

		glPushMatrix() ; glTranslatef( 4.0f, 0.f, 3.6f) ; 
		drawTableLegs(8.0f) ; glPopMatrix() ;
		glPushMatrix() ; glTranslatef(-4.0f, 0.f, 3.6f) ; 
		drawTableLegs(8.0f) ; glPopMatrix() ;
		glPushMatrix() ; glTranslatef( 4.0f, 0.f,-3.6f) ; 
		drawTableLegs(8.0f) ; glPopMatrix() ;
		glPushMatrix() ; glTranslatef(-4.0f, 0.f,-3.6f) ; 
		drawTableLegs(8.0f) ; glPopMatrix() ;

		glBindTexture(GL_TEXTURE_2D, woodTexture);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); 
		glVertex3f(  -4.5, 8.0f, -4.0f ); 
		glTexCoord2f(0.0f, 1.0f); 
		glVertex3f(  -4.5,  8.0f, 4.0f );
		glTexCoord2f(1.0f, 1.0f); 
		glVertex3f( 4.5,  8.0f, 4.0f );
		glTexCoord2f(1.0f, 0.0f); 
		glVertex3f( 4.5, 8.0f, -4.0f );
		glEnd() ;
		glDisable(GL_TEXTURE_2D) ;
	glPopMatrix() ;
	
	/* Draw Small Teapoy */
	glPushMatrix() ;
		glTranslatef(-1.0f, 0.f, 3.5f) ;

		glPushMatrix() ; glTranslatef( 2.7f, 0.f, 2.7f) ; 
		drawTableLegs(4.2f) ; glPopMatrix() ;
		glPushMatrix() ; glTranslatef(-2.7f, 0.f, 2.7f) ; 
		drawTableLegs(4.2f) ; glPopMatrix() ;
		glPushMatrix() ; glTranslatef( 2.7f, 0.f,-2.7f) ; 
		drawTableLegs(4.2f) ; glPopMatrix() ;
		glPushMatrix() ; glTranslatef(-2.7f, 0.f,-2.7f) ; 
		drawTableLegs(4.2f) ; glPopMatrix() ;

		glBindTexture(GL_TEXTURE_2D, marbleTexture);
		glEnable(GL_TEXTURE_2D);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTranslatef(0.f,4.2f,0.f) ;
		glRotatef( 90.0, 1.0, 0.0, 0.0 );
		gluDisk(qobj, 0.0f, 4.f, 40, 5);
		glDisable(GL_TEXTURE_2D) ;
	glPopMatrix() ;
	

	/* Draw Chair */
	glPushMatrix() ;
		glTranslatef(6.0f, 0.f, 5.5f) ;
		glRotatef(-45.0f, 0.f,1.0f, 0.0f) ;

		glPushMatrix() ; glTranslatef( 1.3f, 0.f, 1.3f) ; 
		drawTableLegs(5.f) ; glPopMatrix() ;
		glPushMatrix() ; glTranslatef(-1.3f, 0.f, 1.3f) ; 
		drawTableLegs(5.f) ; glPopMatrix() ;
		glPushMatrix() ; glTranslatef( 1.3f, 0.f,-1.3f) ; 
		drawTableLegs(5.f) ; glPopMatrix() ;
		glPushMatrix() ; glTranslatef(-1.3f, 0.f,-1.3f) ; 
		drawTableLegs(5.f) ; glPopMatrix() ;


		glBindTexture(GL_TEXTURE_2D, woodTexture);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUAD_STRIP);
		glTexCoord2f(0.0f, 0.0f); 
		glVertex3f(  -1.5, 5.f, -1.5f ); 
		glTexCoord2f(0.0f, 1.0f); 
		glVertex3f(  -1.5,  5.f, 1.5f );
		glTexCoord2f(1.0f, 0.0f); 
		glVertex3f( 1.5,  5.f, -1.5f );
		glTexCoord2f(1.0f, 1.0f); 
		glVertex3f( 1.5, 5.f, 1.5f );
		glTexCoord2f(1.0f, 0.0f); 
		glVertex3f( 1.5,  10.0f, -1.5f );
		glTexCoord2f(1.0f, 1.0f); 
		glVertex3f( 1.5, 10.0f, 1.5f );
		glEnd() ;

		glDisable(GL_TEXTURE_2D) ;
	glPopMatrix() ;
	
	glPushMatrix() ;
		glTranslatef(-9.0f, 0.f, 5.5f) ;
		glRotatef(-135.f, 0.f,1.0f, 0.0f) ;

		glPushMatrix() ; glTranslatef( 1.3f, 0.f, 1.3f) ; 
		drawTableLegs(5.f) ; glPopMatrix() ;
		glPushMatrix() ; glTranslatef(-1.3f, 0.f, 1.3f) ; 
		drawTableLegs(5.f) ; glPopMatrix() ;
		glPushMatrix() ; glTranslatef( 1.3f, 0.f,-1.3f) ; 
		drawTableLegs(5.f) ; glPopMatrix() ;
		glPushMatrix() ; glTranslatef(-1.3f, 0.f,-1.3f) ; 
		drawTableLegs(5.f) ; glPopMatrix() ;


		glBindTexture(GL_TEXTURE_2D, woodTexture);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUAD_STRIP);
		glTexCoord2f(0.0f, 0.0f); 
		glVertex3f(  -1.5, 5.f, -1.5f ); 
		glTexCoord2f(0.0f, 1.0f); 
		glVertex3f(  -1.5,  5.f, 1.5f );
		glTexCoord2f(1.0f, 0.0f); 
		glVertex3f( 1.5,  5.f, -1.5f );
		glTexCoord2f(1.0f, 1.0f); 
		glVertex3f( 1.5, 5.f, 1.5f );
		glTexCoord2f(1.0f, 0.0f); 
		glVertex3f( 1.5,  10.0f, -1.5f );
		glTexCoord2f(1.0f, 1.0f); 
		glVertex3f( 1.5, 10.0f, 1.5f );
		glEnd() ;

		glDisable(GL_TEXTURE_2D) ;
	glPopMatrix() ;
	
	glDeleteTextures(1, &woodTexture);
	glDeleteTextures(1, &marbleTexture);
}

void drawTableLegs(float height) {
	GLuint woodTexture = loadBitmap("./img/wood.bmp");

	glPushMatrix() ;
		glTranslatef(0.0f, height, 0.0f) ;
		glRotatef( 90.0, 1.0, 0.0, 0.0 );
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, woodTexture);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		gluCylinder(qobj, 0.15f, 0.15f, height, 15, 5);
		glDisable(GL_TEXTURE_2D) ;
	glPopMatrix() ;
	glDeleteTextures(1, &woodTexture);
}


void drawLights() {
	
	GLfloat mat_amb_diff[] = { 0.5f, 0.5f, 0.5f, 0.5f };
	GLfloat light_position[] = { 0.0f, 1.0f, -0.5f, 0.0f };
	GLfloat light1_position[] = { px, py+5.f, pz+4.4f };
	GLfloat light2_position[] = { -20.f, 20.0f, 0.f };
	GLfloat color_bright[] = { 0.83f, 0.83f, 0.83f };
	GLfloat color_white[] = { 0.23f, 0.23f, 0.23f };
	GLfloat color_yellow[] = { 0.23f, 0.23f, 0.18f };
	GLfloat light1_direction[] = { 0.0f, -1.0f, -0.7f };
	GLfloat light2_direction[] = { 1.0f, -0.4f, 0.f };
	glShadeModel (GL_SMOOTH);

	GLuint metalTexture = loadBitmap("./img/metal.bmp");

	glPushMatrix() ;
	
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, color_white);
	
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	// glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
	// glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.05);
	// glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.01);
	glLightfv(GL_LIGHT1, GL_AMBIENT, color_white);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, color_bright);
	glLightfv(GL_LIGHT1, GL_SPECULAR, color_bright);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_direction);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0);
	
	glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
	// glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 2.5);
	// glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.5);
	glLightfv(GL_LIGHT2, GL_AMBIENT, color_bright);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, color_yellow);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 30.0);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light2_direction);
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff);
	
	glEnable(GL_LIGHTING);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	if (light1) glEnable(GL_LIGHT1);
	else glDisable(GL_LIGHT1);
	if (light2) glEnable(GL_LIGHT2);
	else glDisable(GL_LIGHT2);
	glEnable(GL_LIGHT0);

	
		glBindTexture(GL_TEXTURE_2D, metalTexture);
		glEnable(GL_TEXTURE_2D);
		glColor3f(1.f,1.f,1.f) ;
		glBegin(GL_QUAD_STRIP);
		glTexCoord2f(0.0f, 0.0f); 
		glVertex3f(  -20.f, 22.f, -2.5f ); 
		glTexCoord2f(0.0f, 1.0f); 
		glVertex3f(  -20.f,  19.5f, -2.5f );
		glTexCoord2f(1.0f, 0.0f); 
		glVertex3f( -19.9,  22.f, -2.5f );
		glTexCoord2f(1.0f, 1.0f); 
		glVertex3f( -18.5, 19.5f, -2.5f );
		glTexCoord2f(1.0f, 0.0f); 
		glVertex3f( -19.9,  22.f, 2.5f );
		glTexCoord2f(1.0f, 1.0f); 
		glVertex3f( -18.5, 19.5f, 2.5f );
		glTexCoord2f(0.0f, 0.0f); 
		glVertex3f(  -20.f, 22.f, 2.5f ); 
		glTexCoord2f(0.0f, 1.0f); 
		glVertex3f(  -20.f, 19.5f,2.5f );
		glEnd() ;
		glDisable(GL_TEXTURE_2D);
		glDeleteTextures(1, &metalTexture);
	

	glPopMatrix() ;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	
}
void drawScene() {
	glCallList(roomList);
	glCallList(furnitureList);
}

void initLists() {
	roomList = glGenLists (1);
	glNewList(roomList, GL_COMPILE);
		drawRoom() ;
	glEndList();
	furnitureList = glGenLists (5);
	glNewList(furnitureList, GL_COMPILE);
		drawFurniture() ;
	glEndList();
}


void computeCurve() {
	if (!compcurve) {
		flyover.push_back(point(px,py+4.f,pz+5.f)) ;
		float t = 0.f, gap = 1/((float) steps) ;
		int i ;
		for (i=0; i<steps; t+=gap, i++) {
			curve[i] = flyover.curve(t) ;
		}
	}
	compcurve = showcurve = true ;
}

void drawCurve() {
	int i ;
	glColor3f(1.f,1.f,0.f) ;
	glBegin(GL_LINES) ;
	for (i=0; i<steps; i++) {
		if (i!=0) glVertex3f(curve[i].x, curve[i].y, curve[i].z) ;
		if (i<steps-1) glVertex3f(curve[i].x, curve[i].y, curve[i].z) ;
	}
	glEnd() ;
}
void drawPoints() {
	int i, n=flyover.getCount() ;
	point p ;
	glColor3f(0.15f,1.f,0.f) ;
	for (i=0; i<n; i++) {
		p = flyover.get(i) ;
		glPushMatrix() ;
		glTranslatef(p.x, p.y, p.z) ;
		glutSolidSphere(0.1f,10,10);
		glPopMatrix() ;
		// cout << "Yeaaa me "<< i<< endl ;
	}
}

void mouseClick(int button, int state,int xc, int yc) {
	if (state==GLUT_UP) {
		float xd=2.0f*ratio*tan(pi/8.f)*(xc-width/2)/(float) width ;
		float yd=2.0f*tan(pi/8.f)*(yc-height/2)/(float) height ;
		point curr(x,y,z), strght(lx,ly,lz), 
			vert(0.0f,-1.0f,0.0f), horiz( -1.0f*lz,0.f,lx) ;
		strght.unify() ; horiz.unify() ;

		point aim = vert*yd ; 
		aim += horiz*xd ;
		aim += strght ;
		aim.unify() ;
		aim *= clickDepth ;

		flyover.push_back(aim+curr) ;
		glutPostRedisplay() ;
	}
}
