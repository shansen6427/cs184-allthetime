/*****************************************************************************/
/* This is the program skeleton for homework 2 in CS 184 by Ravi Ramamoorthi */
/* Extends HW 1 to deal with shading, more transforms and multiple objects   */
/*****************************************************************************/


#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <vector>
#include <math.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "shaders.h"
#include "Transform.h"

int amount; // The amount of rotation for each arrow press

vec3 eye; // The (regularly updated) vector coordinates of the eye location 
vec3 up;  // The (regularly updated) vector coordinates of the up location 
vec3 center;
vec3 eye_center; // The (regularly updated) vector coordinates of the eye lookat location
const vec3 eyeinit(0.0,0.0,5.0) ; // Initial eye position, also for resets
const vec3 upinit(0.0,1.0,0.0) ; // Initial up position, also for resets
const vec3 centerinit(0.0,0.0,0.0) ; 
bool useGlu; // Toggle use of "official" opengl/glm transform vs user code
int w, h; // width and height 
float zNear, zFar ;
float fovy ;
GLuint vertexshader, fragmentshader, shaderprogram ; // shaders
static enum {view, translate, scale} transop ; // which operation to transform by 
float sx, sy ; // the scale in x and y 
float tx, ty ; // the translation in x and y
float eye_dp; // the translation in the eye lookat direction
vec3 resetEye ;
vec3 resetUp ;
vec3 resetCenter ;
float resetFovy ;

bool alt_controls;  // if true, use ghost camera

// Variables for geometry and transforms
int tess = 20 ;
float ambientState[] = {0.0, 0.0, 0.0, 1.0} ;
float diffuseState[] = {0.0, 0.0, 0.0, 1.0} ;
float specularState[] = {0.0, 0.0, 0.0, 1.0} ;
float emissionState[] = {0.0, 0.0, 0.0, 1.0} ;
float shininessState[] = {1} ;
std::stack<mat4> transfstack ;
std::vector<std::string> objects ;
std::vector<mat4> objTransforms ;
std::vector<float> objSize ;
std::vector<std::vector<std::vector<float> > > objProps ;

// Variables to set up lighting
GLfloat lightPosition[10][4] ;
GLfloat lightSpecular[10][4] ;
GLfloat lightTransPos[10][4] ;
GLfloat resetLightPos[10][4] ;
GLuint lightposn[10] ;
GLuint lightcolor[10] ;
GLuint lightcount ;
int numLightsOn ;
int selectedLight ;
vec3 lightsUp[10] ;

// Variables to set uniform params for lighting fragment shader 
GLuint islight ;
GLuint ambient ; 
GLuint diffuse ; 
GLuint specular ; 
GLuint emission ;
GLuint shininess ; 

// New helper transformation function to transform vector by modelview 
// May be better done using newer glm functionality.
void transformvec (const GLfloat input[4], GLfloat output[4]) {
  GLfloat modelview[16] ; // in column major order
  glGetFloatv(GL_MODELVIEW_MATRIX, modelview) ; 
  
  for (int i = 0 ; i < 4 ; i++) {
    output[i] = 0 ; 
    for (int j = 0 ; j < 4 ; j++) 
      output[i] += modelview[4*j+i] * input[j] ; 
  }
}

// Uses the Projection matrices (technically deprecated) to set perspective 
// We could also do this in a more modern fashion with glm.  
void reshape(int width, int height){
	w = width;
	h = height;
        mat4 mv ; // just like for lookat

	glMatrixMode(GL_PROJECTION);
        float aspect = (float) w / (float) h ;
        // I am changing the projection stuff to be consistent with lookat
        if (useGlu) mv = glm::perspective(fovy,aspect,zNear,zFar) ; 
        else {
          mv = Transform::perspective(fovy,aspect,zNear,zFar) ; 
          mv = glm::transpose(mv) ; // accounting for row major 
        }
        glLoadMatrixf(&mv[0][0]) ; 

	glViewport(0, 0, w, h);
}

