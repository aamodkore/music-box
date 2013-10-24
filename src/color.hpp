#ifndef COLOR_T
#define COLOR_T

#include <cstdlib>
#include <cmath>
#include <GL/glut.h>

class color_t {
	public:
		double red ;
		double blue ;
		double green ;
		
		color_t() {
			red = 0.0 ;
			blue = 0.0 ;
			green = 0.0 ;
		}
		
		color_t(double r, double g, double b) {
			red = r/255.0 ;
			blue = g/255.0 ;
			green = b/255.0 ;
		}
		
		void set(double r, double g, double b) {
			red = r/255.0 ;
			blue = g/255.0 ;
			green = b/255.0 ;
		}
		
		color_t gradientUp() {
			return color_t (red*255.0+(1.0-red)*102.0 , 
							green*255.0+(1.0-green)*102.0 , 
							blue*255.0+(1.0-blue)*102.0 ) ;
		}
		
		color_t gradientDown() {
			return color_t (red*153 , green*153 , blue*153 ) ;
		}
		
		void color() {
			glColor3f(red,blue,green) ;
		}
} ;

#endif
