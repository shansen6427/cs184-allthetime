// Shapes.cpp: Implementation of Shapes class.

#include "stdafx.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <math.h>
#include "Shapes.h"

float pi = 3.14159265f ;

void Shapes::printLetter(char letter, bool inout) {
	if (inout) {
		if (letter == 'e') {
			Shapes::printE() ;
		} else if (letter == 'f') {
			Shapes::printF() ;
		} else if (letter == 'h') {
			Shapes::printH() ;
		} else if (letter == 'l') {
			Shapes::printL() ;
		} else if (letter == 'n') {
			Shapes::printN() ;
		} else if (letter == 'o') {
			Shapes::printOuterO() ;
		} else if (letter == 'r') {
			Shapes::printOuterR() ;
		} else if (letter == 't') {
			Shapes::printT() ;
		} else if (letter == 'u') {
			Shapes::printOuterU() ;
		} else if (letter == 'w') {
			Shapes::printW() ;
		}
	} else {
		if (letter == 'o') {
			Shapes::printInnerO() ;
		} else if (letter == 'r') {
			Shapes::printInnerR() ;
		} else if (letter == 'u') {
			Shapes::printInnerU() ;
		}
	}

}
void Shapes::printE() {
	// Vertical left
	glBegin(GL_QUADS) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		glVertex3f(-0.5, 0.0, -0.5) ;
		glVertex3f(-0.5, 0.0, 0.5) ;
		glVertex3f(-0.3, 0.0, 0.5) ;
		glVertex3f(-0.3, 0.0, -0.5) ;
	glEnd() ;

	// Horizontal bottom
	glBegin(GL_QUADS) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		glVertex3f(-0.3, 0.0, -0.5) ;
		glVertex3f(-0.3, 0.0, -0.3) ;
		glVertex3f(0.5, 0.0, -0.3) ;
		glVertex3f(0.5, 0.0, -0.5) ;
	glEnd() ;

	// Horizontal middle
	glBegin(GL_QUADS) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		glVertex3f(-0.3, 0.0, -0.1) ;
		glVertex3f(-0.3, 0.0, 0.1) ;
		glVertex3f(0.5, 0.0, 0.1) ;
		glVertex3f(0.5, 0.0, -0.1) ;
	glEnd() ;

	// Horizontal top
	glBegin(GL_QUADS) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		glVertex3f(-0.3, 0.0, 0.3) ;
		glVertex3f(-0.3, 0.0, 0.5) ;
		glVertex3f(0.5, 0.0, 0.5) ;
		glVertex3f(0.5, 0.0, 0.3) ;
	glEnd() ;
}

void Shapes::printF() {
	// Vertical left
	glBegin(GL_QUADS) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		glVertex3f(-0.5, 0.0, -0.5) ;
		glVertex3f(-0.5, 0.0, 0.5) ;
		glVertex3f(-0.3, 0.0, 0.5) ;
		glVertex3f(-0.3, 0.0, -0.5) ;
	glEnd() ;

	// Horizontal middle
	glBegin(GL_QUADS) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		glVertex3f(-0.3, 0.0, -0.1) ;
		glVertex3f(-0.3, 0.0, 0.1) ;
		glVertex3f(0.5, 0.0, 0.1) ;
		glVertex3f(0.5, 0.0, -0.1) ;
	glEnd() ;

	// Horizontal top
	glBegin(GL_QUADS) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		glVertex3f(-0.3, 0.0, 0.3) ;
		glVertex3f(-0.3, 0.0, 0.5) ;
		glVertex3f(0.5, 0.0, 0.5) ;
		glVertex3f(0.5, 0.0, 0.3) ;
	glEnd() ;
}