void printHelp() {
  std::cout << "\npress 'h' to print this message again.\n" 
       << "press '+' or '-' to change the amount of rotation that\noccurs with each arrow press.\n" 
            << "press 'g' to switch between using glm::lookAt and glm::Perspective or your own LookAt.\n"       
            << "press 'r' to reset the transformations.\n"
            << "press 'v' 't' 's' to do view [default], translate, scale.\n"
			<< "press '0' '1' ... '9' to select lights for rotation about the scene.\n" 
            << "press ESC to quit.\n" ;  
    
}

vec3 getLightVec(int lightNum) {
	vec3 lightAsVec = vec3(lightPosition[lightNum][0], lightPosition[lightNum][1], lightPosition[lightNum][2]);
	return lightAsVec ;
}

void changeLightPos(int lightNum, vec3 newPos) {
	lightPosition[lightNum][0] = newPos.x ;
	lightPosition[lightNum][1] = newPos.y ;
	lightPosition[lightNum][2] = newPos.z ;
}

void resetAll() {
	eye = resetEye ; 
	up = resetUp ; 
	center = resetCenter ;
	eye_center = resetCenter ;
	fovy = resetFovy ;
    sx = sy = 1.0 ; 
    tx = ty = 0.0 ;
	useGlu = false;
	zNear = 0.1 ;
	zFar = 99.0 ;
	for (int i = 0; i < numLightsOn; i++) {
		for (int j = 0; j < 3; j++) {
			lightPosition[i][j] = resetLightPos[i][j] ;
		}
	}
}

void keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case '+':
		amount++;
		std::cout << "amount set to " << amount << "\n" ;
		break;
	case '-':
		amount--;
		std::cout << "amount set to " << amount << "\n" ; 
		break;
	case 'g':
		useGlu = !useGlu;
        reshape(w,h) ; 
		std::cout << "Using glm::LookAt and glm::Perspective set to: " << (useGlu ? " true " : " false ") << "\n" ; 
		break;
	case 'h':
		printHelp();
		break;
    case 27:  // Escape to quit
        exit(0) ;
        break ;
    case 'r': // reset eye and up vectors, scale and translate. 
		resetAll() ;
		break ;   
    case 'v': 
		selectedLight = -1 ;
        transop = view ;
        std::cout << "Operation is set to View\n" ; 
        break ; 
    case 't':
        transop = translate ; 
        std::cout << "Operation is set to Translate\n" ; 
        break ; 
    case 's':
        transop = scale ; 
        std::cout << "Operation is set to Scale\n" ; 
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
		if(key - 48 >= numLightsOn){
				std::cout << "There are only " << numLightsOn << " lights; please select again.\n";
		} else {
				transop = view;

				selectedLight = key - 48;
				vec3 lightEye = getLightVec(selectedLight) ;
				vec3 wVec = glm::normalize(lightEye - center);
				vec3 uVec = glm::normalize(glm::cross(up,wVec));
				vec3 vVec = glm::cross(wVec,uVec);
				lightsUp[selectedLight] = vVec;

				std::cout << "Light " << selectedLight << " selected for rotation\n";
		}
	}
	glutPostRedisplay();
}

/**
 *  The controls for the roaming camera.  These are currently only usable as an alternative
 * to the hw2 controls.  Activated when alt_controls = true.  The current controls are:
 * w: move in the direction the camera is currently looking
 * s: move in the opposite direction from which the camera is currently looking
 * a: move to the left of the direction the camera is currently looking
 * d: move to the right of the direction the camera is currently looking
 */
