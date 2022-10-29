#include "engine.h"

void engine::StartMessage () {
	cout << endl << T_YELLOW << BOLD << "NQADE - Not Quite A Demo Engine" << newline;
	cout << " By Jon Baker ( 2020 - 2022 ) " << RESET << newline;
	cout << "  https://jbaker.graphics/ " << newline << newline;
}

void engine::CreateWindowAndContext () {
	cout << T_BLUE << "    Initializing SDL2" << RESET << " ................................ ";
	if ( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
		cout << "Error: " << SDL_GetError() << newline;

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER,       1 );
	SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 );
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE,           8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE,         8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE,          8 );
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE,         8 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE,        24 );
	SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE,       8 );
	SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, MSAACount );


	cout << T_GREEN << "done." << RESET << newline;

	cout << T_BLUE << "    Creating window" << RESET << " .................................. ";

	// prep for window creation
	int flags;
	SDL_DisplayMode dm;
	SDL_GetDesktopDisplayMode( 0, &dm );

	// different window configurations
	int windowInitMode = 0;
	switch ( windowInitMode ) {
		case 0: // little window, using WIDTH/HEIGHT defines in includes.h
			flags = SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE;
			totalScreenWidth = WIDTH;
			totalScreenHeight = HEIGHT;
			window = SDL_CreateWindow( "NQADE", 0, 0, WIDTH, HEIGHT, flags );
			break;

		case 1: // fullscreen borderless
			// first, query the screen resolution
			totalScreenWidth = dm.w;
			totalScreenHeight = dm.h;
			flags = SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN | SDL_WINDOW_BORDERLESS;
			window = SDL_CreateWindow( "NQADE", 0, 0, dm.w, dm.h, flags );
			break;

		case 2: // borderless floating
			totalScreenWidth = dm.w - 100;
			totalScreenHeight = dm.h - 100;
			flags = SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN | SDL_WINDOW_BORDERLESS;
			window = SDL_CreateWindow( "NQADE", 50, 50, totalScreenWidth, totalScreenHeight, flags );
			break;

			// other modes?
	}

	// if init takes some time, don't show the window before it's done
	SDL_ShowWindow( window );

	cout << T_GREEN << "done." << RESET << newline;

	cout << T_BLUE << "    Setting up OpenGL context" << RESET << " ........................ ";
	// initialize OpenGL 4.3 + GLSL version 430
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_FLAGS, 0 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
	GLcontext = SDL_GL_CreateContext( window );
	SDL_GL_MakeCurrent( window, GLcontext );

	SDL_GL_SetSwapInterval( 1 ); // Enable vsync
	// SDL_GL_SetSwapInterval( 0 ); // Disables vsync

	// load OpenGL functions
	if ( gl3wInit() != 0 ) { cout << "Failed to initialize OpenGL loader!" << newline; abort(); }

	// basic OpenGL Config
	// glEnable( GL_DEPTH_TEST );
	// glEnable( GL_LINE_SMOOTH );
	// glPointSize( 3.0 );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	cout << T_GREEN << "done." << RESET << newline;

	struct modelBatch {
		std::vector< string > objModel;
		std::vector< string > texPaths;
	};

	std::vector< modelBatch > baseModels;

	for ( const std::filesystem::directory_entry& file : std::filesystem::recursive_directory_iterator( "../SimulationMode/HighLoD" ) ) {
		std::stringstream fn;
		fn << file;
		string fileName = fn.str();
		// trimming quotes
		if ( !fileName.empty() ) fileName.pop_back();
		fileName.erase( 0, 1 );
		if ( file.is_directory() ) {
			modelBatch m;
			for ( const std::filesystem::directory_entry& fileInner : std::filesystem::recursive_directory_iterator( file ) ) {
				if ( !fileInner.is_directory() ) {
					if ( fileInner.path().extension().string() == ".png" ) {
						m.texPaths.push_back( fileInner.path().string() );

					} else if ( fileInner.path().extension().string() == ".TGA" ) {
						// std::filesystem::path fileInnerE = fileInner;
						// cout << "convert " << fileInner.path().string() << " " <<
						// 	fileInnerE.replace_extension( ".png" ).string() << newline;

					} else if ( fileInner.path().extension().string() == ".OBJ" ) {
						m.objModel.push_back( fileInner.path().string() );

					} else {
						cout << "unexpected extension: " << fileInner.path().string() << newline;

					}
				}
			}
			baseModels.push_back( m );
		}
	}

	// then we can iterate through and generate previews
	const mat3 baseTransform =
		rotation( vec3( 1.0f, 0.0f, 0.0f ), pi / 4.0f ) *
		glm::mat3( 0.0001618f );
		// rotation( vec3( 1.0f, 0.0f, 1.0f ), 2.2f ) *
		// rotation( vec3( 1.0f, 1.0f, 0.0f ), 1.1f ) *
		// rotation( vec3( 0.0f, 1.0f, 0.0f ), 2.3f ) *


	// for  ( auto& modelBase : baseModels ) {
	// 	for ( auto& texx : modelBase.texPaths ) {
	//
			SoftRast s( 8000, 8000 );
			// cout << "model with " << modelBase.objModel[ 0 ] << " and tex " << texx << newline;



			std::random_device rng;
			std::seed_seq seedSeq{ rng(), rng(), rng(), rng(), rng(), rng(), rng(), rng(), rng() };
			auto generator = std::mt19937_64( seedSeq );
			std::uniform_real_distribution< float > rotA( -0.3f, 0.3f );
			std::uniform_real_distribution< float > rotB( -1.1f, 1.1f );
			std::uniform_int_distribution< int > carPick( 0, baseModels.size() - 1 );

			for ( int i = 0; i < 100000; i++ ) {
				int pick = carPick( generator );
				std::uniform_int_distribution< int > texPick( 0, baseModels[ pick ].texPaths.size() - 1 );

				mat3 transform =
					rotation( vec3( 1.0f, 0.0f, 0.0f ), rotA( generator ) ) *
					rotation( vec3( 0.0f, 1.0f, 0.0f ), rotA( generator ) ) *
					rotation( vec3( 0.0f, 0.0f, 1.0f ), rotB( generator ) * 2.2f ) *
					baseTransform;

				vec3 offset = vec3( rotB( generator ), rotB( generator ), rotB( generator ) );


				Tick();
				s.DrawModel( baseModels[ pick ].objModel[ 0 ], baseModels[ pick ].texPaths[ texPick( generator ) ], transform, offset );
				cout << Tock() << " to render" << newline << newline;
			}








	// 		// Image depthOutput( 640, 640 );
	// 		// for ( uint32_t x = 0; x < depthOutput.width; x++ ) {
	// 		// 	for ( uint32_t y = 0; y < depthOutput.height; y++ ) {
	// 		// 		float d = s.Depth.GetAtXY( x, y ).r;
	// 		// 		uint8_t writeVal = uint8_t( RemapRange( d, -1.0f, 1.0f, 0.0f, 255.0f ) );
	// 		// 		depthOutput.SetAtXY( x, y, { writeVal, writeVal, writeVal, 255 } );
	// 		// 	}
	// 		// }
	//
	// 		// depthOutput.Save( "testDepth.png" );
	//
	// 		string parent = std::filesystem::path( texx ).parent_path().string();
	// 		parent = parent.substr( parent.find_last_of( "/" ) + 1 );
	// 		string file = texx.substr( texx.find_last_of( "/" ) + 1 );
	// 		s.Color.Save( "../SimulationMode/PreviewWireframe/" + parent + "_" + file );

			s.Color.Save( "test.png" );

	// 	}
	// }




}

