#ifndef ENGINE
#define ENGINE

#include "includes.h"

class engine
{
public:

	engine();
	~engine();

private:

	SDL_Window * window;
	SDL_GLContext GLcontext;

	ImVec4 clear_color;


    GLuint display_texture;
    GLuint display_shader;
	GLuint display_vao;
	GLuint display_vbo;

	int total_screen_width, total_screen_height;

	void create_window();
	void gl_setup();
	void draw_everything();

	void load_OBJ(std::string filename);

	void quit();
	void quit_conf(bool *open);
		
	bool quitconfirm = false;
	bool pquit = false;

public:
//placeholder
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
