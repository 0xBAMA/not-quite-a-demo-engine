#ifndef ENGINE
#define ENGINE

#include "includes.h"

class engine {
public:
	engine()  { init(); }
	~engine() { quit(); }

  bool mainLoop(); // called from main

private:
  // application handles + basic data
	// windowHandler w;
	SDL_Window * window;
	SDL_GLContext GLcontext;
  int totalScreenWidth, totalScreenHeight;
	ImVec4 clearColor;

  // OpenGL data
  GLuint displayTexture;
  GLuint displayShader;
  GLuint displayVAO;

  // initialization
  void init();
  void startMessage();
	void createWindowAndContext();
  void displaySetup();
  void computeShaderCompile();
  void imguiSetup();

  // main loop functions
  void mainDisplay();
  void handleEvents();
  void clear();
  void imguiPass();
  void imguiFrameStart();
  void imguiFrameEnd();
  void drawTextEditor();
  void quitConf( bool *open );

  // shutdown procedures
  void imguiQuit();
  void SDLQuit();
	void quit();

  // program flags
	bool quitConfirm = false;
	bool pQuit = false;

};

#endif
