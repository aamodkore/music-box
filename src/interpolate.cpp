#include <vector>
#include <algorithm>

template <class T>
void interpolate(float t, vector<T>& A, vector<T>& B, vector<T>& Res) {
	int n = min(A.size(), B.size()) ;
	Res.resize(n) ;
	for (int i=0; i<n; i++) 
		Res[n] = A[n]*t + B[n]*(1-t) ;
}