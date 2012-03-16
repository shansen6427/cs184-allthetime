/*****************************************************************************/
/* This is the program skeleton for homework 2 in CS 184 by Ravi Ramamoorthi */
/* Extends HW 1 to deal with shading, more transforms and multiple objects   */
/*****************************************************************************/

/**
 *  Anubis_alienado.obj provided for free download by www.themovies3d.com, model creation
 * and distribution provided by Scopia Visual Interfaces Systems, s.l. (http://www.scopia.es)
 *  guy.raw and ship.raw (originally "BOY N080409.3DS" and "SHIP N010708.3DS") provided by
 * archive3d.net for non-commercial use
 */

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <vector>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "shaders.h"
#include "Transform.h"
#include "objReader.h"
#include "rawReader.h"
#include "Shapes.h"
#include "QPrint.h"

// View variables
const float eye_height = 1.0 ;
const vec3 eyeinit(0.0, -2.0, eye_height) ;
const vec3 upinit(0.0, 0.0, 1.0) ;
const vec3 centerinit(0.0, 2.0, eye_height) ; 
const int scene_width = 640 ;
const int scene_height = 480 ;
const float zNear = 0.1 ;
const float zFar = 99.0 ;
const float fovy = 30.0 ;
vec3 eye; // The (regularly updated) vector coordinates of the eye location 
/* !!!
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
GLuint lam_vertexshader, lam_fragmentshader, lam_shaderprogram; // alternate shaders

static enum {view, translate, scale, zoom} transop ; // which operation to transform by 
float sx, sy ; // the scale in x and y 
float tx, ty ; // the translation in x and y
*/
vec3 up; // The (regularly updated) vector coordinates of the up location
vec3 center; // The (regularly updated) vector coordinates of the center location
vec3 resetEye ;
vec3 resetUp ;
vec3 resetCenter ;
GLuint vertexshader, fragmentshader, shaderprogram ; // Shader variables
GLuint lam_vertexshader, lam_fragmentshader, lam_shaderprogram; // alternate shaders

static enum {view, zoom, play} transop ; // Mode of viewing

// Room variables
const float room_length = 10.0f ;
const float half_room = room_length / 2 ;
const float room_height = room_length / 2 ;
const float half_height = room_height / 2 - 0.1f ; // Account for jumping which can reveal outside
const float full_height = 2 * half_height ; // Slightly less than room_height

// Board variables
const float z_scale = 1.3f ;
const float letter_scale = 0.8f ;
const float block_size = 0.4f ;
const float spacing = 0.02f ;
const float center_of_board = 4.5 * block_size + 4.5 * spacing ;

// Lighting variables
GLfloat lightPosition[10][4] ;
GLfloat lightSpecular[10][4] ;
GLfloat lightTransPos[10][4] ;

const int numLightsOn = 5 ;
const float light_bright_ceil = 0.5 ;
const float light_bright_dir = 1.0 ;
const GLfloat base_lights[numLightsOn][8] = {
	{center_of_board, 0.0f, full_height - 1.0f, 1.0f, 0.5f, 0.5f, 0.5f, 1.0f},
	{-half_room, 0.0f, full_height, 0.0f, light_bright_dir, light_bright_dir, light_bright_dir, 1.0f},
	{0.0f, -half_room, full_height, 0.0f, light_bright_dir/2, light_bright_dir/2, light_bright_dir/2, 1.0f},
	{0.0f, half_room, full_height, 0.0f, light_bright_dir/2, light_bright_dir/2, light_bright_dir/2, 1.0f},
	{half_room, 0.0f, full_height, 0.0f, light_bright_dir/4, light_bright_dir/4, light_bright_dir/4, 1.0f},
} ;

// Color variables
const float black[4] = {0.0, 0.0, 0.0, 1.0} ;
const float white[4] = {1.0, 1.0, 1.0, 1.0} ;
const float red[4] = {1.0, 0.0, 0.0, 1.0} ;
const float gray[4] = {0.5, 0.5, 0.5, 1.0} ;
const float blue[4] = {0.0, 0.0, 1.0, 1.0} ;
const float green[4] = {0.0, 1.0, 0.0, 1.0} ;
const float yellow[4] = {1.0, 1.0, 0.0, 1.0} ;
const float base_gray[4] = {0.47, 0.53, 0.59, 1.0} ;

const float red_ambi[4] = {0.2, 0.0, 0.0, 1.0} ;
const float gray_ambi[4] = {0.1, 0.1, 0.1, 1.0} ;
const float blue_ambi[4] = {0.0, 0.0, 0.2, 1.0} ;
const float green_ambi[4] = {0.0, 0.2, 0.0, 1.0} ;
const float yellow_ambi[4] = {0.2, 0.2, 0.0, 1.0} ;

const float base_ambi[4] = {0.0, 0.0, 0.0, 1.0} ;
const float base_diff[4] = {0.5, 0.5, 0.5, 1.0} ;
const float base_spec[4] = {1.0, 1.0, 1.0, 1.0} ;
const float base_emis[4] = {0.0, 0.0, 0.0, 1.0} ;
const float base_shin[1] = {100} ;

const float low_spec[4] = {0.1, 0.1, 0.1, 1.0} ;

// Keyboard and mouse variables
const vec3 worldUp = vec3(0.0, 0.0, 1.0) ;
//const float viscosity = 50.0f ; // Constant scale factor for movement
const float viscosity = 10.0f ; // Constant scale factor for movement
const float move_amount = 0.6f / viscosity ;
const float turn_amount = -10.0f / viscosity ; // Negative due to the way rotation works
const float jump_amount = 2.0f / viscosity ;
const float g_accel = -.025f / viscosity ;
const float camera_turn_amount = .1f ;
const float zoom_amount = .03f ;
vec3 forward_dir, move_center, forward_velocity, side_velocity, up_velocity ;
float fb_speed, lr_speed, turn_speed ;
bool align_flag, aligned, viewing, jumping ; // Maintain alignment status
bool key_press_arr[6] ; // Maintain states of key presses

const GLuint GLUT_SCROLL_UP = 3 ;
const GLuint GLUT_SCROLL_DOWN = 4 ;
int mouseoldx, mouseoldy ;

// Game variables
const float block_speed = 0.5 ;
const char correct_arr[10] = {'w', 'h', 'e', 'l', 'o', 'f', 'r', 't', 'u', 'n'} ;
const char block_letters[14] = {'w', 'h', 'e', 'e', 'l', 'o', 'f', 'f', 'o', 'r', 't', 'u', 'n', 'e'} ; // 
std::vector<char> unguessed_vec ;
std::vector<char> guessed_vec ;
float block_rotations[14] ;
bool block_activity[14] ; // Signal the block to rotate
float block_velocity ; // Negative will reveal the block (CW)

const float idle_speed = 1.0 ; // Spinning when out-of-game
const float init_wheel_speed = 5.0 ;
const float wheel_decel = -0.01 ;
float idle_angle ;
float wheel_speed ;
float wheel_angle ;
bool spinning, has_spun ;

const vec3 play_location = vec3(1.5, -(half_room - 0.5f), eye_height) ; // Player must be within play_radius of play_location
const vec3 board_location = vec3(center_of_board, half_room, eye_height) ; // Must also face board_location
const float play_radius = 0.5 ;
bool in_game ;
bool board_ready ; 
int total_score, spin_points ;

