#include "engine.h"

void engine::StartMessage () {
	cout << endl << T_YELLOW << BOLD << "NQADE - Not Quite A Demo Engine" << newline;
	cout << " By Jon Baker ( 2020 - 2022 ) " << RESET << newline;
	cout << "  https://jbaker.graphics/ " << newline << newline;
}

void engine::LoadConfig () {
	cout << T_BLUE << "    Configuring Application" << RESET << " ................... ";
	json j;
	// load the config json, populate config struct - this will probably have more data, eventually
	ifstream i( "resources/engineCode/config.json" );
	i >> j; i.close();
	config.width = j[ "screenWidth" ];
	config.height = j[ "screenHeight" ];
	config.windowOffset.x = j[ "windowOffset" ][ "x" ];
	config.windowOffset.y = j[ "windowOffset" ][ "y" ];
	config.startOnScreen = j[ "startOnScreen" ];

	config.windowFlags |= ( j[ "SDL_WINDOW_FULLSCREEN" ] ? SDL_WINDOW_FULLSCREEN : 0 );
	config.windowFlags |= ( j[ "SDL_WINDOW_FULLSCREEN_DESKTOP" ] ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0 );
	config.windowFlags |= ( j[ "SDL_WINDOW_BORDERLESS" ] ? SDL_WINDOW_BORDERLESS : 0 );
	config.windowFlags |= ( j[ "SDL_WINDOW_RESIZABLE" ] ? SDL_WINDOW_RESIZABLE : 0 );
	config.windowFlags |= ( j[ "SDL_WINDOW_INPUT_GRABBED" ] ? SDL_WINDOW_INPUT_GRABBED : 0 );
	config.vSyncEnable = j[ "vSyncEnable" ];
	config.MSAACount = j[ "MSAACount" ];
	config.OpenGLVersionMajor = j[ "OpenGLVersionMajor" ];
	config.OpenGLVersionMinor = j[ "OpenGLVersionMinor" ];

	config.clearColor.r = j[ "clearColor" ][ "r" ];
	config.clearColor.g = j[ "clearColor" ][ "g" ];
	config.clearColor.b = j[ "clearColor" ][ "b" ];
	config.clearColor.a = j[ "clearColor" ][ "a" ];

	cout << T_GREEN << "done." << RESET << newline;
}

void engine::CreateWindowAndContext () {
	cout << T_BLUE << "    Initializing SDL2" << RESET << " ......................... ";
	if ( SDL_Init( SDL_INIT_EVERYTHING ) != 0 ) {
		cout << "Error: " << SDL_GetError() << newline;
	}
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER,       1 );
	SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 );
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE,           8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE,         8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE,          8 );
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE,         8 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE,        24 );
	SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE,       8 );
	// multisampling AA, for edges when evaluating API geometry
	if ( config.MSAACount > 1 ) {
		SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1 );
		SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, config.MSAACount );
	}
	cout << T_GREEN << "done." << RESET << newline;
	cout << T_BLUE << "    Creating Window" << RESET << " ........................... ";

	// prep for window creation
	SDL_DisplayMode displayMode;
	SDL_GetDesktopDisplayMode( 0, &displayMode );
// different window configurations - this needs work, I don't like this switch statement at all
//	use displayMode dimension for either value set to -1 ( width or height ), or negative to do displayMode.val - config.val? tbd

	// always need OpenGL, always start hidden till init finishes
	config.windowFlags |= SDL_WINDOW_OPENGL;
	config.windowFlags |= SDL_WINDOW_HIDDEN;
	// todo: offset so that it starts on the selected screen, config.startOnScreen ( bump by n * screenWidth )
	window = SDL_CreateWindow( config.windowTitle.c_str(), config.windowOffset.x + config.startOnScreen * displayMode.w, config.windowOffset.y, config.width, config.height, config.windowFlags );

	cout << T_GREEN << "done." << RESET << newline;
	cout << T_BLUE << "    Setting Up OpenGL Context" << RESET << " ................. ";
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_FLAGS, 0 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
	// defaults to OpenGL 4.3
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, config.OpenGLVersionMajor );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, config.OpenGLVersionMinor );
	GLcontext = SDL_GL_CreateContext( window );
	SDL_GL_MakeCurrent( window, GLcontext );

	// config vsync enable/disable
	SDL_GL_SetSwapInterval( config.vSyncEnable ? 1 : 0 );

	// load OpenGL functions
	if ( gl3wInit() != 0 ) { cout << "Failed to Initialize OpenGL Loader!" << newline; abort(); }

	// basic OpenGL Config
	glEnable( GL_DEPTH_TEST );
	// glEnable( GL_LINE_SMOOTH );
	// glPointSize( 3.0 );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	cout << T_GREEN << "done." << RESET << newline;
}

