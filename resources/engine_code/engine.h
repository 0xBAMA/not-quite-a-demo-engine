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

	void quit();
	void quit_conf(bool *open);
		
	bool quitconfirm = false;
	bool pquit = false;

};

#endif