void Shapes::printH() {
	// Vertical left
	glBegin(GL_QUADS) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		glVertex3f(-0.5, 0.0, -0.5) ;
		glVertex3f(-0.5, 0.0, 0.5) ;
		glVertex3f(-0.3, 0.0, 0.5) ;
		glVertex3f(-0.3, 0.0, -0.5) ;
	glEnd() ;

	// Horizontal middle
	glBegin(GL_QUADS) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		glVertex3f(-0.3, 0.0, -0.1) ;
		glVertex3f(-0.3, 0.0, 0.1) ;
		glVertex3f(0.3, 0.0, 0.1) ;
		glVertex3f(0.3, 0.0, -0.1) ;
	glEnd() ;

	// Vertical right
	glBegin(GL_QUADS) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		glVertex3f(0.5, 0.0, -0.5) ;
		glVertex3f(0.5, 0.0, 0.5) ;
		glVertex3f(0.3, 0.0, 0.5) ;
		glVertex3f(0.3, 0.0, -0.5) ;
	glEnd() ;
}

void Shapes::printL() {
	// Vertical left
	glBegin(GL_QUADS) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		glVertex3f(-0.5, 0.0, -0.5) ;
		glVertex3f(-0.5, 0.0, 0.5) ;
		glVertex3f(-0.3, 0.0, 0.5) ;
		glVertex3f(-0.3, 0.0, -0.5) ;
	glEnd() ;

	// Horizontal bottom
	glBegin(GL_QUADS) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		glVertex3f(-0.3, 0.0, -0.5) ;
		glVertex3f(-0.3, 0.0, -0.3) ;
		glVertex3f(0.5, 0.0, -0.3) ;
		glVertex3f(0.5, 0.0, -0.5) ;
	glEnd() ;
}

void Shapes::printN() {
	// Vertical left
	glBegin(GL_QUADS) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		glVertex3f(-0.5, 0.0, -0.5) ;
		glVertex3f(-0.5, 0.0, 0.5) ;
		glVertex3f(-0.3, 0.0, 0.5) ;
		glVertex3f(-0.3, 0.0, -0.5) ;
	glEnd() ;

	// Diagonal TLBR
	glBegin(GL_QUADS) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		glVertex3f(-0.3, 0.0, 0.3) ;
		glVertex3f(-0.3, 0.0, 0.5) ;
		glVertex3f(0.3, 0.0, -0.3) ;
		glVertex3f(0.3, 0.0, -0.5) ;
	glEnd() ;

	// Vertical right
	glBegin(GL_QUADS) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		glVertex3f(0.5, 0.0, -0.5) ;
		glVertex3f(0.5, 0.0, 0.5) ;
		glVertex3f(0.3, 0.0, 0.5) ;
		glVertex3f(0.3, 0.0, -0.5) ;
	glEnd() ;
}

void Shapes::printOuterO() {
	// Circle
	glBegin(GL_POLYGON) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		for (int i = 0; i < 360; i++) {
			float theta = (float) i * pi / 180.0f ;
			glVertex3f(.5 * cos(theta), 0.0, .5 * sin(theta)) ;
		}
	glEnd() ;
}

void Shapes::printInnerO() {
	// Circle
	glBegin(GL_POLYGON) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		for (int i = 0; i < 360; i++) {
			float theta = (float) i * pi / 180.0f ;
			glVertex3f(.3 * cos(theta), -0.01, .3 * sin(theta)) ;
		}
	glEnd() ;
}

void Shapes::printOuterR() {
	// Vertical left
	glBegin(GL_QUADS) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		glVertex3f(-0.4, 0.0, -0.5) ;
		glVertex3f(-0.4, 0.0, 0.5) ;
		glVertex3f(-0.2, 0.0, 0.5) ;
		glVertex3f(-0.2, 0.0, -0.5) ;
	glEnd() ;

	// Semi-circle
	glBegin(GL_POLYGON) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		for (int i = -90; i <= 90; i++) {
			float theta = (float) i * pi / 180.0f ;
			glVertex3f(.3 * cos(theta) + .15, 0, .3 * sin(theta) + .2) ;
		}
	glEnd() ;

	// Horizontal top
	glBegin(GL_QUADS) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		glVertex3f(-0.2, 0.0, 0.3) ;
		glVertex3f(-0.2, 0.0, 0.5) ;
		glVertex3f(.15, 0.0, 0.5) ;
		glVertex3f(.15, 0.0, 0.3) ;
	glEnd() ;

	// Horizontal middle
	glBegin(GL_QUADS) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		glVertex3f(-0.2, 0.0, -0.1) ;
		glVertex3f(-0.2, 0.0, 0.1) ;
		glVertex3f(.15, 0.0, 0.1) ;
		glVertex3f(.15, 0.0, -0.1) ;
	glEnd() ;

	// Vertical right
	glBegin(GL_QUADS) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		glVertex3f(0.4, 0.0, -0.5) ;
		glVertex3f(0.4, 0.0, -0.2) ;
		glVertex3f(0.2, 0.0, -0.2) ;
		glVertex3f(0.2, 0.0, -0.5) ;
	glEnd() ;

	// Quarter-circle
	glBegin(GL_POLYGON) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		glVertex3f(.1, 0, -.2) ;
		for (int i = 0; i < 90; i++) {
			float theta = (float) i * pi / 180.0f ;
			glVertex3f(.3 * cos(theta) + .099, 0, .3 * sin(theta) - .2) ;
		}
	glEnd() ;
}

