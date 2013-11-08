****************** *******************  ******************* *******************

CS 475 Computer Graphics
Assignment 2 Part 3

110050004	Aamod Kore

****************** *******************  ******************* *******************


The code files are in the 'src' folder. Images for texture are in 'img' folder.

To compile run 'make' (See Makefile). Executable is formed in 'bin' folder.

(Uses OpenGL and GLUT, freeglut-3 needs to be installed)

****************** *******************  ******************* *******************


HTML Report and Key Functionality Doc:
http://www.cse.iitb.ac.in/~aamod/cs475/assignment2_2/

Most Updated Code : 
Github Repo: https://github.com/aamodkore/music-box


****************** *******************  ******************* *******************

Keyboard Bindings (refer report: 
		http://www.cse.iitb.ac.in/~aamod/cs475/assignment2_3/)


By default, saving frames to images is enabled. This causes the animation to be 
quite slow. The frame saving can be disabled/enabled using the 'B' key. Also it 
is better to keep SWAP memory off ("sudo swapoff -a")

The image frames are saved in the 'data' folder. 
To create a video out off the images run these commands in the 'data' folder:

	mogrify -flip -format jpg frame_*.ppm
	avconv -r 24 -s svga -f image2 -i './frame_%05d.jpg' ./movie.avi

****************** *******************  ******************* *******************


References :

GLUT Tutorial: http://www.lighthouse3d.com/tutorials/glut-tutorial/
How to Make a Cube in OpenGL: http://www.wikihow.com/Make-a-Cube-in-OpenGL
OpenGL Examples: http://cs.lmu.edu/~ray/notes/openglexamples/
OpenGL Programming Guide: http://www.glprogramming.com/red/
OpenGL Materials and Lighting: http://www.swiftless.com/tutorials/opengl/material_lighting.html
Textures OpenGL: http://cse.csusb.edu/tong/courses/cs520/notes/texture.php
OpenGL Tutorials: http://www.opengl-tutorial.org/beginners-tutorials/


****************** *******************  ******************* *******************

