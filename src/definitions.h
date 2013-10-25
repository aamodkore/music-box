#ifndef MAIN_DEF_H
#define MAIN_DEF_H

#include <GL/glut.h>
#include "box.hpp"
#include "body.hpp"
#include "point.hpp"

// Global Variables
static float angle=0.0f,ratio;
static float x=0.0f, y=10.8f, z=4.0f;
static float lx=0.0f, ly=-0.2f, lz=-1.0f;

static bool light1 = true ;

static const int FPS = 20;

static GLuint roomList, furnitureList ;


const static point null_point(0.f,0.f,0.f); 
const static point ORIGIN(0.f,0.f,0.f) ;


// Function Prototypes
void display();
void init() ;
void specialKeys(int key, int x, int y);
void normalKeys(unsigned char key, int x, int y) ;
void resize(int w, int h) ;
void timer(int x) ;
void moveMeFlat(float dist) ;
void orientMe(float angle) ;

//Define box appropriately
static box container(0.5,0.0) ;
static body man ;

void initLists() ;
void drawRoom() ;
void drawFurniture() ;
void drawLights() ;
void drawScene() ;

#endif