#include <iostream>
#include <vector>
#include <algorithm>
#include "interpolate.h"

using namespace std ;

void interpolate(double t, vector<double>& A, vector<double>& B, vector<double>& Res) {
	int n = min(A.size(), B.size()) ;
	Res.resize(n) ;
	for (int i=0; i<n; i++) 
		Res[n] = A[n]*t + B[n]*(1-t) ;
}

void readFrom (istream& is, vector<double>& vec) {
	int n ; is >> n ;
	vec.resize(n) ;
	for (int i=0; i<n; i++) {
		is >> vec[i] ;
	}
}

void printTo (ostream& os, vector<double>& vec) {
	int n = vec.size();
	os << n << endl ;
	for (int i=0; i<n; i++) {
		os << vec[i] << endl ;
	}
}