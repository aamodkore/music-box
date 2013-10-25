#include <GL/glut.h>
#include <cmath>

#include "point.hpp"

point::point() {
	x = y = z = 0.f ;
}
point::point(float xc, float yc, float zc) {
	x = xc; y = yc; z = zc;
}

point point::operator + (point p) {
	point *res = new point (x+p.x, y+p.y, z+p.z) ;
	return *res ;
}
point point::operator - (point p) {
	point *res = new point (x-p.x, y-p.y, z-p.z) ;
	return *res ;
}
point point::operator * (float f) {
	point *res = new point (f*x, f*y, f*z) ;
	return *res ;
}
point point::operator / (float f) {
	point *res = new point (x/f, y/f, z/f) ;
	return *res ;
}

point point::operator = (point p) {
	x = p.x; y = p.y; z = p.z;
	return *this ;
}

bool point::isnull() {
	return (x==0.f && y==0.f && z==0.f) ;
}

point point::unit() {
	point *res ;
	float factor = x*x + y*y + z*z ;
	if (factor==0.f) return *this ;
	else {
		factor = sqrt(factor) ;
		res = new point();
		*res = *this/factor ;
		return * res ;
	}
}
