#ifndef ENGINE
#define ENGINE
#include "includes.h"

class engine {
public:
	engine()  { Init(); }
	~engine() { Quit(); }

	bool MainLoop (); // called from main

private:
	// application handles + basic data
	// windowHandler w; // this was partially implemented in Voraldo13, consider bringing that over
	SDL_Window * window;
	SDL_GLContext GLcontext;

	// loaded from config.json
	configData config;

	// text renderer framework
	layerManager textRenderer;

	// keyboard input management
	// inputHandler keyboard;

	// OpenGL data
	GLuint blueNoiseTexture;
	GLuint accumulatorTexture;
	GLuint displayTexture;
	GLuint displayShader;
	GLuint displayVAO;
	GLuint dummyDrawShader;
	GLuint tonemapShader;

	// tonemapping parameters + adjustment
	colorGradeParameters tonemap;
	void TonemapControlsWindow ();
	void SendTonemappingParameters ();

	// initialization
	void Init ();
	void StartMessage ();
	void LoadConfig ();
	void CreateWindowAndContext ();
	void DisplaySetup ();
	void ShaderCompile ();
	void ImguiSetup ();

	// main loop functions
	void BlitToScreen ();
	void HandleEvents ();
	void ClearColorAndDepth ();
	void ComputePasses ();
	void ImguiPass ();
	void ImguiFrameStart ();
	void ImguiFrameEnd ();
	void DrawTextEditor ();
	void MenuLayout ( bool* open );
	void QuitConf ( bool* open );

	// shutdown procedures
	void ImguiQuit ();
	void SDLQuit ();
	void Quit ();

	// program flags
	bool quitConfirm = false;
	bool pQuit = false;
};
#endif