void engine::DisplaySetup () {
	// some info on your current platform
	cout << T_BLUE << "    Platform Info :" << RESET << newline;
	const GLubyte *vendor = glGetString( GL_VENDOR );
	cout << T_RED << "      Vendor : " << T_CYAN << vendor << RESET << newline;
	const GLubyte *renderer = glGetString( GL_RENDERER );
	cout << T_RED << "      Renderer : " << T_CYAN << renderer << RESET << newline;
	const GLubyte *version = glGetString( GL_VERSION );
	cout << T_RED << "      OpenGL Version Supported : " << T_CYAN << version << RESET << newline;
	const GLubyte *glslVersion = glGetString( GL_SHADING_LANGUAGE_VERSION );
	cout << T_RED << "      GLSL Version Supported : " << T_CYAN << glslVersion << RESET << newline << newline;



	cout << T_BLUE << "    Setting Up Vertex Data" << RESET << " .................... ";






	SoftRast s ( 3000, 3000 );
	s.LoadModel( "../otherFolks/Sponza/sponza.obj", "../otherFolks/Sponza/" );
	// s.DrawModel( rotation( vec3( 0.0f, 0.0f, 1.0f ), pi ) * mat3( 0.0005f ) );
	// s.DrawModelWireframe( rotation( vec3( 0.0f, 0.0f, 1.0f ), pi ) * mat3( 0.0005f ) );
	// s.Color.Save( "test.png" );
	cout << "loaded " << s.triangles.size() << " triangles" << newline;

	// set up vertex buffers, with all the triangle data - vertex colors are defaulted, not specified in the input
		// position
	std::vector<vec3> positions;
		// texcoord
	std::vector<vec3> texCoords;
		// normal
	std::vector<vec3> normals;

	// I want to try using array textures for texturing
		// this is going to involve resizing the texture maps to a constant size
			// I think that this makes the most sense as 2048x2048, because I have VRAM to burn, and I can use stb_image_resize
			// to make the smaller textures match ( 256x256, 512x512, 1024x1024 ) - I can't find anywhere that says that array
			// textures must all use the same resolution, but they get loaded with glTexImage3D, so I'm kind of assuming that's
			// at least the intended usage
		// then, once they're of uniform size, pack them all into one big buffer, and pass it
		// I want to interleave the normal maps, too, so that'll be diffuse, normal, diffuse, normal...
			// they are already ordered this way in s.texSet

	for ( auto& triangle : s.triangles ) {
		positions.push_back( triangle.p0 );
		positions.push_back( triangle.p1 );
		positions.push_back( triangle.p2 );

		texCoords.push_back( triangle.t0 );
		texCoords.push_back( triangle.t1 );
		texCoords.push_back( triangle.t2 );

		normals.push_back( triangle.n0 );
		normals.push_back( triangle.n1 );
		normals.push_back( triangle.n2 );

		sponzaNumTriangles++;
	}

	// send the data, set up the vertex attributes
	uintptr_t numBytesPositions = positions.size() * sizeof( glm::vec3 );
	uintptr_t numBytesTexCoords = texCoords.size() * sizeof( glm::vec3 );
	uintptr_t numBytesNormals = normals.size() * sizeof( glm::vec3 );

	// OpenGL core spec requires a VAO bound when calling glDrawArrays
	glGenVertexArrays( 1, &displayVAO );
	glBindVertexArray( displayVAO );

	//BUFFER
	glGenBuffers( 1, &displayVBO );
	glBindBuffer( GL_ARRAY_BUFFER, displayVBO );

	// idk
	glUseProgram( sponzaShader );

	// send it
	glBufferData( GL_ARRAY_BUFFER, numBytesPositions + numBytesTexCoords + numBytesNormals, NULL, GL_DYNAMIC_DRAW );
	uint bufferbase = 0;
	glBufferSubData( GL_ARRAY_BUFFER, bufferbase, numBytesPositions, &positions[ 0 ] );
	bufferbase += numBytesPositions;
	glBufferSubData( GL_ARRAY_BUFFER, bufferbase, numBytesTexCoords, &texCoords[ 0 ] );
	bufferbase += numBytesTexCoords;
	glBufferSubData( GL_ARRAY_BUFFER, bufferbase, numBytesNormals, &normals[ 0 ] );


// set up the pointers to the vertex data... layout qualifiers seem to be the easiest way to get this to go through successfully
	{
		const GLvoid * base = ( GLvoid * ) 0;
		// glEnableVertexAttribArray( glGetAttribLocation( sponzaShader, "vPosition" ) );
		// glVertexAttribPointer( glGetAttribLocation( sponzaShader, "vPosition" ), 3, GL_FLOAT, GL_FALSE, 0, base );
		glEnableVertexAttribArray( 0 );
		glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, base );
	}
	{
		const GLvoid * base = ( GLvoid * ) numBytesPositions;
		// glEnableVertexAttribArray( glGetAttribLocation( sponzaShader, "vTexCoord" ) );
		// glVertexAttribPointer( glGetAttribLocation( sponzaShader, "vTexCoord" ), 3, GL_FLOAT, GL_FALSE, 0, base );
		glEnableVertexAttribArray( 1 );
		glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, base );
	}
	{
		const GLvoid * base = ( GLvoid * ) ( numBytesPositions + numBytesTexCoords );
		// glEnableVertexAttribArray( glGetAttribLocation( sponzaShader, "vNormal" ) );
		// glVertexAttribPointer( glGetAttribLocation( sponzaShader, "vNormal" ), 3, GL_FLOAT, GL_FALSE, 0, base );
		glEnableVertexAttribArray( 2 );
		glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, base );
	}

	const size_t tNumBytes = sponzaNumTriangles * 3 * sizeof( vec3 );
	cout << newline << newline << "sent " << sponzaNumTriangles << " triangles, for a total of " <<
		( tNumBytes / 1000000 ) % 1000 << " " <<
		( tNumBytes / 1000 ) % 1000 << " " <<
		( tNumBytes ) % 1000 << " bytes" << newline << newline;

	cout << T_GREEN << "done." << RESET << newline;







	cout << T_BLUE << "    Setting Up Textures" << RESET << " ....................... ";
	// missing textures have been filled with zeroes
	// all textures which do not match the 2048x2048 dimension have been scaled to match on load
	glGenTextures( 1, &texArray );
	glActiveTexture( GL_TEXTURE1 );
	glBindTexture( GL_TEXTURE_2D_ARRAY, texArray );

	// preallocate storage
	glTexStorage3D( GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, 2048, 2048, s.texSet.size() );

	// go go go
	for ( size_t i = 0; i < s.texSet.size(); i++ ) {
		s.texSet[ i ].FlipVertical();
		glTexSubImage3D( GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, 2048, 2048, 1, GL_RGBA, GL_UNSIGNED_BYTE, &s.texSet[ i ].data[ 0 ] );
	}

	// generate the mipmaps
	glGenerateMipmap( GL_TEXTURE_2D_ARRAY );

	const size_t numBytes = 2048 * 2048 * 4 * s.texSet.size();
	cout << newline << newline << "sent " <<
		( numBytes / 1000000 ) % 1000 << " " <<
		( numBytes / 1000 ) % 1000 << " " <<
		( numBytes ) % 1000 << " bytes to GPU for Sponza textures" << newline << newline;

	// parameters
	glTexParameteri( GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri( GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S,  GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T,  GL_REPEAT );





	// create the image textures
	Image initial( config.width, config.height, false );
	glGenTextures( 1, &accumulatorTexture );
	glActiveTexture( GL_TEXTURE3 );
	glBindTexture( GL_TEXTURE_2D, accumulatorTexture );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, config.width, config.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &initial.data[ 0 ] );

	glGenTextures( 1, &displayTexture );
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, displayTexture );
	bool linearFilter = true;
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, linearFilter ? GL_LINEAR : GL_NEAREST );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, linearFilter ? GL_LINEAR : GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, config.width, config.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &initial.data[ 0 ] );

	// blue noise image on the GPU
	Image blueNoiseImage{ "resources/noise/blueNoise.png", LODEPNG };
	glGenTextures( 1, &blueNoiseTexture );
	glActiveTexture( GL_TEXTURE4 );
	glBindTexture( GL_TEXTURE_2D, blueNoiseTexture );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, blueNoiseImage.width, blueNoiseImage.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &blueNoiseImage.data[ 0 ] );

	cout << T_GREEN << "done." << RESET << newline;
}

