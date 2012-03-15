#include "stdafx.h"
#include "rawReader.h"
#include "Transform.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <GL/glew.h>

rawReader::rawReader(){
}

/**
 *  init opens and parses the raw file "filename".
 * .raw files consist of lines as such:
 * f1 f2 f3 f4 f5 f6 f7 f8 f9
 *  These are all floats, where each triplet specifies one vertice of the triangle (to be read as:
 * v1: (f1, f2, f3); v2: (f4, f5, f6); v3: (f7, f8, f9)
 *  init populates class variable vertices with this information
 */
int
rawReader::init(const char* filename){
	std::string str = "" ; 
	
	// open .raw file
	std::cout << "Reading .raw file " << filename << std::endl;
    std::ifstream in ; 
    in.open(filename) ; 
    if (!in.is_open()) {
		std::cerr << "Unable to open file " << filename << "\n" ; 
		return 1 ;
	}

	// parse .raw file
	while(in){
		getline(in, str);

		if(str.empty()){
			// do nothing
		} // read and store vertices
		else{
			float x1,y1,z1;
			float x2,y2,z2;
			float x3,y3,z3;
			sscanf(str.c_str(), "%f %f %f %f %f %f %f %f %f", &x1, &y1, &z1, &x2, &y2, &z2, &x3, &y3, &z3);
			vec3 vertex1(x1,y1,z1);
			vec3 vertex2(x2,y2,z2);
			vec3 vertex3(x3,y3,z3);
			vertices.push_back(vertex1);
			vertices.push_back(vertex2);
			vertices.push_back(vertex3);
		} 
	}

	std::cout << ".raw file read successful" << std::endl;
	return 0;
}

/**
 * draws the .raw object
 *  Goes through vector vertices and draws triangles using sequential triplets of vertices
 *   So the first trinagle will be (vertices[0], vertices[1], vertices[2]) and the
 *  second will be (vertices[3], vertices[4], vertices[5]), etc.
 *  Color arguments used directly
 */
void
rawReader::draw(const float &red, const float &green, const float &blue, const float &alpha){
	vec3 vert1, vert2, vert3;
	vec3 veca, vecb, normal;
	for(unsigned int m = 0; m < vertices.size(); m += 3){
		vert1 = vertices[m];
		vert2 = vertices[m + 1];
		vert3 = vertices[m + 2];

		veca = vec3(vert2.x - vert1.x, vert2.y - vert1.y, vert2.z - vert1.z);
		vecb = vec3(vert3.x - vert1.x, vert3.y - vert1.y, vert3.z - vert1.z);
		normal = glm::normalize(veca * vecb);

		glBegin(GL_TRIANGLES);
			glColor4f(red, green, blue, alpha);
			glNormal3f(normal.x, normal.y, normal.z);
			glVertex3f(vert1.x, vert1.y, vert1.z);
			glVertex3f(vert2.x, vert2.y, vert2.z);
			glVertex3f(vert3.x, vert3.y, vert3.z);
		glEnd();
	}
}

// centers object
void
rawReader::moveToCenter(){
	float x_avg = 0, y_avg = 0, z_avg = 0;
	int num_verts = vertices.size();

	for(int m = 0; m < num_verts; m++){
		x_avg += vertices[m].x;
		y_avg += vertices[m].y;
		z_avg += vertices[m].z;
	}

	x_avg /= num_verts;
	y_avg /= num_verts;
	z_avg /= num_verts;

	//std::cout << "x_avg: " << x_avg << std::endl;
	//std::cout << "y_avg: " << y_avg << std::endl;
	//std::cout << "z_avg: " << z_avg << std::endl;

	for(int m = 0; m < num_verts; m++){
		vertices[m].x -= x_avg;
		vertices[m].y -= y_avg;
		vertices[m].z -= z_avg;
	}
}

void
rawReader::rotate(const float degrees, const vec3& axis)
{
	mat3 R = Transform::rotate(degrees, axis);
	for(unsigned int m = 0; m < vertices.size(); m++){
		vertices[m] = vertices[m] * R;
	}
}

void
rawReader::scale(const float &sx, const float &sy, const float &sz){
	vec4 hom_vertice;
	mat4 S = Transform::scale(sx, sy, sz);
	for(unsigned int m = 0; m < vertices.size(); m++){
		hom_vertice = vec4(vertices[m].x, vertices[m].y, vertices[m].z, 1.0);
		hom_vertice = hom_vertice * S;
		vertices[m] = vec3(hom_vertice.x / hom_vertice.w, hom_vertice.y / hom_vertice.w, hom_vertice.z / hom_vertice.w);
	}
}
    
void
rawReader::translate(const float &tx, const float &ty, const float &tz){
	vec4 hom_vertice;
	mat4 T = Transform::translate(tx, ty, tz);
	for(unsigned int m = 0; m < vertices.size(); m++){
		hom_vertice = vec4(vertices[m].x, vertices[m].y, vertices[m].z, 1.0);
		hom_vertice = hom_vertice * T;
		vertices[m] = vec3(hom_vertice.x / hom_vertice.w, hom_vertice.y / hom_vertice.w, hom_vertice.z / hom_vertice.w);
	}
}