#ifndef BITMAP_H
#define BITMAP_H

#include <iostream>
#include <cstdio>
#include <GL/glut.h>

#include "loadBitmap.h"

using namespace std ;

GLuint loadBitmap(const char * imagepath) {
	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * file = fopen(imagepath,"rb");
	if (!file) {
		cout << "ERROR: loadBitMap: \"" << imagepath << "\": Image could not be opened." << endl ;
		exit(0);
	}

	if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
		cout << "ERROR: loadBitMap: \"" << imagepath << "\": Not a correct BMP file" << endl ;
		exit(0);
	}
	if ( header[0]!='B' || header[1]!='M' ){
		cout << "ERROR: loadBitMap: \"" << imagepath << "\": Not a correct BMP file" << endl ;
		exit(0);
	}

	// Read ints from the byte array
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize==0) imageSize=width*height*3;
	if (dataPos==0) dataPos=54; 

	// Create a buffer
	data = new unsigned char [imageSize];
	
	// Read the actual data from the file into the buffer
	fread(data,1,imageSize,file);
	
	//Everything is in memory now, the file can be closed
	fclose(file);

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);
	
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	
	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	delete data ;

	return textureID ;
}

#endif