// Fragment shader variables
GLint fill_wiring ;
GLint lighting ;
GLint texturing ;
GLuint istex ;
GLuint islight ;
GLuint ambient ; 
GLuint diffuse ; 
GLuint specular ; 
GLuint emission ;
GLuint shininess ;
GLuint lightposn[10] ;
GLuint lightcolor[10] ;
GLuint lightcount ;

GLuint isperturbed;

/* !!!
// MICE
int mouseoldx, mouseoldy ;
// MICE

// CONTROL
bool alt_controls ;
float eye_dp; // the translation in the eye lookat direction
vec3 eye_center; // The (regularly updated) vector coordinates of the eye lookat location
// CONTROL

// CONTROL2
float move_amount ;
float turn_amount ;
vec3 forward_dir ;
vec3 move_center ;
// CONTROL 2

// file variables
objReader obj;
rawReader raw;
*/
// New helper transformation function to transform vector by modelview 
// May be better done using newer glm functionality.
// Texture variables
GLuint texNames[6] ; // Texture name holder
GLubyte marbletexture[256][256][3] ;
GLubyte woodtexture[256][256][3] ;
GLubyte signtexture[1200][600][3] ;
GLubyte baytexture[640][320][3] ;
GLubyte towertexture[500][250][3] ;
GLubyte stuccotexture[160][160][3] ;

#include "geometry.h" // Include after texture variables

// file variables
objReader obj;
rawReader raw, raw2;

/**
 * Transforms INPUT by modelview matrix and returns OUTPUT.
 */
void transformvec (const GLfloat input[4], GLfloat output[4]) {
  GLfloat modelview[16] ; // in column major order
  glGetFloatv(GL_MODELVIEW_MATRIX, modelview) ; 
  
  for (int i = 0 ; i < 4 ; i++) {
    output[i] = 0 ; 
    for (int j = 0 ; j < 4 ; j++) 
      output[i] += modelview[4*j+i] * input[j] ; 
  }
}

/**
 * Loads projection matrix and reshapes window according to WIDTH
 * and HEIGHT.
 */
void reshape(int width, int height){

	glMatrixMode(GL_PROJECTION);
    float aspect = (float) width / (float) height ;
	mat4 mv = glm::perspective(fovy, aspect, zNear, zFar) ;
    glLoadMatrixf(&mv[0][0]) ; 

	glViewport(0, 0, width, height);
}

/**
 * Prints UI functionality.
 */
void printHelp() {
	std::cout << "\nInstructions \n"
		<< "Movement: \n"
		<< "\tW - forward\n" << "\tS - backward\n" << "\tQ - left\n" << "\tE - right\n" 
		<< "\tA - turn counterclockwise\n" << "\tD - turn clockwise\n" << "\tSPACE - jump\n\n" 
		<< "Toggles:\n"       
		<< "\tF - switch between fill and wireframe rendering for desk\n"
		<< "\tT - turn on/off texturing\n" << "\tL - turn on/off lighting\n"
		<< "Mouse: \n"
		<< "\tLeft-click and drag to look around\n" << "\tRight-click to return to forward view\n"
		<< "Modes:\n"  
		<< "\tZ - switch to zoom mode\n" << "\t  - Note: fixes viewing angle\n"
		<< "\tP - play Wheel of Fortune\n" << "\t  - Note: must be standing behind the desk and facing the board\n"
		<< "Misc.:\n"
		<< "\tR - reset the scene\n"
		<< "\tESC - quit\n"
		<< "\tH - repeat these instructions\n\n" ;
}

/**
 * Returns camera to saved position.
 */
void resetCamera() {
	eye = resetEye ;
	center = resetCenter ;
	up = resetUp ;
}

/**
 * Saves current camera position.
 */
void saveResets() {
	resetEye = eye ;
	resetCenter = center ;
	resetUp = up ;
}

/**
 * Recursive timer function used for alignment of center to move_center (camera to forward).
 * Takes and passes decreasing VALUE to determine number of calls.
 */
void alignTimer(int value) {
	glutPostRedisplay() ;
	if (value > 0 && !viewing) { // Make sure the mouse is not in-use
		Transform::centeralign(eye, move_center, center, up, value) ;
		glutTimerFunc(1, alignTimer, --value) ; // Decrement and call recursively
	} else if (viewing) {
		align_flag = true ; // If stopped in the middle of aligning, switch flag
	}
	if (value == 0) { // Completed alignment
		center = move_center ;
		up = worldUp ;
		aligned = true ;
	}
}


/**
 * Set and get key statuses.
 * Accesses key_press_arr according to CMD at location KEY. If setting, uses NEW_VAL.
 */
bool scanKeys(std::string cmd, unsigned char key, bool new_val) {
	int index = -1 ;
	if (key == 'q') index = 0 ;
	else if (key == 'w') index = 1 ;
	else if (key == 'e') index = 2 ;
	else if (key == 'a') index = 3 ;
	else if (key == 's') index = 4 ;
	else if (key == 'd') index = 5 ;

	if (!cmd.compare("get")) return key_press_arr[index] ;
	else if (!cmd.compare("set")) key_press_arr[index] = new_val ;

	return false ;
}

/**
 * Reset guessed and unguessed vectors.
 */
void resetGuesses() {
	unguessed_vec.clear() ;
	guessed_vec.clear() ;
	for (int i = 0; i < 10; i++) {
		unguessed_vec.push_back(correct_arr[i]) ;
	}
}

/**
 * Signal all blocks to rotate to default positions.
 */
void resetRotations() {
	for (int i = 0; i < 14; i++) {
		block_activity[i] = true ;
		block_velocity = block_speed ;
	}
}

/**
 * Process player's guess KEY. Updates blocks and points.
 */
void playerGuess(unsigned char key) {
	bool guessed_right = false ;
	bool guessed_repeat = false ;
	for (unsigned int i = 0; i < unguessed_vec.size(); i++) {
		if (key == unguessed_vec[i]) {
			unguessed_vec.erase(unguessed_vec.begin() + i) ;
			guessed_vec.push_back(key) ;
			guessed_right = true ;
			break ;
		}
	}

	for (unsigned int i = 0; i < guessed_vec.size(); i++) {
		if (key == guessed_vec[i]) {
			guessed_repeat = true ;
			break ;
		}
	}

	if (guessed_right) {
		int letters_flipped = 0 ;
		for (int i = 0; i < 14; i++) {
			if (key == block_letters[i]) {
				block_activity[i] = true ;
				letters_flipped++ ;
			}
		}
		total_score += spin_points * letters_flipped ;
		std::cout << "Yes, there is(are) " << letters_flipped << " " << key << "('s)." << std::endl ;
		std::cout << "That brings your score to " << total_score << "." << std::endl ;
	} else if (guessed_repeat) {
		std::cout << "You've already guessed that!" << std::endl ;
	} else {
		std::cout << "Sorry, there are no " << key << "'s." << std::endl ;
	}

	if (unguessed_vec.size() == 0) {
		std::cout << std::endl << "Congratulations! You've solved the puzzle!" << std::endl ;
		std::cout << "Your score is: " << total_score << std::endl ;
		in_game = false ;
	} else {
		std::cout << std::endl << "Spin again. " << std::endl << std::endl ;
	}
}

/* !!! probably deprecated
void altKeyboard(unsigned char key, int x, int y){
	mat4 translate_matrix;
	vec3 translate_vec; 
	vec4 eye4 = vec4(eye, 1.0), eye_center4(eye_center, 1.0);
	vec3 w_vec, u_vec;
	vec3 worldUp = vec3(0.0, 0.0, 1.0) ;
	vec3 move_vec = move_center - eye ;
	vec3 forward_dir = glm::normalize(vec3(move_vec[0], move_vec[1], 0.0)) ;
	vec3 cross_vec = glm::cross(move_vec, worldUp) ;
	vec3 side_dir = glm::normalize(vec3(cross_vec[0], cross_vec[1], 0.0)) ;
	if (transop == zoom) {
*/
/**
 * Stop the program for MSECONDS milliseconds.
 */