void engine::DisplaySetup () {
	// some info on your current platform
	const GLubyte *renderer = glGetString( GL_RENDERER );	// get renderer string
	const GLubyte *version = glGetString( GL_VERSION );	// version as a string
	const GLubyte *glslVersion = glGetString( GL_SHADING_LANGUAGE_VERSION );	// glsl version as a string
	const GLubyte *vendor = glGetString( GL_VENDOR );		// vendor as a string

	cout << T_BLUE << "    Platform Info :" << RESET << newline;
	cout << T_RED << "      Vendor : " << T_CYAN << vendor << RESET << newline;
	cout << T_RED << "      Renderer : " << T_CYAN << renderer << RESET << newline;
	cout << T_RED << "      OpenGL version supported : " << T_CYAN << version << RESET << newline;
	cout << T_RED << "      GLSL version supported : " << T_CYAN << glslVersion << RESET << newline << newline;

	// create the shader for the triangles to cover the screen
	displayShader = regularShader( "resources/engineCode/shaders/blit.vs.glsl", "resources/engineCode/shaders/blit.fs.glsl" ).shaderHandle;

	// have to have dummy call to this - OpenGL core spec requires a VAO bound when calling glDrawArrays, otherwise it complains
	glGenVertexArrays( 1, &displayVAO );

	// create the image textures
	Image initial( WIDTH, HEIGHT, true );
	glGenTextures( 1, &accumulatorTexture );
	glActiveTexture( GL_TEXTURE3 );
	glBindTexture( GL_TEXTURE_2D, accumulatorTexture );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, WIDTH, HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, &initial.data.data()[ 0 ] );

	glGenTextures( 1, &displayTexture );
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, displayTexture );
	bool linearFilter = true;
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, linearFilter ? GL_LINEAR : GL_NEAREST );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, linearFilter ? GL_LINEAR : GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, WIDTH, HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, &initial.data.data()[ 0 ] );

	// blue noise image on the GPU
	Image blueNoiseImage{ "resources/noise/blueNoise.png", LODEPNG };
	glGenTextures( 1, &blueNoiseTexture );
	glActiveTexture( GL_TEXTURE4 );
	glBindTexture( GL_TEXTURE_2D, blueNoiseTexture );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, blueNoiseImage.width, blueNoiseImage.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &blueNoiseImage.data.data()[ 0 ] );
}

