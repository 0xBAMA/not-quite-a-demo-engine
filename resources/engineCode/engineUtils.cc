#include "engine.h"

bool engine::MainLoop () {
	ZoneScoped;

	HandleEvents();								// handle keyboard / mouse events
	ClearColorAndDepth();					// if I just disable depth testing, this can disappear
	ComputePasses();							// multistage update of displayTexture
	BlitToScreen();								// fullscreen triangle copying the displayTexture to the screen
	ImguiPass();									// do all the gui stuff
	SDL_GL_SwapWindow( window );	// show what has just been drawn to the back buffer ( displayTexture + ImGui )
	FrameMark;										// tells tracy that this is the end of a frame
	return pQuit;									// break main loop when pQuit turns true
}

void engine::ComputePasses () {
	ZoneScoped;

// dummy draw
	// set up environment ( 0:blue noise, 1: accumulator )
	// glBindImageTexture( 0, blueNoiseTexture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA8UI );
	// glBindImageTexture( 1, accumulatorTexture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA8UI );

	// blablah draw something into accumulatorTexture
	// glUseProgram( dummyDrawShader );
	// glDispatchCompute( ( WIDTH + 15 ) / 16, ( HEIGHT + 15 ) / 16, 1 );
	// glMemoryBarrier( GL_SHADER_IMAGE_ACCESS_BARRIER_BIT );

// postprocessing
	// set up environment ( 0:accumulator, 1:display )
	glBindImageTexture( 0, accumulatorTexture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA8UI );
	glBindImageTexture( 1, displayTexture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA8UI );

	// shader for color grading ( color temp, contrast, gamma ... ) + tonemapping
	glUseProgram( tonemapShader );
	SendTonemappingParameters();
	glDispatchCompute( ( WIDTH + 15 ) / 16, ( HEIGHT + 15 ) / 16, 1 );
	glMemoryBarrier( GL_SHADER_IMAGE_ACCESS_BARRIER_BIT );

	// shader to apply dithering
		// ...

	// other postprocessing
		// ...

	// text rendering timestamp, as final step - required texture binds are handled internally
	textRenderer.Update( ImGui::GetIO().DeltaTime );
	textRenderer.Draw( displayTexture ); // displayTexture is the writeTarget
	glMemoryBarrier( GL_SHADER_IMAGE_ACCESS_BARRIER_BIT );
}

void engine::ClearColorAndDepth () {
	ZoneScoped;

	// clear the screen
	glClearColor( clearColor.x, clearColor.y, clearColor.z, clearColor.w );
	// glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glClear( GL_COLOR_BUFFER_BIT );

	ImGuiIO &io = ImGui::GetIO();
	const int width = ( int ) io.DisplaySize.x;
	const int height = ( int ) io.DisplaySize.y;
	// prevent -1, -1 being passed on first frame, since ImGui hasn't rendered yet
	glViewport(0, 0, width > 0 ? width : WIDTH, height > 0 ? height : HEIGHT );
}

void engine::SendTonemappingParameters () {
	ZoneScoped;

	glUniform3fv( glGetUniformLocation( tonemapShader, "colorTempAdjust" ), 1, glm::value_ptr( GetColorForTemperature( tonemap.colorTemp ) ) );
	glUniform1i( glGetUniformLocation( tonemapShader, "tonemapMode" ), tonemap.tonemapMode );
	glUniform1f( glGetUniformLocation( tonemapShader, "gamma" ), tonemap.gamma );
}

void engine::BlitToScreen () {
	ZoneScoped;

	// bind the displayTexture and display its current state
	glBindImageTexture( 0, displayTexture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA8UI );
	glUseProgram( displayShader );
	glBindVertexArray( displayVAO );
	ImGuiIO &io = ImGui::GetIO();
	glUniform2f( glGetUniformLocation( displayShader, "resolution" ), io.DisplaySize.x, io.DisplaySize.y );
	glDrawArrays( GL_TRIANGLES, 0, 3 );
}

void engine::ImguiPass () {
	ZoneScoped;

	ImguiFrameStart();					// start the imgui frame
	TonemapControlsWindow();

	// if ( true )
		// ImGui::ShowDemoWindow();	// show the demo window
	QuitConf( &quitConfirm );		// show quit confirm window, if triggered
	// static bool showMenu = true;
	// MenuLayout( &showMenu );

	ImguiFrameEnd();						// finish up the imgui stuff and put it in the framebuffer
}

