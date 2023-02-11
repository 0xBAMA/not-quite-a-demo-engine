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

	// orientation gizmo from Voraldo13
	orientTrident trident;

//====== OpenGL ===============================================================
	GLuint displayVAO;
	GLuint displayVBO;

	// resource management
	unordered_map< string, GLuint > textures;
	unordered_map< string, GLuint > shaders;
	unordered_map< string, bindSet > bindSets;

//====== tonemapping parameters + adjustment ==================================
	colorGradeParameters tonemap;
	void TonemapControlsWindow ();
	void SendTonemappingParameters ();

//====== initialization =======================================================
	void StartBlock ( string sectionName );
	void EndBlock ();
	void Init ();
	void StartMessage ();
	void LoadConfig ();
	void CreateWindowAndContext ();
	void DisplaySetup ();
	void SetupVertexData ();
	void SetupTextureData ();
	void ShaderCompile ();
	void LoadData ();
	void ImguiSetup ();
	void InitialClear ();
	void ReportStartupStats ();

//====== main loop functions ==================================================
	void BlitToScreen ();
	void HandleEvents ();
	void ClearColorAndDepth ();
	void DrawAPIGeometry ();
	void ComputePasses ();
	void ImguiPass ();
	void ImguiFrameStart ();
	void ImguiFrameEnd ();
	void DrawTextEditor ();
	void MenuLayout ( bool* open );
	void QuitConf ( bool* open );

//====== shutdown procedures ==================================================
	// shutdown procedures
	void ImguiQuit ();
	void SDLQuit ();
	void Quit ();

//====== program flags ========================================================
	bool quitConfirm = false;
	bool pQuit = false;

};
#endif
