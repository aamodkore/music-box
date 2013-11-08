#ifndef MAIN_DEF_H
#define MAIN_DEF_H

#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>

#include "box.hpp"
#include "body.hpp"
#include "point.hpp"
#include "bezierCurve.hpp"

// Global Variables
static float clickDepth=5.0f;
static float x=-16.0f, y=10.8f, z=16.0f;
static float lx=1.2f, ly=0.f, lz=-1.0f;
static float px=16.0f, py=9.0f, pz=-17.0f;
static float ratio, pi=3.14159f;
static float angle=pi+atan(lx/lz); 
static int height,width;
static int anime_step = 0 ;
static const int steps = 100, rec_steps = 100 ;
static const int FPS = 20;
static const int SPACE_LIMIT = 200000;

unsigned char* pRGB ;
vector<double> keyframe ;
vector<double> prev_keyframe, res_keyframe ;

static bool light1=true, light2=true ;
static bool showcurve=false, showpoints=true;
static bool compcurve=false, animate=false;
static bool dance=false, imagedump=true;

static GLuint roomList, furnitureList ;

GLUquadricObj* qobj ;
/* Animation parameter*/
static int curr_l1, curr_l2, prev_l1, prev_l2 ;
static double curr_angle, prev_angle ;

const static point null_point(0.f,0.f,0.f); 
const static point ORIGIN(0.f,0.f,0.f) ;

static point curve[steps+1] ;

//Global filestreams
static ofstream fout ;
static ifstream fin ;

static ifstream* pfin ;


// Function Prototypes
void display();
void init() ;
void reset() ;
void specialKeys(int key, int x, int y);
void normalKeys(unsigned char key, int x, int y) ;
void mouseClick(int button, int state,int x, int y);
void resize(int w, int h) ;
void timer(int v) ; 
void record(int v) ;
void moveMeFlat(float dist) ;
void moveMeHigh(float dist) ;
void orientMe(float angle) ;

void store_keyframe() ;
void capture_frame(unsigned int) ;
void begin_interpolation() ;

static bodyNode* focus=NULL ;
static box container(0.5,0.f) ;
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