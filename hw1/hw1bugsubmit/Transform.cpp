// Transform.cpp: implementation of the Transform class.

#include "stdafx.h"
#include "Transform.h"
#include <math.h>

//Takes as input the current eye position, and the current up vector.
//up is always normalized to a length of 1.
//eye has a length indicating the distance from the viewer to the origin

// Helper rotation function.  Please implement this.  

mat3 Transform::rotate(const float degrees, const vec3& axis) {
  mat3 R; 
  
  float degrees_rad = glm::radians(degrees);
  float x = axis[0];
  float y = axis[1];
  float z = axis[2];

  mat3 I = cos(degrees_rad) * mat3(1.0);
  mat3 parallel = (1 - cos(degrees_rad)) * mat3(x*x, x*y, x*z,
	                                            x*y, y*y, y*z,
											    x*z, y*z, z*z);
  mat3 perpendicular = sin(degrees_rad) * mat3(0, -z, y,
	                                           z, 0, -x,
											   -y, x, 0);

  R = I + parallel + perpendicular;
  return R ; 
}

void Transform::left(float degrees, vec3& eye, vec3& up) {

	mat3 R = rotate(degrees, up);
	eye = eye * R;
}

void Transform::up(float degrees, vec3& eye, vec3& up) {
	float magnitude = sqrt(pow(eye.x,2) + pow(eye.y,2) + pow(eye.z,2));
	vec3 axis = glm::cross(eye, up);
	axis = glm::normalize(axis);
	mat3 R = rotate(degrees, axis);
	eye = eye * R;
	eye = glm::normalize(eye) * mat3(magnitude);
	up = up * R;
	up = glm::normalize(up);
}

mat4 Transform::lookAt(const vec3& eye, const vec3& center, const vec3& up) {
    mat4 M ; 
	
	vec3 w = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(up,w));
	vec3 v = glm::cross(w,u);

	vec3 T = -vec3(glm::dot(u,eye), glm::dot(v,eye), glm::dot(w,eye));
	
	M = mat4(u[0], u[1], u[2], T[0],
		     v[0], v[1], v[2], T[1],
			 w[0], w[1], w[2], T[2],
			    0,    0,    0,   1);

	return M ; 
}

Transform::Transform()
{

}

Transform::~Transform()
{

}

// Some notes about using glm functions.
// You are ONLY permitted to use glm::dot glm::cross glm::normalize
// Do not use more advanced glm functions (in particular, directly using 
// glm::lookAt is of course prohibited).  

// You may use overloaded operators for matrix-vector multiplication 
// But BEWARE confusion between opengl (column major) and row major 
// conventions, as well as what glm implements. 
// In particular, vecnew = matrix * vecold may not implement what you think 
// it does.  It treats matrix as column-major, in essence using the transpose.
// We recommend using row-major and vecnew = vecold * matrix 
// Preferrably avoid matrix-matrix multiplication altogether for this hw. 

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar){
	float rads = glm::radians(fovy);
	float d = 1 / (glm::tan(rads/ 2));
	//d *= aspect * 1.083;
	//d = 3/2;
	float A = - (zFar + zNear) / (zFar - zNear);
	float B = - (2 * zNear * zFar) / (zFar - zNear);
	return mat4(d / aspect, 0.0, 0.0, 0.0,
		        0.0, d, 0.0, 0.0,
				0.0, 0.0, A, B,
				0.0, 0.0, -1.0, 0.0);
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz){
	return mat4(sx, 0.0, 0.0, 0.0, 
		        0.0, sy, 0.0, 0.0,
				0.0, 0.0, sz, 0.0,
				0.0, 0.0, 0.0, 1.0);
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz){
	return mat4(1.0, 0.0, 0.0, tx,
		        0.0, 1.0, 0.0, ty,
				0.0, 0.0, 1.0, tz,
				0.0, 0.0, 0.0, 1.0);
}