#include "engine.h"

bool engine::MainLoop () {
	// compute passes here
		// invoke any shaders you want to use to do work on the GPU

	// clear the screen and depth buffer
	Clear();

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
	static bool showDemoWindow = true;
	if ( showDemoWindow )
		ImGui::ShowDemoWindow( &showDemoWindow );

	// show quit confirm window
	QuitConf( &quitConfirm );

	// finish up the imgui stuff and put it in the framebuffer
	ImguiFrameEnd();
}


void engine::HandleEvents () {
	SDL_Event event;
	while ( SDL_PollEvent( &event ) ) {
		// imgui event handling
		ImGui_ImplSDL2_ProcessEvent( &event );

		if ( event.type == SDL_QUIT )
			pQuit = true;

		if ( event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID( window ) )
			pQuit = true;

		if ( ( event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE) || ( event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_X1 ))
			quitConfirm = !quitConfirm; // x1 is browser back on the mouse

		if ( event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE && SDL_GetModState() & KMOD_SHIFT )
			pQuit = true; // force quit on shift+esc ( bypasses confirm window )
	}
}
