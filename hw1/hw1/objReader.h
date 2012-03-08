/**
 * objReader reads and renders? .obj files
 */

#include <vector>
//#include "transform.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

typedef glm::vec3 vec3 ;

class objReader
{
public:
	objReader();
	int init(const char* filename);
	void draw();
	void moveToCenter();
	void rotate(const float degrees, const vec3& axis) ;
    void scale(const float &sx, const float &sy, const float &sz) ; 
    void translate(const float &tx, const float &ty, const float &tz);
private:
	std::vector<vec3> vertices;
	std::vector<std::vector<int>> faces;
};