void altkeyboard(unsigned char key, int x, int y){
	mat4 translate_matrix;
	vec3 translate_vec; 
	vec4 eye4 = vec4(eye, 1.0), eye_center4(eye_center, 1.0);
	vec3 w_vec, u_vec;
	switch(key){
		case 'w':
			translate_vec = glm::normalize(vec3((eye_center.x - eye.x), (eye_center.y - eye.y), (eye_center.z - eye.z)));
			translate_matrix = Transform::translate(translate_vec.x * eye_dp, translate_vec.y * eye_dp, translate_vec.z * eye_dp);
			eye4 = eye4 * translate_matrix;
			eye_center4 = eye_center4 * translate_matrix;
			eye.x = eye4.x;  eye.y = eye4.y; eye.z = eye4.z;
			eye_center.x = eye_center4.x; eye_center.y = eye_center4.y; eye_center.z = eye_center4.z;
			break;
		case 's':
			translate_vec = glm::normalize(vec3((eye_center.x - eye.x), (eye_center.y - eye.y), (eye_center.z - eye.z)));
			translate_vec = -translate_vec;
			translate_matrix = Transform::translate(translate_vec.x * eye_dp, translate_vec.y * eye_dp, translate_vec.z * eye_dp);
			eye4 = eye4 * translate_matrix;
			eye_center4 = eye_center4 * translate_matrix;
			eye.x = eye4.x;  eye.y = eye4.y; eye.z = eye4.z;
			eye_center.x = eye_center4.x; eye_center.y = eye_center4.y; eye_center.z = eye_center4.z;
			break;
		case 'a':
		    // Using the up vector create a left vector
			w_vec = glm::normalize(eye - eye_center);
			u_vec = glm::normalize(glm::cross(up,w_vec));
			u_vec = -u_vec;

			translate_matrix = Transform::translate(u_vec.x * eye_dp, u_vec.y * eye_dp, u_vec.z * eye_dp);
			eye4 = eye4 * translate_matrix;
			eye_center4 = eye_center4 * translate_matrix;
			eye.x = eye4.x;  eye.y = eye4.y; eye.z = eye4.z;
			eye_center.x = eye_center4.x; eye_center.y = eye_center4.y; eye_center.z = eye_center4.z;
			break;
		case 'd':
			// Using the up vector create a right vector
			w_vec = glm::normalize(eye - eye_center);
			u_vec = glm::normalize(glm::cross(up,w_vec));

			translate_matrix = Transform::translate(u_vec.x * eye_dp, u_vec.y * eye_dp, u_vec.z * eye_dp);
			eye4 = eye4 * translate_matrix;
			eye_center4 = eye_center4 * translate_matrix;
			eye.x = eye4.x;  eye.y = eye4.y; eye.z = eye4.z;
			eye_center.x = eye_center4.x; eye_center.y = eye_center4.y; eye_center.z = eye_center4.z;
			break;
	}
	glutPostRedisplay();
}

//  You will need to enter code for the arrow keys 
//  When an arrow key is pressed, it will call your transform functions

void specialKey(int key, int x, int y) {
	switch(key) {
	case 100: //left
          if (transop == view) {
			  if (selectedLight == -1) {
				  Transform::left(amount, eye,  up);
			  } else {
				  vec3 lightEye = getLightVec(selectedLight) ;
				  Transform::left(-amount, lightEye, lightsUp[selectedLight]) ;
				  changeLightPos(selectedLight, lightEye) ;
			  }
		  }
          else if (transop == scale) sx -= amount * 0.01 ; 
          else if (transop == translate) tx -= amount * 0.01 ; 
          break;
	case 101: //up
          if (transop == view) {
			  if (selectedLight == -1) {
				  Transform::up(amount, eye, center, up);
			  } else {
				  vec3 lightEye = getLightVec(selectedLight) ;
				  vec3 lightUp = lightsUp[selectedLight] ;
				  Transform::up(amount, lightEye, center, lightUp) ;
				  lightsUp[selectedLight] = lightUp ;
				  changeLightPos(selectedLight, lightEye) ;
			  }
		  }
          else if (transop == scale) sy += amount * 0.01 ; 
          else if (transop == translate) ty += amount * 0.01 ; 
          break;
	case 102: //right
          if (transop == view) {
			  if (selectedLight == -1) {
				  Transform::left(-amount, eye,  up);
			  } else {
				  vec3 lightEye = getLightVec(selectedLight) ;
				  Transform::left(amount, lightEye, lightsUp[selectedLight]) ;
				  changeLightPos(selectedLight, lightEye) ;
			  }
		  }
          else if (transop == scale) sx += amount * 0.01 ; 
          else if (transop == translate) tx += amount * 0.01 ; 
          break;
	case 103: //down
          if (transop == view) {
			  if (selectedLight == -1) {
				  Transform::up(-amount,  eye, center,  up);
			  } else {
				  vec3 lightEye = getLightVec(selectedLight) ;
				  vec3 lightUp = lightsUp[selectedLight] ;
				  Transform::up(-amount, lightEye, center, lightUp) ;
				  lightsUp[selectedLight] = lightUp ;
				  changeLightPos(selectedLight, lightEye) ;
			  }
		  }
          else if (transop == scale) sy -= amount * 0.01 ; 
          else if (transop == translate) ty -= amount * 0.01 ; 
          break;
	}
	glutPostRedisplay();
}

