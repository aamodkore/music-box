#ifndef CURVE_H
#define CURVE_H

#include <cstdlib>
#include <vector>
#include "point.hpp"

class bezierCurve {

	float choose_[50][50] ;
	float powerT_[50] ;
	std::vector <point> points_ ;
	int count_ ;

	private :
		float choose (int n, int i) ;
	public :
		bezierCurve() ;

		void push_back(point p) ;
		void pop_back() ;
		point get(int n) ;
		void reset() ;

		inline int getCount() { return count_ ; }

		point curve(float t) ;
} ;

#endif