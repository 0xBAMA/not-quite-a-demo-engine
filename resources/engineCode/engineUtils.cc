#include "engine.h"

bool engine::MainLoop () {

	// clear the screen and depth buffer
	Clear();

	// compute passes here
		// invoke any shaders you want to use to do work on the GPU
	ComputePasses();

	// fullscreen triangle copying the image
	MainDisplay();

	// do all the gui stuff
	ImguiPass();

	// swap the double buffers to present
	SDL_GL_SwapWindow( window );

	// handle all events
	HandleEvents();

	// break main loop when pQuit turns true
	return pQuit;
}

void engine::ComputePasses () {
	textRenderer.Update( ImGui::GetIO().DeltaTime );
	textRenderer.Draw( displayTexture );
	glMemoryBarrier( GL_SHADER_IMAGE_ACCESS_BARRIER_BIT );
}

void engine::Clear () {
	// clear the screen
	glClearColor( clearColor.x, clearColor.y, clearColor.z, clearColor.w );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	ImGuiIO &io = ImGui::GetIO();
	const int width = ( int ) io.DisplaySize.x;
	const int height = ( int ) io.DisplaySize.y;
	// prevent -1, -1 being passed on first frame, since ImGui hasn't rendered yet
	glViewport(0, 0, width > 0 ? width : WIDTH, height > 0 ? height : HEIGHT );
}

void engine::MainDisplay () {
	// bind the display texture
	glBindImageTexture( 0, displayTexture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA8UI );

	// texture display
	ImGuiIO &io = ImGui::GetIO();
	glUseProgram( displayShader );
	glBindVertexArray( displayVAO );
	glUniform2f( glGetUniformLocation( displayShader, "resolution" ), io.DisplaySize.x, io.DisplaySize.y );
	glDrawArrays( GL_TRIANGLES, 0, 3 );
}

void engine::ImguiPass () {
	// start the imgui frame
	ImguiFrameStart();

	// show the demo window
	static bool showDemoWindow = false;
	if ( showDemoWindow )
		ImGui::ShowDemoWindow( &showDemoWindow );

	// show quit confirm window, if triggered
	QuitConf( &quitConfirm );

	// finish up the imgui stuff and put it in the framebuffer
	ImguiFrameEnd();
}


void engine::HandleEvents () {

	//this is the other way to handle the input - check the state of the keys every frame
		// key element here is that you can handle more than one at once - e.g. I can have
		// simultaneous input from left and up, where the SDL_PollEvent method did not make
		// these things available in the same scope - it creates a massive spew of input
		// events when compared to the SDL_PollEvent method, so sometimes, that'll need to
		// be considered ( framerate dependency, cooldown kind of logic )
//==============================================================================
// list of input indices/names: https://wiki.libsdl.org/SDL_Scancode
//==============================================================================

	const uint8_t *state = SDL_GetKeyboardState( NULL );
	// example usage to get rid of compiler warning about unused variable state
		// look up the scancodes for desired keys
	if ( state[ SDL_SCANCODE_RIGHT ] )	cout << "Right Key Pressed" << endl << std::flush;
	if ( state[ SDL_SCANCODE_LEFT ] )		cout << "Left Key Pressed" << endl << std::flush;
	if ( state[ SDL_SCANCODE_UP ] )			cout << "Up Key Pressed" << endl << std::flush;
	if ( state[ SDL_SCANCODE_DOWN ] )		cout << "Down Key Pressed" << endl << std::flush;

// think about some kind of mapping using std::unordered_map - better yet, write an unordered_map implementation

//==============================================================================
//this is the way that the event system used to work - I will keep this for QuitConfirm / force quit ( pQuit = true on return ) handling
	SDL_Event event;
	while ( SDL_PollEvent( &event ) ) {
		// imgui event handling
		ImGui_ImplSDL2_ProcessEvent( &event );

		if ( event.type == SDL_QUIT )
			pQuit = true;

		if ( event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID( window ) )
			pQuit = true;

		if ( ( event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE) || ( event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_X1 ) )
			quitConfirm = !quitConfirm; // x1 is browser back on the mouse

		if ( event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE && SDL_GetModState() & KMOD_SHIFT )
			pQuit = true; // force quit on shift+esc ( bypasses confirm window )
	}
}
