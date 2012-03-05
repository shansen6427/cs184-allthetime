/**
 * objReader reads and renders? .obj files
 */

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

typedef glm::vec3 vec3 ;

class objReader
{
public:
	objReader();
	int init(const char* filename);
	void draw();
private:
	std::vector<vec3> vertices;
	std::vector<vec3> faces;
}