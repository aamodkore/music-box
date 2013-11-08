#ifndef CS475A2_NODE
#define CS475A2_NODE

#include <cstdlib>
#include <vector>
#include <GL/glut.h>

using namespace std ;

class bodyNode {

	vector<bodyNode*> subNodes_ ;
	double transX_, transY_, transZ_ ;
	double angleX_, angleY_, angleZ_ ;
	
	
	public :
		GLuint displayList_ ;
		double llimitX_, llimitY_, llimitZ_ ;
		double ulimitX_, ulimitY_, ulimitZ_ ;
	
		bodyNode() ;
		bodyNode(double x, double y, double z) ;

		void addNode(bodyNode* node) ;
		void clearSubNodes() ;

		void changeAngleX(double s) ;
		void changeAngleY(double s) ;
		void changeAngleZ(double s) ;

		void draw() ;
		void reset() ;

		int readVec(vector<double>&, int) ;
		void storeVec(vector<double>&) ;

		void store(vector<double>&) ;
		void read(vector<double>&) ;

} ;

#endif