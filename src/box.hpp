#ifndef CS475A2_BOX
#define CS475A2_BOX

#include <cstdlib>
#include <GL/glut.h>
#include "color.hpp"

class box {
	double side_ ;
	double angle_ ;
	
	GLuint onlyBox ;
	GLuint onlyLid ;
	GLuint handle ;
	
	public :
		
		color_t handlecolor_ ;
		color_t frontcolor_ ;
		color_t backcolor_ ;
		color_t leftcolor_ ;
		color_t rightcolor_ ;
		color_t topcolor_ ;
		color_t bottomcolor_ ;
	
		box(double side, double angle) ;
		void initialise() ;
		
		void drawMe() ;
		void drawLid() ;
		void drawBox() ;
		void drawHandle() ;
		
		void closeLid(double step) ;
		void openLid(double step) ;
		
} ;

#endif
