#ifndef MAIN_DEF_H
#define MAIN_DEF_H

#include <GL/glut.h>
#include "box.hpp"
#include "body.hpp"
#include "point.hpp"
#include "bezierCurve.hpp"

// Global Variables
static float clickDepth=5.0f;
static float x=-16.0f, y=10.8f, z=16.0f;
static float lx=1.2f, ly=0.f, lz=-1.0f;
static float px=16.0f, py=9.0f, pz=-18.4f;
static float ratio, pi=3.14159f;
static float angle=pi+atan(lx/lz); 
static int height,width;
static int anime_step = 0 ;
static const int steps = 100 ;
static const int FPS = 20;

static bool light1=true, light2=true ;
static bool showcurve=false, showpoints=true;
static bool compcurve=false, animate=false ;

static GLuint roomList, furnitureList ;

GLUquadricObj* qobj ;

const static point null_point(0.f,0.f,0.f); 
const static point ORIGIN(0.f,0.f,0.f) ;

static point curve[steps+1] ;

// Function Prototypes
void display();
void init() ;
void specialKeys(int key, int x, int y);
void normalKeys(unsigned char key, int x, int y) ;
void mouseClick(int button, int state,int x, int y);
void resize(int w, int h) ;
void timer(int x) ;
void moveMeFlat(float dist) ;
void orientMe(float angle) ;

//Define box appropriately
static box container(0.5,100.0) ;
static body man ;
static bezierCurve flyover ;

void initLists() ;
void drawRoom() ;
void drawTableLegs(float height) ;
void drawFurniture() ;
void drawLights() ;
void drawScene() ;

void computeCurve() ;
void drawCurve() ;
void drawPoints() ;

#endif