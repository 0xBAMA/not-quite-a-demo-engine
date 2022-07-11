#ifndef ENGINE
#define ENGINE

#include "includes.h"

class engine {
public:
	engine()  { Init(); }
	~engine() { Quit(); }

	bool MainLoop(); // called from main

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
	void Init ();
	void StartMessage ();
	void CreateWindowAndContext ();
	void DisplaySetup ();
	void ComputeShaderCompile ();
	void ImguiSetup ();

	// main loop functions
	void MainDisplay ();
	void HandleEvents ();
	void Clear ();
	void ImguiPass ();
	void ImguiFrameStart ();
	void ImguiFrameEnd ();
	void DrawTextEditor ();
	void QuitConf ( bool *open );

	// shutdown procedures
	void ImguiQuit ();
	void SDLQuit();
	void Quit();

	// program flags
	bool quitConfirm = false;
	bool pQuit = false;

};

#endif
