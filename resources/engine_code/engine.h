#ifndef ENGINE
#define ENGINE

#include "includes.h"

class engine {
public:
	engine()  { init(); }
	~engine() { quit(); }

  // called from main
  bool mainLoop();

private:
  // application handles + basic data
	SDL_Window * window;
	SDL_GLContext GLcontext;
  int totalScreenWidth, totalScreenHeight;
	ImVec4 clearColor;

  // OpenGL data
  GLuint displayTexture;
  GLuint displayShader;
	GLuint displayVAO;
	GLuint displayVBO;
  // objLoader o; // wrapper for TinyOBJLoader

  // initialization
  void init();
  void startMessage();
	void createWindowAndContext();
  void displaySetup();
  void computeShaderCompile();
  void imguiSetup();

  // main loop functions
  void imguiFrameStart();
  void drawTextEditor();
  void handleEvents();
  void quitConf( bool *open );
  void imguiFrameEnd();

  // shutdown procedures
  void imguiQuit();
  void SDLQuit();
	void quit();

  // program flags
	bool quitConfirm = false;
	bool pQuit = false;

};

#endif
