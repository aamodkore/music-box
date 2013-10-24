#include <cstdlib>
#include <cmath>
#include <GL/glut.h>

#include "box.hpp"
#include "body.hpp"

// Function Prototypes
void display();
void init() ;
void specialKeys(int key, int x, int y);
void normalKeys(unsigned char key, int x, int y) ;
void resize(int w, int h) ;
void timer(int x) ;
void moveMeFlat(float dist) ;
void orientMe(float angle) ;

// Global Variables
static float angle=0.0f,ratio;
static float x=0.0f, y=0.8f, z=4.0f;
static float lx=0.0f, ly=-0.2f, lz=-1.0f;

static bool light1 = true ;

static const int FPS = 20;


//Define box appropriately
box container(0.5,0.0) ;
body man ;

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
	container.initialise() ;
	man.initialise() ;
}

void display(){
 
	//  Clear screen and Z-buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 0.0f, 1.0f, 1.0f, 0.0f };
	glShadeModel (GL_SMOOTH);

	// glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	
	glEnable(GL_LIGHTING);
	if (light1) glEnable(GL_LIGHT0);
	else glDisable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	//container.drawMe() ;
	glPushMatrix() ;
		glScalef(0.18f, 0.18f, 0.18f) ;
		man.draw() ;
	glPopMatrix() ;
	
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
		
