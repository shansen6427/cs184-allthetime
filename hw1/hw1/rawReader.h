/**
 * rawReader reads and renders .raw files (well, some of them, anyway)
 */

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

typedef glm::vec3 vec3 ;

class rawReader
{
public:
	rawReader();
	int init(const char* filename);
	void draw(const float &red, const float &green, const float &blue, const float &alpha);
	void alt_draw(void* ambient, void* diffuse, void* specular, void* emission, void* shininess, void* islight, void* isperturbed);
	void moveToCenter();
	void rotate(const float degrees, const vec3& axis) ;
    void scale(const float &sx, const float &sy, const float &sz) ; 
    void translate(const float &tx, const float &ty, const float &tz);
private:
	std::vector<vec3> vertices;
};