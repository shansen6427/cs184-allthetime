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
#include "Transform2a.h"

int amount; // The amount of rotation for each arrow press
int selected_light;

vec3 eye; // The (regularly updated) vector coordinates of the eye location 
vec3 up;  // The (regularly updated) vector coordinates of the up location 
vec3 center;
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
std::vector<std::vector<std::vector<float>>> objProps ;

// Constants to set up lighting on the teapot
/*
const GLfloat light_position[] = {0, 5, 10, 1};    // Position of light 0
const GLfloat light_position1[] = {0, 5, -10, 1};  // Position of light 1
const GLfloat light_specular[] = {0.6, 0.3, 0, 1};    // Specular of light 0
const GLfloat light_specular1[] = {0, 0.3, 0.6, 1};   // Specular of light 1
const GLfloat one[] = {1, 1, 1, 1};                 // Specular on teapot
const GLfloat medium[] = {0.5, 0.5, 0.5, 1};        // Diffuse on teapot
const GLfloat small[] = {0.2, 0.2, 0.2, 1};         // Ambient on teapot
const GLfloat high[] = {100} ;                      // Shininess of teapot
GLfloat light0[4], light1[4] ; 
*/

// Variables to set uniform params for lighting fragment shader 
GLuint islight ;
/*
GLuint light0posn ; 
GLuint light0color ; 
GLuint light1posn ; 
GLuint light1color ;
*/
GLuint ambient ; 
GLuint diffuse ; 
GLuint specular ; 
GLuint emission ;
GLuint shininess ; 

// OREO
/*
GLfloat lightPosn[10][4] ;
GLfloat lightColor[10][4] ;
GLfloat transLight[10][4] ;
GLuint lightUnipos[10] ;
GLuint lightUnicolor[10] ;
const GLuint maxLights = 10 ;
*/
int lightCount ;
GLuint numLights ;

//ENDOREO

GLfloat light0[4], light1[4], light2[4], light3[4], light4[4], light5[4], light6[4], light7[4], light8[4], light9[4] ; 

GLfloat lights[10][4];

GLfloat lightsposition[10][4];
GLfloat lightsspecular[10][4];

GLfloat lightsposition_backup[10][4];

vec3 lightsup[10];

GLuint light0posn ; 
GLuint light0color ; 
GLuint light1posn ; 
GLuint light1color ;
GLuint light2posn ; 
GLuint light2color ; 
GLuint light3posn ; 
GLuint light3color ; 
GLuint light4posn ; 
GLuint light4color ; 
GLuint light5posn ; 
GLuint light5color ; 
GLuint light6posn ; 
GLuint light6color ; 
GLuint light7posn ; 
GLuint light7color ; 
GLuint light8posn ; 
GLuint light8color ; 
GLuint light9posn ; 
GLuint light9color ; 


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