void sleep(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

/**
 * Print game instructions.
 */
void printInstructions() {
	std::cout << "\nHow-to-play\n"
		<< "\tKeyboard: \n"
		<< "\tENTER - spin the wheel\n"
		<< "\tA to Z - guess a letter\n"
		<< "\tTAB - see instructions again\n"
		<< "\tESC - exit the game\n"
		<< "Winning condition:\n"
		<< "\t- reveal all the letters\n"
		<< "Puzzle hint:\n"
		<< "\t- TV game show\n\n" ;
}

/**
 * Print zoom mode instructions.
 */
void printZoom() {
	std::cout << "\nInstructions\n"
		<< "Mouse:\n"
		<< "\tLeft-click and drag up/down to zoom\n"
		<< "Misc.:\n"
		<< "\tV - return to viewing mode\n" ;
}

/**
 * Initialize the game variables and print game information.
 */
void startGame() {
	in_game = true ;
	board_ready = false ;
	has_spun = false ;
	spinning = false ;
	wheel_angle = 0.0f ;
	wheel_speed = 0.0f ;
	total_score = 0 ;
	spin_points = 0 ;
	resetGuesses() ;
	resetRotations() ;
	std::cout << "********" << std::endl ;
	std::cout << "Wheel " ;
	sleep(500) ;
	std::cout << "of" << std::endl ;
	sleep(500) ;
	std::cout << "Fortune!" << std::endl ;
	std::cout << "********" << std::endl ;
	printInstructions() ;
}

/**
 *  First-person keyboard controls. 
 *  Changes camera movement according to KEY. Ignores mouse X and Y.
 *  Functionality:
 *  w: Move forward
 *  s: Move backward
 *  a: Turn counterclockwise
 *  d: Turn clockwise
 *  q: Move left
 *  e: Move right
 *  z: Activate zoom
 */
void keyboard(unsigned char key, int x, int y){
	if (transop == play) {
		if (key == 27) {
			in_game = false ;
			transop = view ;
			resetCamera() ;
			resetRotations() ;
			std::cout << "Thank you for playing!" << std::endl ;
			std::cout << "----------------------" << std::endl ;
			std::cout << "\nSwitching to viewing mode.\n" ;
		} else if (key == 9) {
			printInstructions() ;
		} else if (in_game && board_ready) {
			if (key == 13 && !spinning && !has_spun) {
				wheel_speed = init_wheel_speed ; // Spin wheel
				spinning = true ;
			} else if (key >= 97 && key <= 122) {
				if (has_spun) {
					playerGuess(key) ;
					has_spun = false ;
				} else if (spinning) {
					std::cout << "Please wait for the wheel to stop." << std::endl ;
				} else {
					std::cout << "You must spin first(ENTER) before guessing a letter." << std::endl ;
				}
			} else {
				if (has_spun) {
					std::cout << "Guess must be a letter of the alphabet; try again." << std::endl ;
				} else if (spinning) {
					std::cout << "Please wait for the wheel to stop." << std::endl ;
				} else {
					std::cout << "You must spin first(ENTER) before guessing a letter." << std::endl ;
				}
			}
		}
	} else if (transop == zoom) {
		switch(key) {
		case 'v':
			transop = view ;
			resetCamera() ;
			std::cout << "\nSwitching to viewing mode.\n" ;
			break ;
		}
	} else if (transop == view) {
		if (key == 'q' || key == 'w' || key == 'e' || key == 'a' || key == 's' || key == 'd' || key == 32) {
			vec3 move_vec = move_center - eye ;
			vec3 cross_vec = glm::cross(move_vec, worldUp) ;
			vec3 forward_dir = glm::normalize(vec3(move_vec[0], move_vec[1], 0.0)) ;
			vec3 side_dir = glm::normalize(vec3(cross_vec[0], cross_vec[1], 0.0)) ; // Points right of view
	
			vec3 eye_from_m = move_center - eye ;
			vec3 eye_from_c = center - eye ;
			float dot_p = glm::dot(eye_from_m, eye_from_c) / (QPrint::magv(eye_from_m) * QPrint::magv(eye_from_c)) ;

			// Animate the camera
			int steps = 50 ; // Increase for smoother alignment
			if (dot_p < 1.0 && align_flag && center != move_center) { // Last condition avoids weird precision case
				glutTimerFunc(0, alignTimer, steps); // Begin timer
				align_flag = false ; // Avoid calling overlapping timers
				aligned = false ; // Stop movement while aligning
			}
		}

		switch(key){
		case 'w':
			fb_speed = move_amount ;
			break ;
		case 's':
			fb_speed = -move_amount ;
			break ;
		case 'a':
			turn_speed = -turn_amount ;
			break ;
		case 'd':
			turn_speed = turn_amount ;
			break;
		case 'q':
			lr_speed = -move_amount ;
			break;
		case 'e':
			lr_speed = move_amount ;
			break;
		case 32: // Space
			if (!jumping && aligned) {
				up_velocity = jump_amount * worldUp ;
				jumping = true ;
			}
			break ;
		case 'z':
			transop = zoom ;
			saveResets() ; // Maintain "true" position during zooming
			std::cout << "Switching to zoom mode.\n" ;
			printZoom() ;
			break ;
		case 'f':
			fill_wiring = !fill_wiring ;
			std::cout << ((fill_wiring) ? "Fill ON" : "Wireframe ON") << std::endl ;
			break ;
		case 't':
			texturing = !texturing ;
			std::cout << "Textures " << ((texturing) ? "ON" : "OFF") << std::endl ;
			break ;
		case 'l':
			lighting = !lighting ;
			std::cout << "Lighting " << ((lighting) ? "ON" : "OFF") << std::endl ;
			break ;
		case 27:
			exit(0) ;
			break ;
		case 'h':
			printHelp() ;
			break ;
		case 'p':
			float dist_to_play = QPrint::magv(eye - play_location) ;
			vec3 distboard_vec = board_location - eye ;
			vec3 eye_from_m = move_center - eye ;
			float dot_play = glm::dot(eye_from_m, distboard_vec) / (QPrint::magv(eye_from_m) * QPrint::magv(distboard_vec)) ;
			std::cout << dist_to_play << std::endl ;
			std::cout << dot_play << std::endl ;
			if (dist_to_play < 1.0 && dot_play >= 0.9925) { // Must be in the right location and facing the right direction
				transop = play ;
				saveResets() ;
				startGame() ;
			}
			break ;
		}
		if (key == 'q' || key == 'w' || key == 'e' || key == 'a' || key == 's' || key == 'd') {
			scanKeys("set", key, true) ; // Mark the key as active
		}
	}
	
	glutPostRedisplay();
}

/**
 *  Keyboard release controls.
 *  Changes camera movement according to KEY. Ignores mouse X and Y.
 *  Handles opposing movement cases.
*/
void keyboardUp(unsigned char key, int x, int y) {
	vec3 move_vec = move_center - eye ;
	vec3 cross_vec = glm::cross(move_vec, worldUp) ;
	vec3 forward_dir = glm::normalize(vec3(move_vec[0], move_vec[1], 0.0)) ;
	vec3 side_dir = glm::normalize(vec3(cross_vec[0], cross_vec[1], 0.0)) ; // Points right of view

	// If the counterpart key is active, switch over to that key's function
	switch(key) {
	case 'w':
		// forward_velocity = (scanKeys("get", 's', true)) ? -move_amount * forward_dir : vec3(0.0) ;
		fb_speed = (scanKeys("get", 's', true)) ? -move_amount : 0 ;
		break ;
	case 's':
		// forward_velocity = (scanKeys("get", 'w', true)) ? move_amount * forward_dir : vec3(0.0) ;
		fb_speed = (scanKeys("get", 'w', true)) ? move_amount : 0 ;
		break ;
	case 'q': 
		// side_velocity = (scanKeys("get", 'e', true)) ? move_amount * side_dir : vec3(0.0) ;
		lr_speed = (scanKeys("get", 'e', true)) ? move_amount : 0 ;
		break ;
	case 'e':
		// side_velocity = (scanKeys("get", 'q', true)) ? -move_amount * side_dir : vec3(0.0) ;
		lr_speed = (scanKeys("get", 'q', true)) ? -move_amount : 0 ;
		break ;
	case 'a':
		turn_speed = (scanKeys("get", 'd', true)) ? turn_amount : 0 ;
		break ;
	case 'd':
		turn_speed = (scanKeys("get", 'a', true)) ? -turn_amount : 0 ;
		break ;
	}
	scanKeys("set", key, false) ; // Mark the key inactive
}

/**
 *  Mouse click function.
 *  Registers the STATE of a BUTTON press at X and Y.
 */
void mouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {
			mouseoldx = x ;
			mouseoldy = y ;
			viewing = true ; // Stop pending alignment
			align_flag = true ; // Allow alignment
		} else if (button == GLUT_RIGHT_BUTTON) {
			center = move_center ;
			up = worldUp ;
			glutPostRedisplay() ;
		}
	} else if (state == GLUT_UP && button == GLUT_LEFT_BUTTON) {
		viewing = false ;
	}
}