void init() {
  
  // Set up initial position for eye, up and amount
  // As well as booleans 

	eye = eyeinit ; 
	up = upinit ; 
	center = centerinit ;
	eye_center = centerinit;

	amount = 5;
    sx = sy = 1.0 ; 
    tx = ty = 0.0 ;
	eye_dp = 0.05;

	useGlu = false;
	zNear = 0.1 ;
	zFar = 99.0 ;
	fovy = 90.0 ;

	numLightsOn = 0 ;
	selectedLight = -1 ;

	alt_controls = true;

	// Initialize the stack
	transfstack.push(mat4(1.0)) ;

	glEnable(GL_DEPTH_TEST);

  // The lighting is enabled using the same framework as in mytest 3 
  // Except that we use two point lights
  // For now, lights and materials are set in display.  Will move to init 
  // later, per update lights

    vertexshader = initshaders(GL_VERTEX_SHADER, "shaders/light.vert.glsl") ;
    fragmentshader = initshaders(GL_FRAGMENT_SHADER, "shaders/light.frag.glsl") ;
    shaderprogram = initprogram(vertexshader, fragmentshader) ; 
    islight = glGetUniformLocation(shaderprogram,"islight") ;        
	
	char name[20] ;
	for (int i = 0; i < 10; i++) {
		sprintf(name, "lightposn[%d]", i) ;
		lightposn[i] = glGetUniformLocation(shaderprogram, name) ;
		sprintf(name, "lightcolor[%d]", i) ;
		lightcolor[i] = glGetUniformLocation(shaderprogram, name) ;
	}
	lightcount = glGetUniformLocation(shaderprogram,"lightcount") ;

	ambient = glGetUniformLocation(shaderprogram,"ambient") ;           
	diffuse = glGetUniformLocation(shaderprogram,"diffuse") ;          
	specular = glGetUniformLocation(shaderprogram,"specular") ; 
	emission = glGetUniformLocation(shaderprogram,"emission") ; 
	shininess = glGetUniformLocation(shaderprogram,"shininess") ;       
}

void display() {
	glClearColor(0, 0, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_MODELVIEW);
	mat4 mv ;

    if (useGlu) mv = glm::lookAt(eye,center,up) ; 
	else {
		  if(alt_controls){
			mv = Transform::lookAt(eye,eye_center,up) ;
		  }else{
			mv = Transform::lookAt(eye,center,up) ;
		  }
          mv = glm::transpose(mv) ; // accounting for row major
        }
    glLoadMatrixf(&mv[0][0]) ; 

        // Set Light and Material properties for the teapot
        // Lights are transformed by current modelview matrix. 
        // The shader can't do this globally. 
        // So we need to do so manually. 

		glUniform1i(lightcount, numLightsOn) ;
		for (int i = 0; i < numLightsOn; i++) {
			transformvec(lightPosition[i], lightTransPos[i]) ;
			glUniform4fv(lightposn[i], 1, lightTransPos[i]) ;
			glUniform4fv(lightcolor[i], 1, lightSpecular[i]) ;
		}

		mat4 sc(1.0), tr(1.0) ;
		sc = Transform::scale(sx,sy,1.0) ; 
		tr = Transform::translate(tx,ty,0.0) ;
		// Multiply the matrices, accounting for OpenGL and GLM.
		sc = glm::transpose(sc) ; tr = glm::transpose(tr) ;
		for (unsigned int i = 0; i < objects.size() ; i++) {
			mat4 objMat = glm::transpose(objTransforms[i]) ;
			mat4 transf = mv * tr * sc * objMat ;
			glLoadMatrixf(&transf[0][0]) ; 

			// Get material properties
			float tempAmbient[4], tempDiffuse[4], tempSpecular[4], tempEmission[4], tempShininess[1] ;
			for (int j = 0; j < 4; j++) {
				tempAmbient[j] = objProps[i][0][j] ;
				tempDiffuse[j] = objProps[i][1][j] ;
				tempSpecular[j] = objProps[i][2][j] ;
				tempEmission[j] = objProps[i][3][j] ;
			}
			tempShininess[0] = objProps[i][4][0] ;

			glUniform4fv(ambient,1,tempAmbient) ; 
			glUniform4fv(diffuse,1,tempDiffuse) ; 
			glUniform4fv(specular,1,tempSpecular) ; 
			glUniform4fv(emission,1,tempEmission) ;
			glUniform1fv(shininess,1,tempShininess) ; 
			glUniform1i(islight,true) ;
			
			float size = objSize[i] ;

			if (!objects[i].compare("teapot")) {
				glutSolidTeapot(size);
			} else if (!objects[i].compare("sphere")) {
				glutSolidSphere(size, tess, tess) ;
			} else if (!objects[i].compare("cube")) {
				glutSolidCube(size) ;
			}
		}

	glutSwapBuffers();
}

