// QPrint header file.
// This class contains static methods for printing
// array and vector elements to output.

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class QPrint 
{
public:
	QPrint();
	virtual ~QPrint();
	static void v3p(std::string msg, glm::vec3 input);
};