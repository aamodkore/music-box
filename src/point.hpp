#ifndef POINT_H
#define POINT_H

#include <GL/glut.h>

class point {
	public :
		float x, y, z ;

		point() ;
		point(float, float, float) ;

		point operator + (point) ;
		point operator - (point) ;
		point operator * (float) ;
		point operator / (float) ;

		point operator = (point) ;

		bool isnull() ;
		point unit() ;
} ;

const static point null_point(0.f,0.f,0.f); 
const static point ORIGIN(0.f,0.f,0.f) ;

#endif