void stopInvalid() {
	std::cerr << "Invalid command and/or number of parameters" << std::endl ;
	throw 2 ;
}

void alterStack(mat4 M) {
	mat4 & T = transfstack.top() ;
	T = M * T ;
}

void saveProps() {
	std::vector<std::vector<float> > props ;
	std::vector<float> temp1, temp2, temp3, temp4, temp5 ;
	for (int i = 0; i < 4; i++) {
		temp1.push_back(ambientState[i]) ;
		temp2.push_back(diffuseState[i]) ;
		temp3.push_back(specularState[i]) ;
		temp4.push_back(emissionState[i]) ;
	}
	temp5.push_back(shininessState[0]) ;

	props.push_back(temp1) ;
	props.push_back(temp2) ;
	props.push_back(temp3) ;
	props.push_back(temp4) ;
	props.push_back(temp5) ;

	objProps.push_back(props) ;
}

// Change the scene or initialize objects depending on command
void execute(std::string cmd, std::vector<std::string> params) {
	int numParams = params.size() ;
	if (!cmd.compare("size")) {
		if (numParams != 2) stopInvalid();
		w = atof(params[0].c_str()) ;
		h = atof(params[1].c_str()) ;
	} else if (!cmd.compare("camera")) {
		if (numParams != 10) stopInvalid();
		float cam[10] ;
		for (int i = 0; i < 10; i++) cam[i] = atof(params[i].c_str()) ;
		eye = vec3(cam[0], cam[1], cam[2]) ;
		center = vec3(cam[3], cam[4], cam[5]) ;
		eye_center = center;

		up = glm::normalize(vec3(cam[6], cam[7], cam[8])) ;
		fovy = cam[9] ;
		resetEye = eye ;
		resetCenter = center ;
		resetUp = up ;
		resetFovy = fovy ;
	} else if (!cmd.compare("light")) {
		if (numParams != 8) stopInvalid();
		for (int i = 0; i < 4; i++) {
			lightPosition[numLightsOn][i] = atof(params[i].c_str()) ;
			resetLightPos[numLightsOn][i] = atof(params[i].c_str()) ;
			lightSpecular[numLightsOn][i] = atof(params[i + 4].c_str()) ;
		}
		numLightsOn++;
	} else if (!cmd.compare("ambient")) {
		if (numParams != 4) stopInvalid();
		for (int i = 0; i < 4; i++) ambientState[i] = atof(params[i].c_str()) ;
	} else if (!cmd.compare("diffuse")) {
		if (numParams != 4) stopInvalid();
		for (int i = 0; i < 4; i++) diffuseState[i] = atof(params[i].c_str()) ;
	} else if (!cmd.compare("specular")) {
		if (numParams != 4) stopInvalid();
		for (int i = 0; i < 4; i++) specularState[i] = atof(params[i].c_str()) ;
	} else if (!cmd.compare("emission")) {
		if (numParams != 4) stopInvalid();
		for (int i = 0; i < 4; i++) emissionState[i] = atof(params[i].c_str()) ;
	} else if (!cmd.compare("shininess")) {
		if (numParams != 1) stopInvalid();
		shininessState[0] = atof(params[0].c_str()) ;
	} else if (!cmd.compare("teapot")) {
		if (numParams != 1) stopInvalid();
		float size = atof(params[0].c_str()) ;
		objects.push_back("teapot") ;
		objTransforms.push_back(transfstack.top()) ;
		objSize.push_back(size) ;
		saveProps() ;
	} else if (!cmd.compare("sphere")) {
		if (numParams != 1) stopInvalid();
		float radius = atof(params[0].c_str()) ;
		objects.push_back("sphere") ;
		objTransforms.push_back(transfstack.top()) ;
		objSize.push_back(radius) ;
		saveProps() ;
	} else if (!cmd.compare("cube")) {
		if (numParams != 1) stopInvalid();
		float size = atof(params[0].c_str()) ;
		objects.push_back("cube") ;
		objTransforms.push_back(transfstack.top()) ;
		objSize.push_back(size) ;
		saveProps() ;
	} else if (!cmd.compare("translate")) {
		if (numParams != 3) stopInvalid();
		float xyz[3];
		for (int i = 0; i < 3; i++) xyz[i] = atof(params[i].c_str()) ;
		alterStack(Transform::translate(xyz[0], xyz[1], xyz[2])) ;
	} else if (!cmd.compare("rotate")) {
		if (numParams != 4) stopInvalid();
		float xyz[3];
		for (int i = 0; i < 3; i++) xyz[i] = atof(params[i].c_str()) ;
		vec3 axis = vec3(xyz[0], xyz[1], xyz[2]) ;
		float degrees = atof(params[3].c_str()) ;
		mat3 rotateMat = Transform::rotate(degrees, axis) ;
		alterStack(mat4(vec4(rotateMat[0], 0.0), vec4(rotateMat[1], 0.0), vec4(rotateMat[2], 0.0), vec4(vec3(0.0), 1.0))) ;
	} else if (!cmd.compare("scale")) {
		if (numParams != 3) stopInvalid();
		float xyz[3];
		for (int i = 0; i < 3; i++) xyz[i] = atof(params[i].c_str()) ;
		alterStack(Transform::scale(xyz[0], xyz[1], xyz[2])) ;
	} else if (!cmd.compare("pushTransform")) {
		if (numParams != 0) stopInvalid();
		transfstack.push(transfstack.top()) ;
	} else if (!cmd.compare("popTransform")) {
		if (numParams != 0) stopInvalid();
		transfstack.pop() ;
	} else {
		stopInvalid() ;
	}
}