void engine::HandleEvents () {
	ZoneScoped;

	static SoftRast s( WIDTH, HEIGHT );
	static bool firstTime = true;
	if ( firstTime ) {
		s.LoadModel( "../otherFolks/Sponza/sponza.obj", "../otherFolks/Sponza/" );
		firstTime = false;
	}

	static mat3 transform = rotation( vec3( 0.0f, 1.0f, 0.0f ), -1.5f ) * rotation( vec3( 1.0f, 0.0f, 0.0f ), pi - 0.2f ) * mat3( 0.005f );
	static vec3 offset = vec3( 0.0f, 2.5f, -1.0f );
	s.Color.SetTo( 0 );
	s.Depth.SetTo( 10000.0f );
	s.DrawModel( transform, offset );

	// buffer result to the accumulator buffer

	glBindTexture( GL_TEXTURE_2D, accumulatorTexture );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, WIDTH, HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, &s.Color.data[ 0 ] );

	// s.Color.Save( "test.png" );

	// Image depthOutput( WIDTH, HEIGHT );
	// for ( uint32_t x = 0; x < WIDTH; x++ ) {
	// 	for ( uint32_t y = 0; y < HEIGHT; y++ ) {
	// 		float d = s.Depth.GetAtXY( x, y ).r;
	// 		uint8_t writeVal = uint8_t( RemapRange( d, -1.0f, 1.0f, 0.0f, 255.0f ) );
	// 		depthOutput.SetAtXY( x, y, { writeVal, writeVal, writeVal, 255 } );
	// 	}
	// }
	// depthOutput.Save( "testDepth.png" );

	const uint8_t *state = SDL_GetKeyboardState( NULL );
	const float scalar = SDL_GetModState() & KMOD_SHIFT ? 1000.0f : 10.0f;

	if ( state[ SDL_SCANCODE_RIGHT ] ) {
		cout << "Right Key Pressed" << newline << flush;
		offset += transform * vec3( 0.0f, 0.0f, 1.0f * scalar );
	}

	if ( state[ SDL_SCANCODE_LEFT ] ) {
		cout << "Left Key Pressed" << newline << flush;
		offset += transform * vec3( 0.0f, 0.0f, -1.0f * scalar );
	}

	if ( state[ SDL_SCANCODE_UP ] ) {
		cout << "Up Key Pressed" << newline << flush;
		offset += transform * vec3( 1.0f * scalar, 0.0f, 0.0f );
	}

	if ( state[ SDL_SCANCODE_DOWN ] ) {
		cout << "Down Key Pressed" << newline << flush;
		offset += transform * vec3( -1.0f * scalar, 0.0f, 0.0f );
	}

	if ( state[ SDL_SCANCODE_PAGEDOWN ] ) {
		cout << "PageDown Pressed" << newline << flush;
		offset += transform * vec3( 0.0f, -1.0f * scalar, 0.0f );
	}

	if ( state[ SDL_SCANCODE_PAGEUP ] ) {
		cout << "PageUp Pressed" << newline << flush;
		offset += transform * vec3( 0.0f, 1.0f * scalar, 0.0f );
	}

	if ( state[ SDL_SCANCODE_W ] ) {
		cout << "W Pressed" << newline << flush;
		transform = rotation( transform * vec3( 0.0f, 0.0f, 1.0f ), -0.01f * scalar ) * transform;
	}

	if ( state[ SDL_SCANCODE_S ] ) {
		cout << "S Pressed" << newline << flush;
		transform = rotation( transform * vec3( 0.0f, 0.0f, 1.0f ), 0.01f * scalar ) * transform;
	}

	if ( state[ SDL_SCANCODE_A ] ) {
		cout << "A Pressed" << newline << flush;
		transform = rotation( transform * vec3( 0.0f, 1.0f, 0.0f ), 0.01f * scalar ) * transform;
	}

	if ( state[ SDL_SCANCODE_D ] ) {
		cout << "D Pressed" << newline << flush;
		transform = rotation( transform * vec3( 0.0f, 1.0f, 0.0f ), -0.01f * scalar ) * transform;
	}

//==============================================================================
// Need to keep this for pQuit handling ( force quit )
// In particular - checking for window close and the SDL_QUIT event can't really be determined
//  via the keyboard state, and then imgui needs it too, so can't completely kill the event
//  polling loop - maybe eventually I'll find a solution for this
	SDL_Event event;
	SDL_PumpEvents();
	while ( SDL_PollEvent( &event ) ) {
		// imgui event handling
		ImGui_ImplSDL2_ProcessEvent( &event );
		// swap out the multiple if statements for a big chained boolean setting the value of pQuit
		pQuit = ( event.type == SDL_QUIT ) ||
				( event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID( window ) ) ||
				( event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE && SDL_GetModState() & KMOD_SHIFT );
		// this has to stay because it doesn't seem like ImGui::IsKeyReleased is stable enough to use
		if ( ( event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE ) || ( event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_X1 )  )
			quitConfirm = !quitConfirm;
	}
}