void keyboard(unsigned char key, int x, int y) {
	vec3 light_eye, w_vec, u_vec, v_vec;
	selected_light = -1;
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
		eye = eyeinit ; 
		up = upinit ; 
        sx = sy = 1.0 ; 
        tx = ty = 0.0 ; 
		for(int x = 0; x < lightCount; x++){
			for(int y = 0; y < 3; y++){
				lightsposition[x][y] = lightsposition_backup[x][y];
			}
		}
		break ;   
    case 'v': 
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
		break;
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
		if(key - 48 >= lightCount){
			std::cout << "There are only " << lightCount
				<< " lights; please select again\n";
		}else{
			transop = view;
			selected_light = key - 48;

			light_eye = vec3(lightsposition[selected_light][0],
								lightsposition[selected_light][1],
								lightsposition[selected_light][2]);
			w_vec = glm::normalize(light_eye);
			u_vec = glm::normalize(glm::cross(up,w_vec));
			v_vec = glm::cross(w_vec,u_vec);
			lightsup[selected_light] = -v_vec;

			std::cout << "Light " << selected_light
				<< " selected for rotation\n";
		}
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
			  if(selected_light == -1) {
				  Transform::left(amount, eye,  up);
			  }else{
				  vec3 light_eye = vec3(lightsposition[selected_light][0],
										lightsposition[selected_light][1],
										lightsposition[selected_light][2]);

				
				  Transform::left(amount, light_eye, lightsup[selected_light]);
				  lightsposition[selected_light][0] = light_eye.x;
				  lightsposition[selected_light][1] = light_eye.y;
				  lightsposition[selected_light][2] = light_eye.z;
			  }
		  }
          else if (transop == scale) sx -= amount * 0.01 ; 
          else if (transop == translate) tx -= amount * 0.01 ; 
          break;
	case 101: //up
          if (transop == view){
			  if(selected_light == -1){
				  Transform::up(amount,  eye,  up);
			  }else{
				vec3 light_eye = vec3(lightsposition[selected_light][0],
										lightsposition[selected_light][1],
										lightsposition[selected_light][2]);

				vec3 lightup = -lightsup[selected_light];
				
				std::cout << "before lightsup: (" << lightsup[selected_light].x << ", " << lightsup[selected_light].y << ", " << lightsup[selected_light].z << ")\n";
				//Transform::up(amount, light_eye, -lightsup[selected_light]);
				Transform::up(amount, light_eye, lightup);
				std::cout << "after lightsup: (" << lightup.x << ", " << lightup.y << ", " << lightup.z << ")\n";
				lightsup[selected_light] = -lightup;
				lightsposition[selected_light][0] = light_eye.x;
				lightsposition[selected_light][1] = light_eye.y;
				lightsposition[selected_light][2] = light_eye.z;
			  }
		  }
          else if (transop == scale) sy += amount * 0.01 ; 
          else if (transop == translate) ty += amount * 0.01 ; 
          break;
	case 102: //right
		if (transop == view){
			if(selected_light == -1) {
				Transform::left(-amount, eye,  up);
			}else{
				vec3 light_eye = vec3(lightsposition[selected_light][0],
										lightsposition[selected_light][1],
										lightsposition[selected_light][2]);
				
				Transform::left(-amount, light_eye, lightsup[selected_light]);
				lightsposition[selected_light][0] = light_eye.x;
				lightsposition[selected_light][1] = light_eye.y;
				lightsposition[selected_light][2] = light_eye.z;
			}
		}
		else if (transop == scale) sx += amount * 0.01 ; 
        else if (transop == translate) tx += amount * 0.01 ; 
        break;
	case 103: //down
          if (transop == view){
			  if(selected_light == -1){
				  Transform::up(-amount,  eye,  up);
			  }else{
				vec3 light_eye = vec3(lightsposition[selected_light][0],
										lightsposition[selected_light][1],
										lightsposition[selected_light][2]);
				
				Transform::up(-amount, light_eye, -lightsup[selected_light]);
				lightsposition[selected_light][0] = light_eye.x;
				lightsposition[selected_light][1] = light_eye.y;
				lightsposition[selected_light][2] = light_eye.z;
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
	amount = 5;
    sx = sy = 1.0 ; 
    tx = ty = 0.0 ;
	useGlu = false;
	zNear = 0.1 ;
	zFar = 99.0 ;
	fovy = 90.0 ;

	//OREO
	lightCount = 0 ;
	//ENDOREO
	selected_light = -1;

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

	//OREO
	/*
	for (int i = 0; i < maxLights; i++) {
		char name[20] ;
		sprintf(name, "lightUnipos[%d]", i) ;
		lightUnipos[i] = glGetUniformLocation(shaderprogram, name) ;
		sprintf(name, "lightUnicolor[%d]", i) ;
		lightUnicolor[i] = glGetUniformLocation(shaderprogram, name) ;
	}
	*/
	//ENDOREO

	numLights = glGetUniformLocation(shaderprogram, "num_lights");

	 light0posn = glGetUniformLocation(shaderprogram,"light0posn") ;       
      light0color = glGetUniformLocation(shaderprogram,"light0color") ;       
      light1posn = glGetUniformLocation(shaderprogram,"light1posn") ;       
      light1color = glGetUniformLocation(shaderprogram,"light1color") ;   
	  light2posn = glGetUniformLocation(shaderprogram,"light2posn") ;       
      light2color = glGetUniformLocation(shaderprogram,"light2color") ;       
      light3posn = glGetUniformLocation(shaderprogram,"light3posn") ;       
      light3color = glGetUniformLocation(shaderprogram,"light3color") ;   
	  light4posn = glGetUniformLocation(shaderprogram,"light4posn") ;       
      light4color = glGetUniformLocation(shaderprogram,"light4color") ;       
      light5posn = glGetUniformLocation(shaderprogram,"light5posn") ;       
      light5color = glGetUniformLocation(shaderprogram,"light5color") ;   
	  light6posn = glGetUniformLocation(shaderprogram,"light6posn") ;       
      light6color = glGetUniformLocation(shaderprogram,"light6color") ;       
      light7posn = glGetUniformLocation(shaderprogram,"light7posn") ;       
      light7color = glGetUniformLocation(shaderprogram,"light7color") ;   
	  light8posn = glGetUniformLocation(shaderprogram,"light8posn") ;       
      light8color = glGetUniformLocation(shaderprogram,"light8color") ;       
      light9posn = glGetUniformLocation(shaderprogram,"light9posn") ;       
      light9color = glGetUniformLocation(shaderprogram,"light9color") ;   

    /*  
	light0posn = glGetUniformLocation(shaderprogram,"light0posn") ;          
	light0color = glGetUniformLocation(shaderprogram,"light0color") ;         
	light1posn = glGetUniformLocation(shaderprogram,"light1posn") ;          
	light1color = glGetUniformLocation(shaderprogram,"light1color") ; 
	*/
	ambient = glGetUniformLocation(shaderprogram,"ambient") ;           
	diffuse = glGetUniformLocation(shaderprogram,"diffuse") ;          
	specular = glGetUniformLocation(shaderprogram,"specular") ;  
	emission = glGetUniformLocation(shaderprogram, "emission") ;
	shininess = glGetUniformLocation(shaderprogram,"shininess") ;       
}

void display() {
	glClearColor(0, 0, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_MODELVIEW);
	mat4 mv ;

    if (useGlu) mv = glm::lookAt(eye,center,up) ; 
	else {
          mv = Transform::lookAt(eye,center,up) ; 
          mv = glm::transpose(mv) ; // accounting for row major
        }
    glLoadMatrixf(&mv[0][0]) ; 

        // Set Light and Material properties for the teapot
        // Lights are transformed by current modelview matrix. 
        // The shader can't do this globally. 
        // So we need to do so manually. 
		/*
        transformvec(light_position, light0) ; 
        transformvec(light_position1, light1) ; 
 
		glUniform4fv(light0posn, 1, light0) ; 
        glUniform4fv(light0color, 1, light_specular) ; 
        glUniform4fv(light1posn, 1, light1) ; 
        glUniform4fv(light1color, 1, light_specular1) ; 
	
		glUniform4fv(ambient,1,small) ; 
        glUniform4fv(diffuse,1,small) ; 
        glUniform4fv(specular,1,one) ; 
        glUniform1fv(shininess,1,high) ; 
        glUniform1i(islight,true) ;
		*/

		glUniform1i(numLights, lightCount);

		//OREO
		/*
		for (int i = 0; i < maxLights; i++) {
			transformvec(lightPosn[i], transLight[i]) ;
			glUniform4fv(lightUnipos[i], 1, transLight[i]) ;
			glUniform4fv(lightUnicolor[i], 1, lightColor[i]) ;
		}
		*/
		//ENDOREO

		switch(lightCount){
			case 10:
				transformvec(lightsposition[9], light9);
				glUniform4fv(light9posn, 1, light9) ;
				glUniform4fv(light9color, 1, lightsspecular[9]);
			case 9:
				transformvec(lightsposition[8], light8);
				glUniform4fv(light8posn, 1, light8) ;
				glUniform4fv(light8color, 1, lightsspecular[8]);
			case 8:
				transformvec(lightsposition[7], light7);
				glUniform4fv(light7posn, 1, light7) ;
				glUniform4fv(light7color, 1, lightsspecular[7]);
			case 7:
				transformvec(lightsposition[6], light6);
				glUniform4fv(light6posn, 1, light6) ;
				glUniform4fv(light6color, 1, lightsspecular[6]);
			case 6:
				transformvec(lightsposition[5], light5);
				glUniform4fv(light5posn, 1, light5) ;
				glUniform4fv(light5color, 1, lightsspecular[5]);
			case 5:
				transformvec(lightsposition[4], light4);
				glUniform4fv(light4posn, 1, light4) ;
				glUniform4fv(light4color, 1, lightsspecular[4]);
			case 4:
				transformvec(lightsposition[3], light3);
				glUniform4fv(light3posn, 1, light3) ;
				glUniform4fv(light3color, 1, lightsspecular[3]);
			case 3:
				transformvec(lightsposition[2], light2);
				glUniform4fv(light2posn, 1, light2) ;
				glUniform4fv(light2color, 1, lightsspecular[2]);
			case 2:
				transformvec(lightsposition[1], light1);
				glUniform4fv(light1posn, 1, light1) ;
				glUniform4fv(light1color, 1, lightsspecular[1]);
			case 1:
				transformvec(lightsposition[0], light0);
				glUniform4fv(light0posn, 1, light0) ;
				glUniform4fv(light0color, 1, lightsspecular[0]);
			default:
				break;
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
	std::vector<std::vector<float>> props ;
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
		up = vec3(cam[6], cam[7], cam[8]) ;
		fovy = cam[9] ;
	} else if (!cmd.compare("light")) {
		if (numParams != 8) stopInvalid();

		//OREO
		/*
		for (int i = 0; i < 4; i++) {
			lightPosn[lightCount][i] = atof(params[i].c_str()) ;
			lightColor[lightCount][i] = atof(params[i + 4].c_str()) ;
		}
		lightCount++;
		*/
		//ENDOREO

		lightsposition[lightCount][0] = atof(params[0].c_str());
		lightsposition[lightCount][1] = atof(params[1].c_str());
		lightsposition[lightCount][2] = atof(params[2].c_str());
		lightsposition[lightCount][3] = (atof(params[3].c_str()) == 0) ? 1 : atof(params[3].c_str());
		lightsspecular[lightCount][0] = atof(params[4].c_str());
		lightsspecular[lightCount][1] = atof(params[5].c_str());
		lightsspecular[lightCount][2] = atof(params[6].c_str());
		lightsspecular[lightCount][3] = 1;
		lightCount++;

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

void backup_lights(){
	for(int x = 0; x < lightCount; x++){
		for(int y = 0; y < 3; y++){
			lightsposition_backup[x][y] = lightsposition[x][y];
		}
	}
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("HW2: Transformations");

	GLenum err = glewInit() ; 
	if (GLEW_OK != err) { 
		std::cerr << "Error: " << glewGetString(err) << std::endl; 
	} 

	init();
	parse(argv[1])	;
	backup_lights();
	glutDisplayFunc(display);
	glutSpecialFunc(specialKey);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutReshapeWindow(600, 400);
	printHelp();
	glutMainLoop();
	return 0;
}
