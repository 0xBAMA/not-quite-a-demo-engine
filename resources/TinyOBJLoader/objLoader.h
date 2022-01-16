#ifndef OBJLOAD
#define OBJLOAD

#include "tiny_obj_loader.h"
#include "../engineCode/includes.h"

class objLoader {
public:
	objLoader(){}
	objLoader( std::string filename ){
		LoadOBJ( filename );
	}

	void LoadOBJ(std::string filename);

	// OBJ data (per mesh)
	// this may vary in length
	std::vector<glm::vec4> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> texcoords;

	// these should all be the same length, the number of triangles
	std::vector<glm::ivec3> triangle_indices;
	std::vector<glm::ivec3> normal_indices;
	std::vector<glm::ivec3> texcoord_indices;
};

#endif
