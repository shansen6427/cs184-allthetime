#include "objReader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "stdafx.h"
#include <GL/glew.h>
#include <GL/glut.h>

objReader::objReader(){
}

int
objReader::init(const char* filename){
	const char* buffer;
	std::string str = "" ; 
	
	std::cout << "Reading .obj file " << filename << std::endl;
    std::ifstream in ; 
    in.open(filename) ; 
    if (!in.is_open()) {
		std::cerr << "Unable to open file " << filename << "\n" ; 
		return 1 ;
	}

	while(in){
		getline(in, str);

		if(str[0] == 'v'){
			float x,y,z;
			sscanf(str.c_str(), "v %f %f %f", &x, &y, &z);
			vec3 vertice(x,y,z);
			vertices.push_back(vertice);
		}
		if(str[0] == 'f'){
			int v1,v2,v3;
			sscanf(str.c_str(), "f %d %d %d", &v1, &v2, &v3);
			vec3 face(v1, v2, v3);
			faces.push_back(face);
		}
	}

	return 0;
}

void
objReader::draw(){
	vec3 vert1, vert2, vert3;
	for(int n = 0; n < faces.size(); n++){
		vert1 = vertices[faces[n].x - 1];
		vert2 = vertices[faces[n].y - 1];
		vert3 = vertices[faces[n].z - 1];
		glBegin(GL_TRIANGLES);
			glVertex3f(vert1.x, vert1.y, vert1.z);
			glVertex3f(vert2.x, vert2.y, vert2.z);
			glVertex3f(vert3.x, vert3.y, vert3.z);
		glEnd();
	}
}