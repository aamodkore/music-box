#include <vector>

#include "point.hpp"
#include "bezierCurve.hpp"

float bezierCurve::choose (int n, int i) {
	if (choose_[n][i]<0) {
		if (i==0) choose_[n][i] = 1.f ;
		else if (i>n/2) choose_[n][i] = choose(n,n-i) ;
		else choose_[n][i] = choose(n-1,i-1)+choose(n-1,i) ;
	}
	return choose_[n][i] ;
}

bezierCurve::bezierCurve() {
	points_.clear() ;
	count_ = 0 ;
	for (int i=0; i<50; i++) for (int j=0; j<=i; j++) choose_[i][j]=-1 ;
}

void bezierCurve::push_back(point p) {
	if (count_<50) {
		count_++ ;
		points_.push_back(p) ;
	}
}

void bezierCurve::pop_back() {
	if (count_>0) {
		count_-- ;
		points_.pop_back() ;
	}
}

point bezierCurve::get(int n) {
	return points_[n%count_] ;
}

point bezierCurve::curve(float t) {
	if (t<=0.f) return points_[0] ;
	else if (t>=1.f) return points_[count_-1] ;

	else {
		float s = 1.f - t ;
		int n = count_-1 ;
		point *res = new point() ;

		powerT_[0] = 1.f ;
		for (int i=1; i<count_; i++) 
			powerT_[i] = t*powerT_[i-1] ;
		s = s/t ;
		for (int i=n-1; i>=0; i--) 
			powerT_[i] = s*powerT_[i+1] ;

		for (int i=0; i<count_; i++) 
			*res += (points_[i])*(powerT_[i]*choose(n,i)) ;
		
		return *res ;
	}
}

void bezierCurve::reset() {
	points_.clear() ;
	count_ = 0 ;
}

