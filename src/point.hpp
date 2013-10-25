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

		point operator += (point) ;
		point operator -= (point) ;
		point operator *= (float) ;
		point operator /= (float) ;

		point operator = (point) ;

		bool isnull() ;
		point unit() ;
		point unify() ;
} ;

#endif