void engine::ComputeShaderCompile () {
	// initialize the text renderer
	textRenderer.Init( WIDTH, HEIGHT, computeShader( "resources/fonts/fontRenderer/font.cs.glsl" ).shaderHandle );

	// something to put data in the accumulator texture
	dummyDrawShader = computeShader( "resources/engineCode/shaders/dummyDraw.cs.glsl" ).shaderHandle;

	// tonemapping shader
	tonemapShader = computeShader( "resources/engineCode/shaders/tonemap.cs.glsl" ).shaderHandle;
}


void engine::ImguiSetup () {
	cout << T_BLUE << "    Configuring dearImGUI" << RESET << " ............................ ";

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();

	// enable docking
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	// Setup Platform/Renderer bindings
	ImGui_ImplSDL2_InitForOpenGL( window, GLcontext );
	const char *glsl_version = "#version 430";
	ImGui_ImplOpenGL3_Init( glsl_version );

	// initial value for clear color
	// clearColor = ImVec4( 0.295f, 0.295f, 0.295f, 0.5f );
	clearColor = ImVec4( 0.0f, 0.0f, 0.0f, 1.0f );
	glClearColor( clearColor.x, clearColor.y, clearColor.z, clearColor.w );
	glClear( GL_COLOR_BUFFER_BIT );
	SDL_GL_SwapWindow( window ); // show clear color

	// setting custom font, if desired
	// io.Fonts->AddFontFromFileTTF( "resources/fonts/star_trek/titles/TNG_Title.ttf", 16 );

	ImGui::StyleColorsDark();
	ImVec4 *colors = ImGui::GetStyle().Colors;

	colors[ ImGuiCol_Text ]
		= ImVec4( 0.64f, 0.37f, 0.37f, 1.00f );
	colors[ ImGuiCol_TextDisabled ]
		= ImVec4( 0.49f, 0.26f, 0.26f, 1.00f );
	colors[ ImGuiCol_WindowBg ]
		= ImVec4( 0.17f, 0.00f, 0.00f, 0.98f );
	colors[ ImGuiCol_ChildBg ]
		= ImVec4( 0.00f, 0.00f, 0.00f, 0.00f );
	colors[ ImGuiCol_PopupBg ]
		= ImVec4( 0.18f, 0.00f, 0.00f, 0.94f );
	colors[ ImGuiCol_Border ]
		= ImVec4( 0.35f, 0.00f, 0.03f, 0.50f );
	colors[ ImGuiCol_BorderShadow ]
		= ImVec4( 0.00f, 0.00f, 0.00f, 0.00f );
	colors[ ImGuiCol_FrameBg ]
		= ImVec4( 0.14f, 0.04f, 0.00f, 1.00f );
	colors[ ImGuiCol_FrameBgHovered ]
		= ImVec4( 0.14f, 0.04f, 0.00f, 1.00f );
	colors[ ImGuiCol_FrameBgActive ]
		= ImVec4( 0.14f, 0.04f, 0.00f, 1.00f );
	colors[ ImGuiCol_TitleBg ]
		= ImVec4( 0.14f, 0.04f, 0.00f, 1.00f );
	colors[ ImGuiCol_TitleBgActive ]
		= ImVec4( 0.14f, 0.04f, 0.00f, 1.00f );
	colors[ ImGuiCol_TitleBgCollapsed ]
		= ImVec4( 0.00f, 0.00f, 0.00f, 0.51f );
	colors[ ImGuiCol_MenuBarBg ]
		= ImVec4( 0.14f, 0.14f, 0.14f, 1.00f );
	colors[ ImGuiCol_ScrollbarBg ]
		= ImVec4( 0.02f, 0.02f, 0.02f, 0.53f );
	colors[ ImGuiCol_ScrollbarGrab ]
		= ImVec4( 0.31f, 0.31f, 0.31f, 1.00f );
	colors[ ImGuiCol_ScrollbarGrabHovered ]
		= ImVec4( 0.41f, 0.41f, 0.41f, 1.00f );
	colors[ ImGuiCol_ScrollbarGrabActive ]
		= ImVec4( 0.51f, 0.51f, 0.51f, 1.00f );
	colors[ ImGuiCol_CheckMark ]
		= ImVec4( 0.87f, 0.23f, 0.09f, 1.00f );
	colors[ ImGuiCol_SliderGrab ]
		= ImVec4( 0.87f, 0.23f, 0.09f, 1.00f );
	colors[ ImGuiCol_SliderGrabActive ]
		= ImVec4( 1.00f, 0.33f, 0.00f, 1.00f );
	colors[ ImGuiCol_Button ]
		= ImVec4( 0.81f, 0.38f, 0.09f, 0.08f );
	colors[ ImGuiCol_ButtonHovered ]
		= ImVec4( 0.87f, 0.23f, 0.09f, 1.00f );
	colors[ ImGuiCol_ButtonActive ]
		= ImVec4( 1.00f, 0.33f, 0.00f, 1.00f );
	colors[ ImGuiCol_Header ]
		= ImVec4( 0.81f, 0.38f, 0.09f, 0.08f );
	colors[ ImGuiCol_HeaderHovered ]
		= ImVec4( 0.87f, 0.23f, 0.09f, 1.00f );
	colors[ ImGuiCol_HeaderActive ]
		= ImVec4( 1.00f, 0.33f, 0.00f, 1.00f );
	colors[ ImGuiCol_Separator ]
		= ImVec4( 0.81f, 0.38f, 0.09f, 0.08f );
	colors[ ImGuiCol_SeparatorHovered ]
		= ImVec4( 0.87f, 0.23f, 0.09f, 1.00f );
	colors[ ImGuiCol_SeparatorActive ]
		= ImVec4( 1.00f, 0.33f, 0.00f, 1.00f );
	colors[ ImGuiCol_ResizeGrip ]
		= ImVec4( 0.81f, 0.38f, 0.09f, 0.08f );
	colors[ ImGuiCol_ResizeGripHovered ]
		= ImVec4( 0.87f, 0.23f, 0.09f, 1.00f );
	colors[ ImGuiCol_ResizeGripActive ]
		= ImVec4( 1.00f, 0.33f, 0.00f, 1.00f );
	colors[ ImGuiCol_Tab ]
		= ImVec4( 0.81f, 0.38f, 0.09f, 0.08f );
	colors[ ImGuiCol_TabHovered ]
		= ImVec4( 0.87f, 0.23f, 0.09f, 1.00f );
	colors[ ImGuiCol_TabActive ]
		= ImVec4( 1.00f, 0.33f, 0.00f, 1.00f );
	colors[ ImGuiCol_TabUnfocused ]
		= ImVec4( 0.81f, 0.38f, 0.09f, 0.08f );
	colors[ ImGuiCol_TabUnfocusedActive ]
		= ImVec4( 0.81f, 0.38f, 0.09f, 0.08f );
	colors[ ImGuiCol_PlotLines ]
		= ImVec4( 0.61f, 0.61f, 0.61f, 1.00f );
	colors[ ImGuiCol_PlotLinesHovered ]
		= ImVec4( 1.00f, 0.43f, 0.35f, 1.00f );
	colors[ ImGuiCol_PlotHistogram ]
		= ImVec4( 0.90f, 0.70f, 0.00f, 1.00f );
	colors[ ImGuiCol_PlotHistogramHovered ]
		= ImVec4( 1.00f, 0.60f, 0.00f, 1.00f );
	colors[ ImGuiCol_TextSelectedBg ]
		= ImVec4( 0.81f, 0.38f, 0.09f, 0.08f );
	colors[ ImGuiCol_DragDropTarget ]
		= ImVec4( 1.00f, 1.00f, 0.00f, 0.90f );
	colors[ ImGuiCol_NavHighlight ]
		= ImVec4( 1.00f, 0.60f, 0.00f, 1.00f );
	colors[ ImGuiCol_NavWindowingHighlight ]
		= ImVec4( 1.00f, 1.00f, 1.00f, 0.70f );
	colors[ ImGuiCol_NavWindowingDimBg ]
		= ImVec4( 0.80f, 0.80f, 0.80f, 0.20f );
	colors[ ImGuiCol_ModalWindowDimBg ]
		= ImVec4( 0.80f, 0.80f, 0.80f, 0.35f );

	cout << T_GREEN << "done." << RESET << newline << newline;
}
