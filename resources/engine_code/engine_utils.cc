#include "engine.h"

bool engine::mainLoop() {
  ImGuiIO &io = ImGui::GetIO();

  glClearColor( clearColor.x, clearColor.y, clearColor.z, clearColor.w ); // from hsv picker
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the background

  // texture display
  glUseProgram( displayShader );
  glBindVertexArray( displayVAO );
  glBindBuffer( GL_ARRAY_BUFFER, displayVBO );

  glUniform2f( glGetUniformLocation( displayShader, "resolution"), io.DisplaySize.x, io.DisplaySize.y );
  glDrawArrays( GL_TRIANGLES, 0, 3 );

  // start the imgui frame
  imguiFrameStart();

  // show quit confirm window
  quitConf( &quitConfirm );

  // show the demo window
  static bool showDemoWindow = true;
  if ( showDemoWindow )
    ImGui::ShowDemoWindow( &showDemoWindow );

  // finish up the imgui stuff and put it in the framebuffer
  imguiFrameEnd();

  // swap the double buffers to present
  SDL_GL_SwapWindow( window );

  // handle all events
  handleEvents();

  // break main loop when pQuit turns true
  return pQuit;
}


void engine::handleEvents() {
  // handle events
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
      pQuit = true; // force quit on shift+esc

  }
}
