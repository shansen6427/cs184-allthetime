#include "stdafx.h"
#include "objReader.h"
#include "Transform.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <GL/glew.h>

objReader::objReader(){
}

/**
 *  init opens and parses the obj file "filename".
 * .obj files consist of lines as such:
 * v x y z   // defines vertex
 * vt x y z  // defines texture information
 * vn x y z  // defines normal vector
 * f v/vt/vn ...  // defines a polygon as a series of vertex/texture/vertex normal triplets separated by slashes
 *  init populates class variables vertices and faces with this information (currently ignores texture information)
 */
int
objReader::init(const char* filename){
	std::string str = "" ; 
	
	// open .obj file
	std::cout << "Reading .obj file " << filename << std::endl;
    std::ifstream in ; 
    in.open(filename) ; 
    if (!in.is_open()) {
		std::cerr << "Unable to open file " << filename << "\n" ; 
		return 1 ;
	}

	// parse .obj file
	while(in){
		getline(in, str);

		if(str.empty()){
			// do nothing
		} // read and store vertices
		else if(str[0] == 'v'){
			float x,y,z;
			sscanf(str.c_str(), "v %f %f %f", &x, &y, &z);
			vec3 vertex(x,y,z);
			vertices.push_back(vertex);
		} // read and store faces
		else if(str[0] == 'f'){
			std::vector<int> f;
			int slash_pos, vert;
			std::string buf;
			std::stringstream ss(str) ;
			ss >> buf ;
			while (ss >> buf) {
				slash_pos = buf.find('/');
				buf = buf.substr(0, slash_pos);
				vert = atoi(buf.c_str());
				f.push_back(vert);
			}
			faces.push_back(f);
		}
	}

	std::cout << ".obj file read successful" << std::endl;
	return 0;
}

/**
 * draws the .obj object
 *  Goes through vector faces and specifies each vertex using that information
 *  Color arguments are used directly
 */
void
objReader::draw(const float &red, const float &green, const float &blue, const float &alpha){
	std::vector<int> face;
	vec3 vert;
	vec3 vert1, vert2, vert3;
	vec3 veca, vecb, normal;
	for(unsigned int m = 0; m < faces.size(); m++){
		face = faces[m];
		vert1 = vertices[face[0] - 1];
		vert2 = vertices[face[1] - 1];
		vert3 = vertices[face[2] - 1];

		veca = vec3(vert2.x - vert1.x, vert2.y - vert1.y, vert2.z - vert1.z);
		vecb = vec3(vert3.x - vert1.x, vert3.y - vert1.y, vert3.z - vert1.z);
		normal = glm::normalize(veca * vecb);
		
		glBegin(GL_POLYGON);
			glColor4f(red, green, blue, alpha);
			glNormal3f(normal.x, normal.y, normal.z);
			for(unsigned int n = 0; n < face.size(); n++){
				vert = vertices[face[n] - 1];
				//if(m < 5) std::cout << "vert: (" << vert.x << ", " << vert.y << ", " << vert.z << ")/n";
				glVertex3f(vert.x, vert.y, vert.z);
			}
		glEnd();
	}
}

// centers object
void
objReader::moveToCenter(){
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
objReader::rotate(const float degrees, const vec3& axis)
{
	mat3 R = Transform::rotate(degrees, axis);
	for(unsigned int m = 0; m < vertices.size(); m++){
		vertices[m] = vertices[m] * R;
	}
}

void
objReader::scale(const float &sx, const float &sy, const float &sz){
	vec4 hom_vertice;
	mat4 S = Transform::scale(sx, sy, sz);
	for(unsigned int m = 0; m < vertices.size(); m++){
		hom_vertice = vec4(vertices[m].x, vertices[m].y, vertices[m].z, 1.0);
		hom_vertice = hom_vertice * S;
		vertices[m] = vec3(hom_vertice.x / hom_vertice.w, hom_vertice.y / hom_vertice.w, hom_vertice.z / hom_vertice.w);
	}
}
    
void
objReader::translate(const float &tx, const float &ty, const float &tz){
	vec4 hom_vertice;
	mat4 T = Transform::translate(tx, ty, tz);
	for(unsigned int m = 0; m < vertices.size(); m++){
		hom_vertice = vec4(vertices[m].x, vertices[m].y, vertices[m].z, 1.0);
		hom_vertice = hom_vertice * T;
		vertices[m] = vec3(hom_vertice.x / hom_vertice.w, hom_vertice.y / hom_vertice.w, hom_vertice.z / hom_vertice.w);
	}
}