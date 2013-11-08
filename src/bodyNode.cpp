#include <vector>
#include <iostream>
#include <GL/glut.h>
#include "bodyNode.hpp"

using namespace std ;

bodyNode::bodyNode() {
	displayList_  = glGenLists (1);
	llimitX_ = llimitY_ = llimitZ_ = -180.0 ;
	ulimitX_ = ulimitY_ = ulimitZ_ = 180.0 ;
	transX_ = transY_ = transZ_ =
		angleX_ = angleY_ = angleZ_ = 0.0 ;
}

bodyNode::bodyNode(double x, double y, double z) {
	displayList_  = glGenLists (1);
	transX_ = x ;
	transY_ = y ;
	transZ_ = z ;
	llimitX_ = llimitY_ = llimitZ_ = -180.0 ;
	ulimitX_ = ulimitY_ = ulimitZ_ = 180.0 ;
	angleX_ = angleY_ = angleZ_ = 0.0 ;
}


void bodyNode::addNode(bodyNode* node) {
	subNodes_.push_back(node) ;
}
void bodyNode::clearSubNodes() {
	subNodes_.clear() ;
}

void bodyNode::changeAngleX(double s) {
	double a = angleX_ + s;
	if (a>=llimitX_ && a<=ulimitX_)
		angleX_ = a;
}

void bodyNode::changeAngleY(double s) {
	double a = angleY_ + s;
	if (a>=llimitY_ && a<=ulimitY_)
		angleY_ = a;
}

void bodyNode::changeAngleZ(double s) {
	double a = angleZ_ + s;
	if (a>=llimitZ_ && a<=ulimitZ_)
		angleZ_ = a;
}

void bodyNode::draw() {
	glPushMatrix() ;
		glTranslatef(transX_,transY_,transZ_) ;
		glRotatef( angleZ_, 0.0, 0.0, 1.0 );
		glRotatef( angleX_, 1.0, 0.0, 0.0 );
		glRotatef( angleY_, 0.0, 1.0, 0.0 );
		glCallList(displayList_);
		for (int i=0; i<subNodes_.size(); i++) 
			if (subNodes_[i] != NULL )
				subNodes_[i]->draw() ;
	glPopMatrix() ;
}

void bodyNode::storeVec(vector<double>& v) {
	v.push_back(angleX_); v.push_back(angleY_); v.push_back(angleZ_);
	for (int i=0; i<subNodes_.size(); i++) 
		subNodes_[i]->storeVec(v) ;
}

void bodyNode::store(vector<double>& v) {
	v.clear() ; storeVec(v) ;
}

void bodyNode::read(vector<double>& v) {
	readVec(v,0) ;
}

int bodyNode::readVec(vector<double>& v, int index) {
	if (index<0 || index+3>v.size()) {cout << "sfdgdhtyt " << index << " " << v.size()<< endl;return -1 ;}
	angleX_ = v[index] ; index++ ;
	angleY_ = v[index] ; index++ ;
	angleZ_ = v[index] ; index++ ;
	for (int i=0; i<subNodes_.size(); i++) {
		index = subNodes_[i]->readVec(v,index) ;
	}
	return index ;
}

void bodyNode::reset() {
	angleX_ = angleY_ = angleZ_ = 0 ;
	for (int i=0; i<subNodes_.size(); i++) 
		subNodes_[i]->reset() ;
}

