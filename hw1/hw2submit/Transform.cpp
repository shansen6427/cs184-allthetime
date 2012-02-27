// Transform.cpp: implementation of the Transform class.

#include "stdafx.h"
#include "Transform.h"

//Takes as input the current eye position, and the current up vector.
//up is always normalized to a length of 1.
//eye has a length indicating the distance from the viewer to the origin

// Helper rotation function.  Please implement this.  

mat3 Transform::rotate(const float degrees, const vec3& axis) {
	mat3 R ; 
	float theta = degrees * pi / 180.0f ;
	vec3 normAxis = glm::normalize(axis) ;
	float x = normAxis[0] ;
	float y = normAxis[1] ;
	float z = normAxis[2] ;
	R = cos(theta) * mat3(1.0f) 
		+ (1 - cos(theta)) * mat3(pow(x, 2), x * y, x * z, x * y, pow(y, 2), y * z, x * z, y * z, pow(z, 2))
		+ sin(theta) * mat3(0.0f, -z, y, z, 0.0f, -x, -y, x, 0.0f) ;
	return R ; 
}

void Transform::left(float degrees, vec3& eye, vec3& up) {
	mat3 rotation = rotate(degrees, up) ;
	float magnitude = sqrt(pow(eye[0], 2) + pow(eye[1], 2) + pow(eye[2], 2)) ;
	eye = eye * rotation ;
}

void Transform::up(float degrees, vec3& eye, vec3& center, vec3& up) {
	vec3 crossVector = glm::cross(eye - center, up) ;
	mat3 rotation = rotate(degrees, crossVector) ;
	eye = eye * rotation ;
	up = up * rotation ;
}

mat4 Transform::lookAt(const vec3& eye, const vec3& center, const vec3& up) {
    mat4 M ; 
	vec3 T = -eye ;
	vec3 w(glm::normalize(eye - center)) ;
	vec3 u(glm::normalize(glm::cross(up, w)));
	vec3 v(glm::cross(w, u)) ;
	mat3 R = mat3(u, v, w) ;
	vec3 RT = T * R ;
	M = mat4(vec4(u, RT[0]), vec4(v, RT[1]), vec4(w, RT[2]), vec4(0.0, 0.0, 0.0, 1.0)) ;
	return M ; 
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar) {
	mat4 M ;
	float theta = fovy / 2 ;
	float dist = 1 / glm::tan(glm::radians(theta)) ;
	float A = - (zFar + zNear) / (zFar - zNear) ;
	float B = (-2 * zFar * zNear) / (zFar - zNear) ;
	vec4 a(dist / aspect, 0.0, 0.0, 0.0) ;
	vec4 b(0.0, dist, 0.0, 0.0) ;
	vec4 c(0.0, 0.0, A, B) ;
	vec4 d(0.0, 0.0, -1.0, 0.0) ;
	M = mat4(a, b, c, d) ;
	return M ;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) {
	mat4 M ;
	vec4 a(sx, 0.0, 0.0, 0.0) ;
	vec4 b(0.0, sy, 0.0, 0.0) ;
	vec4 c(0.0, 0.0, sz, 0.0) ;
	vec4 d(0.0, 0.0, 0.0, 1.0) ;
	M = mat4(a, b, c, d) ;
	return M ;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) {
	mat4 M ;
	vec3 a(1.0, 0.0, 0.0) ;
	vec3 b(0.0, 1.0, 0.0) ;
	vec3 c(0.0, 0.0, 1.0) ;
	vec3 d(0.0) ;
	M = mat4(vec4(a, tx), vec4(b, ty), vec4(c, tz), vec4(d, 1.0)) ;
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