void Shapes::printInnerR() {
	// Semi-circle
	glBegin(GL_POLYGON) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		for (int i = -90; i <= 90; i++) {
			float theta = (float) i * pi / 180.0f ;
			glVertex3f(.1 * cos(theta) + .15, -0.001, .1 * sin(theta) + .2) ;
		}
	glEnd() ;

	// Quarter-circle
	glBegin(GL_POLYGON) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		glVertex3f(.1, 0, -.2) ;
		for (int i = 0; i <= 90; i++) {
			float theta = (float) i * pi / 180.0f ;
			glVertex3f(.1 * cos(theta) + .1, -0.001, .1 * sin(theta) - .2) ;
		}
	glEnd() ;
}

void Shapes::printT() {
	// Horizontal top
	glBegin(GL_QUADS) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		glVertex3f(-0.5, 0.0, 0.3) ;
		glVertex3f(-0.5, 0.0, 0.5) ;
		glVertex3f(.5, 0.0, 0.5) ;
		glVertex3f(.5, 0.0, 0.3) ;
	glEnd() ;

	// Vertical middle
	glBegin(GL_QUADS) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		glVertex3f(-0.1, 0.0, -0.5) ;
		glVertex3f(-0.1, 0.0, 0.5) ;
		glVertex3f(.1, 0.0, 0.5) ;
		glVertex3f(.1, 0.0, -0.5) ;
	glEnd() ;
}

void Shapes::printOuterU() {
	// Vertical left
	glBegin(GL_QUADS) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		glVertex3f(-0.4, 0.0, -0.1) ;
		glVertex3f(-0.2, 0.0, -0.1) ;
		glVertex3f(-0.2, 0.0, 0.5) ;
		glVertex3f(-0.4, 0.0, 0.5) ;
	glEnd() ;

	// Vertical right
	glBegin(GL_QUADS) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		glVertex3f(0.4, 0.0, -0.1) ;
		glVertex3f(0.2, 0.0, -0.1) ;
		glVertex3f(0.2, 0.0, 0.5) ;
		glVertex3f(0.4, 0.0, 0.5) ;
	glEnd() ;

	// Semi-circle
	glBegin(GL_POLYGON) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		for (int i = -180; i <= 0; i++) {
			float theta = (float) i * pi / 180.0f ;
			glVertex3f(.4 * cos(theta), 0, .4 * sin(theta) - 0.1) ;
		}
	glEnd() ;

}

void Shapes::printInnerU() {
	// Semi-circle
	glBegin(GL_POLYGON) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		for (int i = -180; i <= 0; i++) {
			float theta = (float) i * pi / 180.0f ;
			glVertex3f(.2 * cos(theta), -0.001, .2 * sin(theta) - 0.1) ;
		}
	glEnd() ;
}