void parse(const char * filename) {
	std::cout << filename << std::endl;
	std::string str, ret = "" ; 
    std::ifstream in ; 
    in.open(filename) ; 
    if (!in.is_open()) {
		std::cerr << "Unable to Open File " << filename << "\n" ; 
		throw 2 ;
	}
	getline(in, str) ;
	while (in) {
		if ((str.find_first_not_of("/t/r/n") != std::string::npos) && (str[0] != '#')) {
			std::string cmd, buf = "";
			std::vector<std::string> params ;
			std::stringstream ss(str) ;
			ss >> cmd ;
			while (ss >> buf) {
				params.push_back(buf) ;
			}
			execute(cmd, params) ;
			// std::cout << cmd << std::endl;
			// std::cout << params[0] << std::endl;
		}
		getline (in, str) ;
    }
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("HW2: Transformations");

	GLenum err = glewInit() ; 

	init();
	parse(argv[1]);
	glutDisplayFunc(display);
	glutSpecialFunc(specialKey);
	if(alt_controls){
		glutKeyboardFunc(altkeyboard);
	}else{
		glutKeyboardFunc(keyboard);
	}
	glutReshapeFunc(reshape);
	glutReshapeWindow(600, 400);
	printHelp();
	glutMainLoop();
	return 0;
}
