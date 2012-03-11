// Shapes.cpp: Implementation of Shapes class.

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

Shapes::Shapes()
{
	// 
}

Shapes::~Shapes()
{

}