/**
 *  Mouse drag function.
 *  Takes current mouse position X and Y.
 */
void mouseDrag(int x, int y) {
	int xloc = x - mouseoldx ;
	int yloc = y - mouseoldy ;

	if (!jumping) { // Disable camera while jumping
		if (transop == view) {
			Transform::centerleft(camera_turn_amount * xloc, eye, center, up) ; // Rotate center and up about the z-axis
			Transform::centerup(-camera_turn_amount * yloc, eye, center, up) ; // Rotate center and up about the perpendicular axis
		} else if (transop == zoom) {
			Transform::zoom(zoom_amount * yloc, eye, center) ;
		}
	}
	
	mouseoldy = y ;
	mouseoldx = x ;

	glutPostRedisplay() ;
}

void switchShader(bool lambert){
	if(lambert){
		//std::cout << "Now using lambertian shader" << std::endl;
	
		islight = glGetUniformLocation(lam_shaderprogram,"islight") ; 
		isperturbed = glGetUniformLocation(lam_shaderprogram,"isperturbed") ; 
		
		char name[20] ;
		for (int i = 0; i < 10; i++) {
			sprintf(name, "lightposn[%d]", i) ;
			lightposn[i] = glGetUniformLocation(lam_shaderprogram, name) ;
			sprintf(name, "lightcolor[%d]", i) ;
			lightcolor[i] = glGetUniformLocation(lam_shaderprogram, name) ;
		}
		lightcount = glGetUniformLocation(lam_shaderprogram,"lightcount") ;

		ambient = glGetUniformLocation(lam_shaderprogram,"ambient") ;           
		diffuse = glGetUniformLocation(lam_shaderprogram,"diffuse") ;          
		specular = glGetUniformLocation(lam_shaderprogram,"specular") ; 
		emission = glGetUniformLocation(lam_shaderprogram,"emission") ; 
		shininess = glGetUniformLocation(lam_shaderprogram,"shininess") ;
	}else{
		//std::cout << "Now using standard shader" << std::endl;
	
		islight = glGetUniformLocation(shaderprogram,"islight") ;   
		isperturbed = glGetUniformLocation(shaderprogram,"isperturbed") ;   
		
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
}

/* !!!
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
	// CONTROL
	eye_dp = 0.05;
	alt_controls = true ;

	// CONTROL 2
	move_amount = 0.2;
	turn_amount = 3.0;
	move_center = vec3(0.0, 2.0, 1.0);

	numLightsOn = 0 ;
	selectedLight = -1 ;

	alt_controls = false;

	// initialize .obj reader
	//obj.init("Anubis_alienado.obj");
	//obj.moveToCenter();
	//obj.scale(2.0, 2.0, 2.0);
	//obj.translate(0.0, 0.5, 0.0);

	// initialize .raw reader
	raw.init("guy.raw");
	raw.moveToCenter();
	//raw.scale(0.06, 0.06, 0.06);
	raw.scale(0.001, 0.001, 0.001);
	//raw.translate(0.0, 1, 0.0);
	raw.rotate(-90, vec3(1, 0, 0));

	// Initialize the stack
	transfstack.push(mat4(1.0)) ;

	glEnable(GL_DEPTH_TEST);

  // The lighting is enabled using the same framework as in mytest 3 
  // Except that we use two point lights
  // For now, lights and materials are set in display.  Will move to init 
  // later, per update lights

	lam_vertexshader = initshaders(GL_VERTEX_SHADER, "shaders/lam_light.vert.glsl") ;
    lam_fragmentshader = initshaders(GL_FRAGMENT_SHADER, "shaders/lam_light.frag.glsl") ;
	lam_shaderprogram = initprogram(lam_vertexshader, lam_fragmentshader) ;
    
	vertexshader = initshaders(GL_VERTEX_SHADER, "shaders/light.vert.glsl") ;
    fragmentshader = initshaders(GL_FRAGMENT_SHADER, "shaders/light.frag.glsl") ;
    shaderprogram = initprogram(vertexshader, fragmentshader) ; 
    islight = glGetUniformLocation(shaderprogram,"islight") ;        
	
    isperturbed = glGetUniformLocation(shaderprogram,"isperturbed") ;        
	
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
*/

/**
 * Display the scene.
 */
void display() {
	glClearColor(0, 0, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Move smoothly if not in the process of alignment
	if (aligned && transop == view) {
		vec3 move_vec = move_center - eye ;
		vec3 cross_vec = glm::cross(move_vec, worldUp) ;
		vec3 forward_dir = glm::normalize(vec3(move_vec[0], move_vec[1], 0.0f)) ;
		vec3 side_dir = glm::normalize(vec3(cross_vec[0], cross_vec[1], 0.0f)) ; // Points right of view

		forward_velocity = fb_speed * forward_dir ;
		side_velocity = lr_speed * side_dir ;

		float room_limit = half_room - 0.2f ;

		// Forward/backward
		eye += forward_velocity ;
		move_center += forward_velocity ;
		if (eye[0] > room_limit || eye[0] < -room_limit || eye[1] > room_limit || eye[1] < -room_limit) {
			eye -= forward_velocity ;
			move_center -= forward_velocity ;
		}

		// Side
		eye += side_velocity ;
		move_center += side_velocity ;
		if (eye[0] > room_limit || eye[0] < -room_limit || eye[1] > room_limit || eye[1] < -room_limit) {
			eye -= side_velocity ;
			move_center -= side_velocity ;
		}

		// Turn
		Transform::moveleft(turn_speed, eye, move_center) ;

		// Jump
		eye += up_velocity ;
		move_center += up_velocity ;

		// Apply gravity
		if (jumping) up_velocity += g_accel * worldUp ;

		// Stop upon landing
		if (eye[2] < eye_height || move_center[2] < eye_height) {
			eye[2] = move_center[2] = center[2] = eye_height ;
			up_velocity[2] = 0.0f ;
			jumping = false ;
		} 

		// Update if moving
		if (forward_velocity != vec3(0.0f) || side_velocity != vec3(0.0f) || turn_speed != 0.0f || up_velocity != vec3(0.0f)) {
			center = move_center ;
			up = worldUp ;
		}
	}
	glMatrixMode(GL_MODELVIEW);
	mat4 mv = glm::lookAt(eye,center,up) ; 
    glLoadMatrixf(&mv[0][0]) ; 

    // Set lighting  
	glUniform1i(lightcount, numLightsOn) ;
	for (int i = 0; i < numLightsOn; i++) {
		transformvec(lightPosition[i], lightTransPos[i]) ;
		glUniform4fv(lightposn[i], 1, lightTransPos[i]) ;
		glUniform4fv(lightcolor[i], 1, lightSpecular[i]) ;
	}
	
	glUniform4fv(ambient,1,base_ambi) ; 
	glUniform4fv(diffuse,1,base_diff) ; 
	glUniform4fv(specular,1,base_spec) ; 
	glUniform4fv(emission,1,base_emis) ;
	glUniform1fv(shininess,1,base_shin) ; 
	glUniform1i(islight,lighting) ;

	glUniform1i(isperturbed, false);

	// Textured materials
	glUniform1i(istex, texturing) ;
		// Right wall
		glBindTexture(GL_TEXTURE_2D, texNames[2]) ; 
		glPushMatrix() ; 
			glTranslatef(half_room,0.0,half_height) ; 
			Shapes::plane(room_length, room_height, 6) ;
		glPopMatrix() ; 
		// Front wall
		glBindTexture(GL_TEXTURE_2D, texNames[3]) ; 
		glPushMatrix() ; 
			glTranslatef(0.0,half_room,half_height) ; 
			Shapes::plane(room_length, room_height, 3) ;
		glPopMatrix() ; 
		// Back wall
		glBindTexture(GL_TEXTURE_2D, texNames[4]) ;
		glPushMatrix() ; 
			glTranslatef(0.0,-half_room,half_height) ; 
			Shapes::plane(room_length, room_height, 4) ;
		glPopMatrix() ; 
		glUniform4fv(ambient, 1, gray_ambi) ;
		// Floor
		glBindTexture (GL_TEXTURE_2D, texNames[1]) ;
		Shapes::plane(10.0, 10.0, 1) ;
		// Ceiling
		glBindTexture(GL_TEXTURE_2D, texNames[5]) ;
		glPushMatrix() ; 
			glTranslatef(0.0,0.0,full_height) ; 
			Shapes::plane(room_length, room_length, 2) ;
		glPopMatrix() ; 
	glUniform1i(istex, 0) ;

	// Left Wall
	glUniform4fv(diffuse, 1, black) ;
	glUniform4fv(ambient, 1, black) ;
	glUniform4fv(specular, 1, low_spec) ;
		glPushMatrix() ; 
			glTranslatef(-half_room,0.0,half_height) ; 
			Shapes::plane(room_length, room_height, 5) ;
		glPopMatrix() ; 
	glUniform4fv(specular, 1, base_spec) ;

	// Staircase
	float bot_banister_height = 0.4f ;
	float top_banister_height = 2.0f ;
	float banister_length = 3.0f ;
	float banister_thickness = 0.2f ;
	float stair_width = 4.0f ;
	float step_height = (top_banister_height - bot_banister_height) / 4 ;
	float step_width = banister_length / 5 ;
	glPushMatrix() ;
		// First banister
		glUniform4fv(diffuse, 1, red) ;
		glUniform4fv(ambient, 1, red_ambi) ;
		glTranslatef(-half_room + banister_length / 2, -stair_width / 2, 0.0f) ; // Against left wall
		Shapes::banister(bot_banister_height, top_banister_height, banister_length, banister_thickness) ;

		// Stairs
		glUniform4fv(diffuse, 1, gray) ;
		glUniform4fv(ambient, 1, gray_ambi) ;
		glPushMatrix() ;
			glTranslatef(-banister_length / 2 + step_width / 2, stair_width / 2, step_height / 3 + 3 * step_height) ;
			glPushMatrix() ;
				glScalef(step_width, stair_width - banister_thickness, step_height) ;
				glutSolidCube(1.0) ;
			glPopMatrix() ;
			glTranslatef(step_width, 0.0f, -step_height) ;
			glPushMatrix() ;
				glScalef(step_width, stair_width - banister_thickness, step_height) ;
				glutSolidCube(1.0) ;
			glPopMatrix() ;
			glTranslatef(step_width, 0.0f, -step_height) ;
			glPushMatrix() ;
				glScalef(step_width, stair_width - banister_thickness, step_height) ;
				glutSolidCube(1.0) ;
			glPopMatrix() ;
			glTranslatef(step_width, 0.0f, -step_height) ;
			glPushMatrix() ;
				glScalef(step_width, stair_width - banister_thickness, step_height) ;
				glutSolidCube(1.0) ;
			glPopMatrix() ;
		glPopMatrix() ;

		// Second banister
		glUniform4fv(diffuse, 1, red) ;
		glUniform4fv(ambient, 1, red_ambi) ;
		glTranslatef(0.0f, stair_width, 0.0f) ;
		Shapes::banister(bot_banister_height, top_banister_height, banister_length, banister_thickness) ;
	glPopMatrix() ;

	// Wheel and base properties
	float base_height = 0.4f ;
	float middle_base_height = base_height * 0.75f ;
	float bottom_base_height = middle_base_height / 2 ;
	float base_x = center_of_board ;
	float base_y = -1.5 ;
	float base_radius = 0.7 ;
	float middle_base_radius = base_radius + 0.1f ;
	float bottom_base_radius = base_radius + 0.2f ;

	float desk_height = base_height + 0.1f ;
	float desk_inner = bottom_base_radius ;
	float desk_outer = desk_inner + 0.2f ;
	int desk_angle1 = -160 ;
	int desk_angle2 = -20 ;
	float wheel_radius = base_radius + .01f ; // Make the wheel slightly larger than its base
	
	int color_cycle = 0 ; // Variable for determining color of strip
	float stick_height = 0.16 ;

	glLoadMatrixf(&mv[0][0]) ;
	// Upper base

	glUniform4fv(diffuse, 1, base_gray) ;
	glUniform4fv(ambient, 1, gray_ambi) ;
	glPushMatrix() ;
	glTranslatef(base_x, base_y, 0.0) ;
	glBegin(GL_QUAD_STRIP) ;
		for (int i = 0; i <= 360; i++) {
			float theta = (float) i * pi / 180.0f ;
			glNormal3f(cos(theta), sin(theta), 0.0) ;
			glVertex3f(base_radius * cos(theta), base_radius * sin(theta), middle_base_height) ;
			glNormal3f(cos(theta), sin(theta), 0.0) ;
			glVertex3f(base_radius * cos(theta), base_radius * sin(theta), base_height) ;
		}
	glEnd() ;

	// Middle base
	glUniform4fv(diffuse, 1, green) ;
	glUniform4fv(ambient, 1, green_ambi) ;
	glBegin(GL_QUAD_STRIP) ;
		for (int i = 0; i <= 360; i++) {
			float theta = (float) i * pi / 180.0f ;
			glNormal3f(cos(theta), sin(theta), 0.0) ;
			glVertex3f(middle_base_radius * cos(theta), middle_base_radius * sin(theta), bottom_base_height) ;
			glNormal3f(cos(theta), sin(theta), 0.0) ;
			glVertex3f(middle_base_radius * cos(theta), middle_base_radius * sin(theta), middle_base_height) ;
		}
	glEnd() ;

	// Middle top
	glBegin(GL_TRIANGLE_FAN) ;
		glNormal3f(0.0, 0.0, 1.0f) ;
		glVertex3f(0.0f, 0.0f, middle_base_height) ;
		for (int i = 0; i <= 360; i++) {
			float theta = (float) i * pi / 180.0f ;
			glNormal3f(0.0, 0.0, 1.0f) ;
			glVertex3f(middle_base_radius * cos(theta), middle_base_radius * sin(theta), middle_base_height) ;
		}
	glEnd() ;

	// Bottom base
	glBegin(GL_QUAD_STRIP) ;
		for (int i = 0; i <= 360; i++) {
			float theta = (float) i * pi / 180.0f ;
			glNormal3f(cos(theta), sin(theta), 0.0) ;
			glVertex3f(bottom_base_radius * cos(theta), bottom_base_radius * sin(theta), 0.0) ;
			glNormal3f(cos(theta), sin(theta), 0.0) ;
			glVertex3f(bottom_base_radius * cos(theta), bottom_base_radius * sin(theta), bottom_base_height) ;
		}
	glEnd() ;

	// Bottom top
	glBegin(GL_TRIANGLE_FAN) ;
		glNormal3f(0.0, 0.0, 1.0f) ;
		glVertex3f(0.0f, 0.0f, bottom_base_height) ;
		for (int i = 0; i <= 360; i++) {
			float theta = (float) i * pi / 180.0f ;
			glNormal3f(0.0, 0.0, 1.0f) ;
			glVertex3f(bottom_base_radius * cos(theta), bottom_base_radius * sin(theta), bottom_base_height) ;
		}
	glEnd() ;

	if (!fill_wiring) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glUniform4fv(diffuse, 1, blue) ;
	glUniform4fv(ambient, 1, blue_ambi) ;
	// Inner edge
	glBegin(GL_QUAD_STRIP) ;
		for (int i = desk_angle1; i <= desk_angle2; i++) {
			float theta = (float) i * pi / 180.0f ;
			glNormal3f(cos(theta), sin(theta), 0.0) ;
			glVertex3f(desk_inner * cos(theta), desk_inner * sin(theta), 0.0) ;
			glNormal3f(cos(theta), sin(theta), 0.0) ;
			glVertex3f(desk_inner * cos(theta), desk_inner * sin(theta), desk_height) ;
		}
	glEnd() ;

	switchShader(true);

	// Outer edge
	glBegin(GL_QUAD_STRIP) ;
		for (int i = desk_angle1; i <= desk_angle2; i++) {
			float theta = (float) i * pi / 180.0f ;
			glNormal3f(cos(theta), sin(theta), 0.0) ;
			glVertex3f(desk_outer * cos(theta), desk_outer * sin(theta), 0.0) ;
			glNormal3f(cos(theta), sin(theta), 0.0) ;
			glVertex3f(desk_outer * cos(theta), desk_outer * sin(theta), desk_height) ;
		}
	glEnd() ;

	switchShader(false);

	// Desk top
	glBegin(GL_QUAD_STRIP) ;
		for (int i = desk_angle1; i <= desk_angle2; i++) {
			float theta = (float) i * pi / 180.0f ;
			glNormal3f(0.0f, 0.0f, 1.0f) ;
			glVertex3f(desk_inner * cos(theta), desk_inner * sin(theta), desk_height) ;
			glNormal3f(0.0f, 0.0f, 1.0f) ;
			glVertex3f(desk_outer * cos(theta), desk_outer * sin(theta), desk_height) ;
		}
	glEnd() ;

	glBegin(GL_QUADS) ;
		float theta1 = (float) desk_angle1 * pi / 180.0f ;
		float theta2 = (float) desk_angle2 * pi / 180.0f ;

		glNormal3f(sin(theta1), -cos(theta1), 0.0) ;
		glVertex3f(desk_inner * cos(theta1), desk_inner * sin(theta1), 0.0) ;
		glNormal3f(sin(theta1), -cos(theta1), 0.0) ;
		glVertex3f(desk_outer * cos(theta1), desk_outer * sin(theta1), 0.0) ;
		glNormal3f(sin(theta1), -cos(theta1), 0.0) ;
		glVertex3f(desk_outer * cos(theta1), desk_outer * sin(theta1), desk_height) ;
		glNormal3f(sin(theta1), -cos(theta1), 0.0) ;
		glVertex3f(desk_inner * cos(theta1), desk_inner * sin(theta1), desk_height) ;

		glNormal3f(sin(theta2), -cos(theta2), 0.0) ;
		glVertex3f(desk_inner * cos(theta2), desk_inner * sin(theta2), 0.0) ;
		glNormal3f(sin(theta2), -cos(theta2), 0.0) ;
		glVertex3f(desk_outer * cos(theta2), desk_outer * sin(theta2), 0.0) ;
		glNormal3f(sin(theta2), -cos(theta2), 0.0) ;
		glVertex3f(desk_outer * cos(theta2), desk_outer * sin(theta2), desk_height) ;
		glNormal3f(sin(theta2), -cos(theta2), 0.0) ;
		glVertex3f(desk_inner * cos(theta2), desk_inner * sin(theta2), desk_height) ;
	glEnd() ;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glUniform4fv(diffuse, 1, black) ;
	glUniform4fv(ambient, 1, black) ;
	float strip_height = base_height - middle_base_height ;
	float strip_width = 0.05 ;
	// Indicator strip on top base, no normals
	glPushMatrix() ;
		glTranslatef(0.0, 0.0, (base_height + middle_base_height) / 2) ;
		if (in_game) {
			glRotatef(wheel_angle, 0.0, 0.0, 1.0) ;
		} else {
			glRotatef(idle_angle, 0.0, 0.0, 1.0) ;
		}
		glBegin(GL_QUADS) ;
			glVertex3f(-base_radius - .005, strip_width / 2, -strip_height / 2) ;
			glVertex3f(-base_radius - .005, -strip_width / 2, -strip_height / 2) ;
			glVertex3f(-base_radius - .005, -strip_width / 2, strip_height / 2) ;
			glVertex3f(-base_radius - .005, strip_width / 2, strip_height / 2) ;

			glVertex3f(base_radius + .005, strip_width / 2, -strip_height / 2) ;
			glVertex3f(base_radius + .005, -strip_width / 2, -strip_height / 2) ;
			glVertex3f(base_radius + .005, -strip_width / 2, strip_height / 2) ;
			glVertex3f(base_radius + .005, strip_width / 2, strip_height / 2) ;

			glVertex3f(strip_width / 2, base_radius + .005, -strip_height / 2) ;
			glVertex3f(-strip_width / 2, base_radius + .005, -strip_height / 2) ;
			glVertex3f(-strip_width / 2, base_radius + .005, strip_height / 2) ;
			glVertex3f(strip_width / 2, base_radius + .005, strip_height / 2) ;

			glVertex3f(strip_width / 2, -base_radius - .005, -strip_height / 2) ;
			glVertex3f(-strip_width / 2, -base_radius - .005, -strip_height / 2) ;
			glVertex3f(-strip_width / 2, -base_radius - .005, strip_height / 2) ;
			glVertex3f(strip_width / 2, -base_radius - .005, strip_height / 2) ;
		glEnd() ;
	glPopMatrix() ;

	glTranslatef(0.0, 0.0, base_height) ; // Place wheel on top of base
	// Have wheel spin idly until game starts
	if (in_game) {
		glRotatef(wheel_angle, 0.0, 0.0, 1.0) ;
	} else {
		glRotatef(idle_angle, 0.0, 0.0, 1.0) ;
	}
	idle_angle += idle_speed ;
	if (idle_angle >= 360) idle_angle = 0 ; 
	wheel_angle += wheel_speed ;
	if (wheel_speed > 0) wheel_speed += wheel_decel ;
	if (wheel_speed < 0) {
		wheel_speed = 0 ;
		spinning = false ;
		has_spun = true ;
		spin_points = ((rand() % 10) + 1) * 100 ;
		std::cout << "You've landed on " << spin_points << " points." << std::endl ;
	}

	int num_triangles = 20 ;
	int angle_step = 360 / num_triangles ;
	for (int i = 0; i < 360; i += angle_step) {
		if (color_cycle % 4 == 0) {
			glUniform4fv(diffuse, 1, red) ;
			glUniform4fv(ambient, 1, red_ambi) ;
		} else if (color_cycle % 4 == 1) {
			glUniform4fv(diffuse, 1, green) ;
			glUniform4fv(ambient, 1, green_ambi) ;
		} else if (color_cycle % 4 == 2) {
			glUniform4fv(diffuse, 1, blue) ;
			glUniform4fv(ambient, 1, blue_ambi) ;
		} else if (color_cycle % 4 == 3) {
			glUniform4fv(diffuse, 1, yellow) ;
			glUniform4fv(ambient, 1, yellow_ambi) ;
		}

/* !!!
		mat4 sc(1.0), tr(1.0) ;
		sc = Transform::scale(sx,sy,1.0) ; 
		tr = Transform::translate(tx,ty,0.0) ;
		// Multiply the matrices, accounting for OpenGL and GLM.
		sc = glm::transpose(sc) ; tr = glm::transpose(tr) ;
		for (unsigned int i = 0; i < objects.size() ; i++) {
			//if(i == 1) switchShader(true);
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

			glUniform1i(isperturbed, false);
			
			float size = objSize[i] ;

			if (!objects[i].compare("teapot")) {
				glutSolidTeapot(size);
			} else if (!objects[i].compare("sphere")) {
				glutSolidSphere(size, tess, tess) ;
			} else if (!objects[i].compare("cube")) {
				glutSolidCube(size) ;
	*/
		float theta = (float) i * pi / 180.0f ;
		int j = i + angle_step ; // Determine the next vertex
		float theta2 = (float) j * pi / 180.0f ;
		glBegin(GL_TRIANGLES) ;
			glNormal3f(0.0, 0.0, 1.0) ;
			glVertex3f(0.0, 0.0, 0.0) ;
			glNormal3f(0.0, 0.0, 1.0) ;
			glVertex3f(wheel_radius * cos(theta), wheel_radius * sin(theta), 0.0) ;
			glNormal3f(0.0, 0.0, 1.0) ;
			glVertex3f(wheel_radius * cos(theta2), wheel_radius * sin(theta2), 0.0) ;
		glEnd() ;

		glUniform4fv(diffuse, 1, white) ;
		glUniform4fv(ambient, 1, gray_ambi) ;
		glPushMatrix() ;
			glTranslatef(base_radius * cos(theta), base_radius * sin(theta), stick_height / 2) ;
			glScalef(0.1, 0.1, 1.0) ;
			glutSolidCube(stick_height) ;
		glPopMatrix() ;

		color_cycle++ ;
	}
	glPopMatrix() ;

	// Draw the static board
	float startx = 0.0f ;
	float starty = half_room - block_size / 2 ;
	float startz = block_size * z_scale / 2 ;
	float xpos, ypos, zpos ;

	glUniform4fv(diffuse, 1, green) ;
	glUniform4fv(ambient, 1, green_ambi) ;
	glBindTexture (GL_TEXTURE_2D, texNames[0]) ; 
	glUniform1i(istex, texturing) ;
		glPushMatrix() ;
		for (int i = 0 ; i < 10 ; i++) {
			for (int j = 0 ; j < 4 ; j++) {
				if (j == 1 && (i != 0 && i != 8 && i != 9)) continue ;
				if (j == 2 && (i != 0 && i != 6 && i != 9)) continue ;
				xpos = startx + (float) i * (block_size + spacing) ;
				ypos = starty ;
				zpos = startz + (float) j * (block_size * z_scale + spacing) ;
				glPushMatrix() ;
					glTranslatef(xpos, ypos, zpos) ;
					glScalef(1.0, 1.0, z_scale) ;
					Shapes::cube(block_size) ;
				glPopMatrix() ;
			}
		}
		glPopMatrix() ;
	glUniform1i(istex, 0) ;
	
	// Increase the rotation on active blocks
	int inactive_count = 0 ;
	for (int i = 0; i < 14; i++) {
		if (block_activity[i]) {
			block_rotations[i] += block_velocity ;
			if (block_rotations[i] < -90) {
				block_rotations[i] = -90 ;
				block_activity[i] = false ;
			}
			if (block_rotations[i] > 0) {
				block_rotations[i] = 0 ;
				block_activity[i] = false ;
			}
		} else {
			inactive_count++ ;
		}
	}
	if (inactive_count == 14) {
		block_velocity = -block_speed ;
		board_ready = true ;
	}

	// Draw letter blocks
	int block_number = 0 ;
	for (int j = 2; j > 0; j--) {
		for (int i = 1; i < 9; i++) {
			if ((j == 1 && i == 8) || (j == 2 && i == 6)) continue ;
			xpos = startx + (float) i * (block_size + spacing) ;
			ypos = starty ;
			zpos = startz + (float) j * (block_size * z_scale + spacing) ;

			glPushMatrix() ;
				glTranslatef(xpos, ypos, zpos) ;
				glRotatef(block_rotations[block_number], 0.0, 0.0, 1.0) ;
				glScalef(1.0, 1.0, z_scale) ;
				glUniform4fv(diffuse, 1, white) ;
				glUniform4fv(ambient, 1, gray_ambi) ;
				glutSolidCube(block_size) ;
			glPopMatrix() ;

			glPushMatrix() ;
				glTranslatef(xpos, ypos, zpos) ; // Move center axis to blocks
				glRotatef(block_rotations[block_number], 0.0, 0.0, 1.0) ; // Rotate with the block
				glTranslatef(block_size / 2 + spacing / 4, 0.0, 0.0) ; // Translate to the right face of the block
				glRotatef(90.0f, 0.0f, 0.0f, 1.0f) ; // Rotate to face right
				glScalef(letter_scale * block_size, letter_scale * block_size, letter_scale * z_scale * block_size) ; // Scale first
				glUniform4fv(diffuse, 1, black) ;
				glUniform4fv(ambient, 1, black) ;
				char letter = block_letters[block_number] ;
				Shapes::printLetter(letter, true) ;
				glUniform4fv(diffuse, 1, white) ; // Same color as block
				glUniform4fv(ambient, 1, gray_ambi) ;
				Shapes::printLetter(letter, false) ;
			glPopMatrix() ;

			block_number++ ; // Move on to the next block
		}
	}

	// perturbed sphere
	float amb[4] = {0.2, 0.2, 0.2, 1.0};
	float dif[4] = {0.3, 0.1, 0.9, 1.0};
	float spec[4] = {0.6, 0.6, 0.6, 1.0};
	float ems[4] = {0.0, 0.0, 0.0, 1.0};
	float shn = 0.5;
	
	glUniform4fv(ambient,1,amb) ; 
	glUniform4fv(diffuse,1,dif) ; 
	glUniform4fv(specular,1,spec) ; 
	glUniform4fv(emission,1,ems) ;
	glUniform1fv(shininess,1,&shn) ; 
	glUniform1i(islight,true) ;
	glUniform1i(isperturbed, true);
			
	glPushMatrix() ;
			glTranslatef(1.90, -1.5, 0.5) ;
			glutSolidSphere(0.10, 200, 200) ;
	glPopMatrix() ;
	

	//switchShader(false);
	//obj.draw(0, 0, 1, 1);
	//raw.draw(1, 0, 0, 1);
	//raw2.draw(0, 1, 0, 1);
	//raw.alt_draw(&ambient, &diffuse, &specular, &emission, &shininess, &islight, &isperturbed);

	glutSwapBuffers();
	glFlush();
}

/**
 * Initialize the lighting variables.
 */
void initLights() {
	lighting = 1 ;
	texturing = 1 ;
	for (int n = 0; n < numLightsOn; n++) {
		for (int i = 0; i < 4; i++) {
				lightPosition[n][i] = base_lights[n][i] ;
				lightSpecular[n][i] = base_lights[n][i + 4] ;
		}
	}
}

/**
 * Initialize the viewing variables.
 */
void initView() {
	eye = eyeinit ; 
	up = upinit ; 
	center = centerinit ;
}

/**
 * Initialize movement variables.
 */
void initMovement() {
	forward_velocity = side_velocity = up_velocity = vec3(0.0) ;
	fb_speed = lr_speed = turn_speed = 0 ;
	move_center = vec3(0.0, 2.0, 1.0) ;
	align_flag = true ;
	aligned = true ; // Make sure this is true 
	viewing = false ;
	jumping = false ;
	for (int i = 0; i < 6; i++) key_press_arr[i] = false ;
	mouseoldx = mouseoldy = 0 ;
}

/**
 * Initialize game variables.
 */
void initGame() {
	block_velocity = 0 ;
	for (int i = 0; i < 14; i++) {
		block_activity[i] = false ;
		block_rotations[i] = 0 ;
	}
	wheel_angle = idle_angle = wheel_speed = 0.0f ;
	spinning = has_spun = false ;
	srand((unsigned) time(0)) ; // For RNG

	in_game = false ;
	board_ready = true ;
	total_score = spin_points = 0 ;
}

/**
 * Initialize GLUT functions.
 */
void initGlut() {
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseDrag);
	glutKeyboardFunc(keyboard);
	if (transop == view) glutKeyboardUpFunc(keyboardUp);
	glutIdleFunc(display) ; // Necessary for constant animation
	glutReshapeFunc(reshape);
	glutReshapeWindow(scene_width, scene_height);
}

/**
 * Initialize shader variables.
 */
void initShaders() {
	// glGenBuffers(numperobj*numobjects+ncolors+1, buffers) ; // 1 for texcoords 
    // initcolorscube() ; 
	// initobject(FLOOR, (GLfloat *) floorverts, sizeof(floorverts), (GLfloat *) floorcol, sizeof (floorcol), (GLubyte *) floorinds, sizeof (floorinds), GL_POLYGON) ; 
    // initobjectnocol(CUBE, (GLfloat *) cubeverts, sizeof(cubeverts), (GLubyte *) cubeinds, sizeof (cubeinds), GL_QUADS) ;
	fill_wiring = lighting = texturing = 1 ;
	inittexture(shaderprogram) ;
	
	lam_vertexshader = initshaders(GL_VERTEX_SHADER, "shaders/lam_light.vert.glsl") ;
    lam_fragmentshader = initshaders(GL_FRAGMENT_SHADER, "shaders/lam_light.frag.glsl") ;
	lam_shaderprogram = initprogram(lam_vertexshader, lam_fragmentshader) ;
    
    vertexshader = initshaders(GL_VERTEX_SHADER, "shaders/light.vert.glsl") ;
    fragmentshader = initshaders(GL_FRAGMENT_SHADER, "shaders/light.frag.glsl") ;
    shaderprogram = initprogram(vertexshader, fragmentshader) ; 
    
	islight = glGetUniformLocation(shaderprogram,"islight") ;
	isperturbed = glGetUniformLocation(shaderprogram,"isperturbed") ;        
	istex = glGetUniformLocation(shaderprogram, "istex") ;

	char name[20] ;
	for (int i = 0; i < 10; i++) {
		sprintf_s(name, "lightposn[%d]", i) ;
		lightposn[i] = glGetUniformLocation(shaderprogram, name) ;
		sprintf_s(name, "lightcolor[%d]", i) ;
		lightcolor[i] = glGetUniformLocation(shaderprogram, name) ;
	}
	lightcount = glGetUniformLocation(shaderprogram,"lightcount") ;
	ambient = glGetUniformLocation(shaderprogram,"ambient") ;           
	diffuse = glGetUniformLocation(shaderprogram,"diffuse") ;          
	specular = glGetUniformLocation(shaderprogram,"specular") ; 
	emission = glGetUniformLocation(shaderprogram,"emission") ; 
	shininess = glGetUniformLocation(shaderprogram,"shininess") ;   
}

void initImportObjects(){
	// initialize .obj reader
	obj.init("Anubis_alienado.obj");
	obj.moveToCenter();
	obj.scale(0.5, 0.5, 0.5);
	obj.rotate(90, vec3(1.0, 0.0, 0.0));
	obj.rotate(180, vec3(0.0, 0.0, 1.0));
	obj.translate(-1.0, 4.0, 0.55);

	// initialize .raw reader
	raw.init("guy.raw");
	raw.moveToCenter();
	raw.scale(0.00022, 0.00022, 0.00022);
	//raw.rotate(90, vec3(1, 0, 0));
	raw.translate(1.8, -2.9, 0.77);

	//raw2.init("guy.raw");
	//raw2.moveToCenter();
	//raw2.scale(0.00022, 0.00022, 0.00022);
	//raw.rotate(90, vec3(1, 0, 0));
	//raw2.translate(2, -2, 0.7);
}

/**
 * Initialize all the necessary variables.
 */
void init() {

	glEnable(GL_DEPTH_TEST) ;
	glDepthFunc(GL_LESS) ;
	
	initLights() ;
	initView() ;
	initMovement() ;
	initGame() ;
	initShaders() ;
	initImportObjects() ;
	initGlut() ;
	printHelp() ;
}

/**
 * Main function.
 */
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("HW3: TV Game Show");
	GLenum err = glewInit() ; 
	init();
	/* !!!
	parse(argv[1]);
	glutDisplayFunc(display);
	glutSpecialFunc(specialKey);
	// glutKeyboardFunc(keyboard);

	// MICE
	glutMouseFunc(mouse);
	glutMotionFunc(mousedrag);
	// MICE

	// CONTROL
	if(alt_controls){
		glutKeyboardFunc(altKeyboard);
	}else{
		glutKeyboardFunc(keyboard);
	}

	glutReshapeFunc(reshape);
	glutReshapeWindow(600, 400);
	printHelp();
	*/
	glutMainLoop();
	return 0;
}