void Shapes::printW() {
	// Diagonal TLBR
	glBegin(GL_QUADS) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		glVertex3f(-0.5, 0.0, 0.5) ;
		glVertex3f(-0.3, 0.0, 0.5) ;
		glVertex3f(-0.2, 0.0, -0.5) ;
		glVertex3f(-0.4, 0.0, -0.5) ;
	glEnd() ;

	// Diagonal BLTR
	glBegin(GL_QUADS) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		glVertex3f(-0.4, 0.0, -0.5) ;
		glVertex3f(-0.2, 0.0, -0.5) ;
		glVertex3f(0.0, 0.0, -0.2) ;
		glVertex3f(0.0, 0.0, 0.1) ;
	glEnd() ;

	// Diagonal TLBR
	glBegin(GL_QUADS) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		glVertex3f(0.4, 0.0, -0.5) ;
		glVertex3f(0.2, 0.0, -0.5) ;
		glVertex3f(0.0, 0.0, -0.2) ;
		glVertex3f(0.0, 0.0, 0.1) ;
	glEnd() ;

	// Diagonal BLTR
	glBegin(GL_QUADS) ;
		glNormal3f(0.0, -1.0, 0.0) ; // for shading
		glVertex3f(0.5, 0.0, 0.5) ;
		glVertex3f(0.3, 0.0, 0.5) ;
		glVertex3f(0.2, 0.0, -0.5) ;
		glVertex3f(0.4, 0.0, -0.5) ;
	glEnd() ;
}

void Shapes::cube(float size) {
	float len = size / 2 ;
	glBegin(GL_QUADS) ;
		// Top
		glNormal3f(0.0, 0.0, 1.0) ; 
		glTexCoord2f(0.0f, 0.0f) ; glVertex3f(-len, -len,  len) ;
		glNormal3f(0.0, 0.0, 1.0) ; 
		glTexCoord2f(1.0f, 0.0f) ; glVertex3f( len, -len,  len) ;
		glNormal3f(0.0, 0.0, 1.0) ; 
		glTexCoord2f(1.0f, 1.0f) ; glVertex3f( len,  len,  len) ;
		glNormal3f(0.0, 0.0, 1.0) ; 
		glTexCoord2f(0.0f, 1.0f) ; glVertex3f(-len,  len,  len) ;

		// Bottom
		glNormal3f(0.0, 0.0, -1.0) ; 
		glTexCoord2f(0.0f, 0.0f) ; glVertex3f(-len, -len,  -len) ;
		glNormal3f(0.0, 0.0, -1.0) ; 
		glTexCoord2f(1.0f, 0.0f) ; glVertex3f( len, -len,  -len) ;
		glNormal3f(0.0, 0.0, -1.0) ; 
		glTexCoord2f(1.0f, 1.0f) ; glVertex3f( len,  len,  -len) ;
		glNormal3f(0.0, 0.0, -1.0) ; 
		glTexCoord2f(0.0f, 1.0f) ; glVertex3f(-len,  len,  -len) ;

		// Front
		glNormal3f(0.0, -1.0, 0.0) ; 
		glTexCoord2f(0.0f, 0.0f) ; glVertex3f(-len, -len,  -len) ;
		glNormal3f(0.0, -1.0, 0.0) ; 
		glTexCoord2f(1.0f, 0.0f) ; glVertex3f( len, -len,  -len) ;
		glNormal3f(0.0, -1.0, 0.0) ; 
		glTexCoord2f(1.0f, 1.0f) ; glVertex3f( len, -len,  len) ;
		glNormal3f(0.0, -1.0, 0.0) ; 
		glTexCoord2f(0.0f, 1.0f) ; glVertex3f(-len, -len,  len) ;

		// Back
		glNormal3f(0.0, 1.0, 0.0) ; 
		glTexCoord2f(0.0f, 0.0f) ; glVertex3f(-len, len,  -len) ;
		glNormal3f(0.0, 1.0, 0.0) ; 
		glTexCoord2f(1.0f, 0.0f) ; glVertex3f( len, len,  -len) ;
		glNormal3f(0.0, 1.0, 0.0) ; 
		glTexCoord2f(1.0f, 1.0f) ; glVertex3f( len, len,  len) ;
		glNormal3f(0.0, 1.0, 0.0) ; 
		glTexCoord2f(0.0f, 1.0f) ; glVertex3f(-len, len,  len) ;

		// Side
		glNormal3f(-1.0, 0.0, 0.0) ; 
		glTexCoord2f(0.0f, 0.0f) ; glVertex3f(-len, -len,  -len) ;
		glNormal3f(-1.0, 0.0, 0.0) ; 
		glTexCoord2f(1.0f, 0.0f) ; glVertex3f(-len, len,  -len) ;
		glNormal3f(-1.0, 0.0, 0.0) ; 
		glTexCoord2f(1.0f, 1.0f) ; glVertex3f(-len, len,  len) ;
		glNormal3f(-1.0, 0.0, 0.0) ; 
		glTexCoord2f(0.0f, 1.0f) ; glVertex3f(-len, -len,  len) ;

		// Side
		glNormal3f(1.0, 0.0, 0.0) ; 
		glTexCoord2f(0.0f, 0.0f) ; glVertex3f(len, -len,  -len) ;
		glNormal3f(1.0, 0.0, 0.0) ; 
		glTexCoord2f(1.0f, 0.0f) ; glVertex3f(len, len,  -len) ;
		glNormal3f(1.0, 0.0, 0.0) ; 
		glTexCoord2f(1.0f, 1.0f) ; glVertex3f(len, len,  len) ;
		glNormal3f(1.0, 0.0, 0.0) ; 
		glTexCoord2f(0.0f, 1.0f) ; glVertex3f(len, -len,  len) ;

	glEnd() ;
}