void engine::ShaderCompile () {
	cout << T_BLUE << "    Compiling Shaders" << RESET << " ......................... ";

	// create the shader for the triangles to cover the screen
	displayShader = regularShader( "resources/engineCode/shaders/blit.vs.glsl", "resources/engineCode/shaders/blit.fs.glsl" ).shaderHandle;

	// load the sponza shader
	sponzaShader = regularShader( "resources/engineCode/shaders/sponza.vs.glsl", "resources/engineCode/shaders/sponza.fs.glsl" ).shaderHandle;

	// initialize the text renderer
	textRenderer.Init( config.width, config.height, computeShader( "resources/fonts/fontRenderer/font.cs.glsl" ).shaderHandle );

	// something to put data in the accumulator texture
	dummyDrawShader = computeShader( "resources/engineCode/shaders/dummyDraw.cs.glsl" ).shaderHandle;

	// tonemapping shader
	tonemapShader = computeShader( "resources/engineCode/shaders/tonemap.cs.glsl" ).shaderHandle;

	cout << T_GREEN << "done." << RESET << newline;
}

void engine::ImguiSetup () {
	cout << T_BLUE << "    Configuring dearImGUI" << RESET << " ..................... ";

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
	glClearColor( config.clearColor.x, config.clearColor.y, config.clearColor.z, config.clearColor.w );
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
