// QPrint.cpp: Implementation of QPrint class.

#include <iostream>
#include <string>
#include "QPrint.h"

void QPrint::v3p(std::string msg, glm::vec3 input) {
	std::cout << msg << input[0] << " " << input[1] << " " << input[2] << std::endl ;
}

float QPrint::magv(glm::vec3 input) {
	return sqrt(pow(input[0], 2) + pow(input[1], 2) + pow(input[2], 2)) ;
}

QPrint::QPrint()
{

}

QPrint::~QPrint()
{

}