void Shapes::plane(float length, float width, int orientation) {
	float repeat_factor = 10.0f ; // For floor and ceiling
	float dir = 0.0f ;
	glBegin(GL_QUADS) ;
		// 1 up, 2 down, 3 front, 4 back, 5 right, 6 left
		float xcoord, ycoord, zcoord ;
		if (orientation == 1) {
			xcoord = length / 2 ;
			ycoord = width / 2 ;
			zcoord = 0.0f ;
			dir = 1.0f ;
		} else if (orientation == 2) {
			xcoord = -length / 2 ;
			ycoord = width / 2 ;
			zcoord = 0.0f ;
			dir = -1.0f ;
		} else if (orientation == 3) {
			xcoord = length / 2 ;
			ycoord = 0.0f ;
			zcoord = width / 2 ;
			dir = -1.0f ;
		} else if (orientation == 4) {
			xcoord = -length / 2 ;
			ycoord = 0.0f ;
			zcoord = width / 2 ;
			dir = 1.0f ;
		} else if (orientation == 5) {
			xcoord = 0.0f ;
			ycoord = length / 2 ;
			zcoord = width / 2 ;
			dir = 1.0f ;
		} else if (orientation == 6) {
			xcoord = 0.0f ;
			ycoord = -length / 2 ;
			zcoord = width / 2 ;
			dir = -1.0f ;
		}
		if (zcoord == 0.0f) {
			glNormal3f(0.0f, 0.0f, dir) ;
			glTexCoord2f(0.0f, 0.0f) ; glVertex3f(-xcoord, ycoord, 0.0f) ;
			glNormal3f(0.0f, 0.0f, dir) ;
			glTexCoord2f(repeat_factor, 0.0f) ; glVertex3f(xcoord, ycoord, 0.0f) ;
			glNormal3f(0.0f, 0.0f, dir) ;
			glTexCoord2f(repeat_factor, repeat_factor) ; glVertex3f(xcoord, -ycoord, 0.0f) ;
			glNormal3f(0.0f, 0.0f, dir) ;
			glTexCoord2f(0.0f, repeat_factor) ; glVertex3f(-xcoord, -ycoord, 0.0f) ;
		} else if (ycoord == 0.0f) {
			glNormal3f(0.0f, dir, 0.0f) ;
			glTexCoord2f(0.0f, 0.0f) ; glVertex3f(-xcoord, 0.0f, zcoord) ;
			glNormal3f(0.0f, dir, 0.0f) ;
			glTexCoord2f(1.0f, 0.0f) ; glVertex3f(xcoord, 0.0f, zcoord) ;
			glNormal3f(0.0f, dir, 0.0f) ;
			glTexCoord2f(1.0f, 1.0f) ; glVertex3f(xcoord, 0.0f, -zcoord) ;
			glNormal3f(0.0f, dir, 0.0f) ;
			glTexCoord2f(0.0f, 1.0f) ; glVertex3f(-xcoord, 0.0f, -zcoord) ;
		} else if (xcoord == 0.0f) {
			glNormal3f(dir, 0.0f, 0.0f) ;
			glTexCoord2f(0.0f, 0.0f) ; glVertex3f(0.0f, -ycoord, zcoord) ;
			glNormal3f(dir, 0.0f, 0.0f) ;
			glTexCoord2f(1.0f, 0.0f) ; glVertex3f(0.0f, ycoord, zcoord) ;
			glNormal3f(dir, 0.0f, 0.0f) ;
			glTexCoord2f(1.0f, 1.0f) ; glVertex3f(0.0f, ycoord, -zcoord) ;
			glNormal3f(dir, 0.0f, 0.0f) ;
			glTexCoord2f(0.0f, 1.0f) ; glVertex3f(0.0f, -ycoord, -zcoord) ;
		}
	glEnd() ;
}

