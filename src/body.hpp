#ifndef CS475A2_BODY
#define CS475A2_BODY

#include <GL/glut.h>
#include "bodyNode.hpp"


class body {

	GLuint parts_ ;

	public :
		bodyNode *head_, *neck_,  *chest_, *torso_, *hip_, *larm_, *rarm_, *lelbow_, *relbow_, *lhand_, *rhand_, *lthigh_, *rthigh_, *lleg_, *rleg_, *lfoot_, *rfoot_ ;


		body() ;				// Default constructor
								// Initialises all node pointers to null

		void initialise() ;		// Initialises all the nodes and the 
								// display lists for the nodes accordingly
								// and constructs the heirarchical tree

		void draw() ;			// Calls the recursive draw function
								// Starting with the 'hip'

		void reset() ;			// Resets to default position
} ;

#endif