void Shapes::banister(float bot_height, float top_height, float length, float thickness) {
	float slope = (top_height - bot_height) / -length ;
	float y = 0.0f ; // Parallel to y-axis by construction
	float x, z ;
	if (slope == 0.0f) {
		x = 0.0f ;
		z = 1.0f ;
	} else {
		float recip = - 1 / slope ;
		float mag = sqrt(pow(recip, 2) + 1.0f) ;
		x = 1 / mag ;
		z = recip / mag ;
	}
	float bh = bot_height ;
	float th = top_height ;
	float l = length / 2 ;
	float t = thickness / 2 ;
	
	glBegin(GL_QUADS) ;
		// Front side
		glNormal3f(0.0f, -1.0f, 0.0f) ;
		glVertex3f(-l, -t, 0.0f) ;
		glNormal3f(0.0f, -1.0f, 0.0f) ;
		glVertex3f(l, -t, 0.0f) ;
		glNormal3f(0.0f, -1.0f, 0.0f) ;
		glVertex3f(l, -t, bh) ;
		glNormal3f(0.0f, -1.0f, 0.0f) ;
		glVertex3f(-l, -t, th) ;
	
		// Back side
		glNormal3f(0.0f, 1.0f, 0.0f) ;
		glVertex3f(-l, t, 0.0f) ;
		glNormal3f(0.0f, 1.0f, 0.0f) ;
		glVertex3f(l, t, 0.0f) ;
		glNormal3f(0.0f, 1.0f, 0.0f) ;
		glVertex3f(l, t, bh) ;
		glNormal3f(0.0f, 1.0f, 0.0f) ;
		glVertex3f(-l, t, th) ;

		// Right strip
		glNormal3f(1.0f, 0.0f, 0.0f) ;
		glVertex3f(l, -t, 0.0f) ;
		glNormal3f(1.0f, 0.0f, 0.0f) ;
		glVertex3f(l, t, 0.0f) ;
		glNormal3f(1.0f, 0.0f, 0.0f) ;
		glVertex3f(l, t, bh) ;
		glNormal3f(1.0f, 0.0f, 0.0f) ;
		glVertex3f(l, -t, bh) ;

		// Top strip
		glNormal3f(x, y, z) ;
		glVertex3f(l, -t, bh) ;
		glNormal3f(x, y, z) ;
		glVertex3f(l, t, bh) ;
		glNormal3f(x, y, z) ;
		glVertex3f(-l, t, th) ;
		glNormal3f(x, y, z) ;
		glVertex3f(-l, -t, th) ;

		// Back strip
		glNormal3f(-1.0f, 0.0f, 0.0f) ;
		glVertex3f(-l, -t, 0.0f) ;
		glNormal3f(-1.0f, 0.0f, 0.0f) ;
		glVertex3f(-l, t, 0.0f) ;
		glNormal3f(-1.0f, 0.0f, 0.0f) ;
		glVertex3f(-l, t, th) ;
		glNormal3f(-1.0f, 0.0f, 0.0f) ;
		glVertex3f(-l, -t, th) ;

	glEnd() ;

}

Shapes::Shapes()
{

}

Shapes::~Shapes()
{

}