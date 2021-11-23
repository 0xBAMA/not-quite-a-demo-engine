#include "engine.h"
// This contains the lower level code

// TinyOBJLoader - This has to be included in a .cc file, so it's here for right
// now
#define TINYOBJLOADER_IMPLEMENTATION
// #define TINYOBJLOADER_USE_DOUBLE
#include "../TinyOBJLoader/tiny_obj_loader.h"
// tinyobj callbacks
//  user_data is passed in as void, then cast as 'engine' class to push
//  vertices, normals, texcoords, index, material info
void vertex_cb(void *user_data, float x, float y, float z, float w) {
  engine *t = reinterpret_cast<engine *>(user_data);

  t->vertices.push_back(glm::vec4(x, y, z, w));
}

void normal_cb(void *user_data, float x, float y, float z) {
  engine *t = reinterpret_cast<engine *>(user_data);

  t->normals.push_back(glm::vec3(x, y, z));
}

void texcoord_cb(void *user_data, float x, float y, float z) {
  engine *t = reinterpret_cast<engine *>(user_data);

  t->texcoords.push_back(glm::vec3(x, y, z));
}

void index_cb(void *user_data, tinyobj::index_t *indices, int num_indices) {
  engine *t = reinterpret_cast<engine *>(user_data);

  if (num_indices == 3) // this is a triangle
  {
    // OBJ uses 1-indexing, convert to 0-indexing
    t->triangle_indices.push_back(glm::ivec3(indices[0].vertex_index - 1,
                                             indices[1].vertex_index - 1,
                                             indices[2].vertex_index - 1));
    t->normal_indices.push_back(glm::ivec3(indices[0].normal_index - 1,
                                           indices[1].normal_index - 1,
                                           indices[2].normal_index - 1));
    t->texcoord_indices.push_back(glm::ivec3(indices[0].texcoord_index - 1,
                                             indices[1].texcoord_index - 1,
                                             indices[2].texcoord_index - 1));
  }

  // lines, points have a different number of indicies
  //  might want to handle these
}

void usemtl_cb(void *user_data, const char *name, int material_idx) {
  engine *t = reinterpret_cast<engine *>(user_data);
  (void)t;
}

void mtllib_cb(void *user_data, const tinyobj::material_t *materials,
               int num_materials) {
  engine *t = reinterpret_cast<engine *>(user_data);
  (void)t;
}

void group_cb(void *user_data, const char **names, int num_names) {
  engine *t = reinterpret_cast<engine *>(user_data);
  (void)t;
}

void object_cb(void *user_data, const char *name) {
  engine *t = reinterpret_cast<engine *>(user_data);
  (void)t;
}

// this is where the callbacks are used
void engine::load_OBJ(std::string filename) {
  tinyobj::callback_t cb;
  cb.vertex_cb = vertex_cb;
  cb.normal_cb = normal_cb;
  cb.texcoord_cb = texcoord_cb;
  cb.index_cb = index_cb;
  cb.usemtl_cb = usemtl_cb;
  cb.mtllib_cb = mtllib_cb;
  cb.group_cb = group_cb;
  cb.object_cb = object_cb;

  std::string warn;
  std::string err;

  std::ifstream ifs(filename.c_str());
  tinyobj::MaterialFileReader mtlReader(".");

  bool ret =
      tinyobj::LoadObjWithCallback(ifs, cb, this, &mtlReader, &warn, &err);

  if (!warn.empty()) {
    std::cout << "WARN: " << warn << std::endl;
  }

  if (!err.empty()) {
    std::cerr << err << std::endl;
  }

  if (!ret) {
    std::cerr << "Failed to parse .obj" << std::endl;
  }

  cout << "vertex list length: " << vertices.size() << endl;
  cout << "normal list length: " << normals.size() << endl;
  cout << "texcoord list length: " << texcoords.size() << endl;

  cout << "vertex index list length: " << triangle_indices.size() << endl;
  cout << "normal index length: " << normal_indices.size() << endl;
  cout << "texcoord index length: " << texcoord_indices.size() << endl;
}

void engine::create_window() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    printf("Error: %s\n", SDL_GetError());
  }

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);

  // this is how you query the screen resolution
  SDL_DisplayMode dm;
  SDL_GetDesktopDisplayMode(0, &dm);

  // pulling these out because I'm going to try to span the whole screen with
  // the window, in a way that's flexible on different resolution screens
  total_screen_width = dm.w;
  total_screen_height = dm.h;

  cout << "creating window...";

  // window = SDL_CreateWindow( "OpenGL Window", 50, 50, total_screen_width-100,
  // total_screen_height-100, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN |
  // SDL_WINDOW_BORDERLESS );
  window = SDL_CreateWindow(
      "OpenGL Window", 0, 0, total_screen_width, total_screen_height,
      SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);
  SDL_ShowWindow(window);

  cout << "done." << endl;

  cout << "setting up OpenGL context...";
  // OpenGL 4.3 + GLSL version 430
  const char *glsl_version = "#version 430";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  GLcontext = SDL_GL_CreateContext(window);

  SDL_GL_MakeCurrent(window, GLcontext);
  SDL_GL_SetSwapInterval(1); // Enable vsync
  // SDL_GL_SetSwapInterval(0); // explicitly disable vsync

  if (gl3wInit() != 0) fprintf(stderr, "Failed to initialize OpenGL loader!\n");

  glEnable(GL_DEPTH_TEST);
  // glEnable(GL_LINE_SMOOTH);

  glPointSize(3.0);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io; // void cast prevents unused variable warning

  // enable docking
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

  // adds a font, as default
  // io.Fonts->AddFontFromFileTTF("resources/fonts/star_trek/titles/Jefferies.ttf", 15);
  // io.Fonts->AddFontFromFileTTF("resources/fonts/star_trek/titles/TNG_Title.ttf", 16);

  ImGui::StyleColorsDark();

  // Setup Platform/Renderer bindings
  ImGui_ImplSDL2_InitForOpenGL(window, GLcontext);
  ImGui_ImplOpenGL3_Init(glsl_version);

  clear_color = ImVec4(75.0f / 255.0f, 75.0f / 255.0f, 75.0f / 255.0f, 0.5f); // initial value for clear color

  // really excited by the fact imgui has an hsv picker to set this
  glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);
  SDL_GL_SwapWindow(window);

  cout << "done." << endl;

  ImVec4 *colors = ImGui::GetStyle().Colors;

  colors[ImGuiCol_Text] = ImVec4(0.64f, 0.37f, 0.37f, 1.00f);
  colors[ImGuiCol_TextDisabled] = ImVec4(0.49f, 0.26f, 0.26f, 1.00f);
  colors[ImGuiCol_WindowBg] = ImVec4(0.17f, 0.00f, 0.00f, 0.98f);
  colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_PopupBg] = ImVec4(0.18f, 0.00f, 0.00f, 0.94f);
  colors[ImGuiCol_Border] = ImVec4(0.35f, 0.00f, 0.03f, 0.50f);
  colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_FrameBg] = ImVec4(0.14f, 0.04f, 0.00f, 1.00f);
  colors[ImGuiCol_FrameBgHovered] = ImVec4(0.14f, 0.04f, 0.00f, 1.00f);
  colors[ImGuiCol_FrameBgActive] = ImVec4(0.14f, 0.04f, 0.00f, 1.00f);
  colors[ImGuiCol_TitleBg] = ImVec4(0.14f, 0.04f, 0.00f, 1.00f);
  colors[ImGuiCol_TitleBgActive] = ImVec4(0.14f, 0.04f, 0.00f, 1.00f);
  colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
  colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
  colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
  colors[ImGuiCol_CheckMark] = ImVec4(0.87f, 0.23f, 0.09f, 1.00f);
  colors[ImGuiCol_SliderGrab] = ImVec4(0.87f, 0.23f, 0.09f, 1.00f);
  colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 0.33f, 0.00f, 1.00f);
  colors[ImGuiCol_Button] = ImVec4(0.81f, 0.38f, 0.09f, 0.08f);
  colors[ImGuiCol_ButtonHovered] = ImVec4(0.87f, 0.23f, 0.09f, 1.00f);
  colors[ImGuiCol_ButtonActive] = ImVec4(1.00f, 0.33f, 0.00f, 1.00f);
  colors[ImGuiCol_Header] = ImVec4(0.81f, 0.38f, 0.09f, 0.08f);
  colors[ImGuiCol_HeaderHovered] = ImVec4(0.87f, 0.23f, 0.09f, 1.00f);
  colors[ImGuiCol_HeaderActive] = ImVec4(1.00f, 0.33f, 0.00f, 1.00f);
  colors[ImGuiCol_Separator] = ImVec4(0.81f, 0.38f, 0.09f, 0.08f);
  colors[ImGuiCol_SeparatorHovered] = ImVec4(0.87f, 0.23f, 0.09f, 1.00f);
  colors[ImGuiCol_SeparatorActive] = ImVec4(1.00f, 0.33f, 0.00f, 1.00f);
  colors[ImGuiCol_ResizeGrip] = ImVec4(0.81f, 0.38f, 0.09f, 0.08f);
  colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.87f, 0.23f, 0.09f, 1.00f);
  colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 0.33f, 0.00f, 1.00f);
  colors[ImGuiCol_Tab] = ImVec4(0.81f, 0.38f, 0.09f, 0.08f);
  colors[ImGuiCol_TabHovered] = ImVec4(0.87f, 0.23f, 0.09f, 1.00f);
  colors[ImGuiCol_TabActive] = ImVec4(1.00f, 0.33f, 0.00f, 1.00f);
  colors[ImGuiCol_TabUnfocused] = ImVec4(0.81f, 0.38f, 0.09f, 0.08f);
  colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.81f, 0.38f, 0.09f, 0.08f);
  colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
  colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
  colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
  colors[ImGuiCol_TextSelectedBg] = ImVec4(0.81f, 0.38f, 0.09f, 0.08f);
  colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
  colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
  colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
  colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
  colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}

void engine::quit_conf(bool *open) {
  if (*open) {
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration;

    // create centered window
    ImGui::SetNextWindowPos( ImVec2(total_screen_width / 2 - 120, total_screen_height / 2 - 25));
    ImGui::SetNextWindowSize(ImVec2(300, 55));
    ImGui::Begin("quit", open, flags);

    ImGui::Text("Are you sure you want to quit?");

    ImGui::Text("  ");
    ImGui::SameLine();

    // button to cancel -> set this window's bool to false
    if (ImGui::Button(" Cancel "))
      *open = false;

    ImGui::SameLine();
    ImGui::Text("      ");
    ImGui::SameLine();

    // button to quit -> set pquit to true
    if (ImGui::Button(" Quit "))
      pquit = true;

    ImGui::End();
  }
}

void engine::gl_setup() {
  // some info on your current platform
  const GLubyte *renderer = glGetString(GL_RENDERER); // get renderer string
  const GLubyte *version = glGetString(GL_VERSION);   // version as a string
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n\n\n", version);

  // create the shader for the triangles to cover the screen
  display_shader = Shader("resources/engine_code/shaders/blit.vs.glsl", "resources/engine_code/shaders/blit.fs.glsl").Program;

  std::vector<glm::vec3> points;
  points.clear();

  // based on this, one triangle is significantly faster than two
  // https://michaldrobot.com/2014/04/01/gcn-execution-patterns-in-full-screen-passes/
  // main idea there is that there is coherency along the diagonal, which does not exist with two triangles
  // e.g. if the execution blocks straddle the diagonal, they have to consider two primitives instead of one
  // so even with the clipping that happens around the viewport, the rasterization process is still cheaper,
  // since there is no divergence there. Long story short, good for about 10% speedup. Good practice.
  points.push_back(glm::vec3(-1, -1, 0.5)); // A
  points.push_back(glm::vec3(3, -1, 0.5));  // B
  points.push_back(glm::vec3(-1, 3, 0.5));  // C

  // vao, vbo
  cout << "  setting up vao, vbo for display geometry...........";
  glGenVertexArrays(1, &display_vao);
  glBindVertexArray(display_vao);

  glGenBuffers(1, &display_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, display_vbo);
  cout << "done." << endl;

  // buffer the data
  cout << "  buffering vertex data..............................";
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * points.size(), NULL, GL_DYNAMIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * points.size(), &points[0]);
  cout << "done." << endl;

  // set up attributes
  cout << "  setting up attributes in display shader............";
  GLuint points_attrib = glGetAttribLocation(display_shader, "vPosition");
  glEnableVertexAttribArray(points_attrib);
  glVertexAttribPointer(points_attrib, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(static_cast<const char *>(0) + (0)));
  cout << "done." << endl;

  // replace this with real image data
  std::vector<uint8_t> image_data;
  image_data.resize(WIDTH * HEIGHT * 4);

  // fill with random values
  std::default_random_engine gen;
  std::uniform_int_distribution<uint8_t> dist(150, 255);
  std::uniform_int_distribution<uint8_t> dist2(12, 45);

  for (auto it = image_data.begin(); it != image_data.end(); it++) {
    int index = (it - image_data.begin());
    uint8_t rxor = (uint8_t)((index / (WIDTH)) % 256) ^ (uint8_t)((index % (4 * WIDTH)) % 256);

    switch ((index) % 4) {
    case 3:
      *it = 255; // alpha channels
      break;

    case 2:
      *it = (index % (WIDTH * 3) < WIDTH) ? 36 - dist2(gen) : 0;
      break;

    case 1:
      *it = dist(gen);
      break;

    case 0:
      *it = 0.75 * (rxor);
      break;

    default:
      break;
    }

    // *it = ((index) % 4 == 3) ? 255 : noise < 0.56 ? noise * 0.75 *
    // (3-(index%4)) * rxor : noise*dist(gen); // alpha channels get 255, other
    // colors get random
  }

  // create the image textures
  glGenTextures(1, &display_texture);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_RECTANGLE, display_texture);

  // texture parameters
  glTexParameterf(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  // buffer the image data to the GPU
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_RECTANGLE, display_texture);
  glTexImage2D(GL_TEXTURE_RECTANGLE, 0, GL_RGBA8UI, WIDTH, HEIGHT, 0,
               GL_RGBA_INTEGER, GL_UNSIGNED_BYTE, &image_data[0]);
  glBindImageTexture(0, display_texture, 0, GL_FALSE, 0, GL_READ_WRITE,
                     GL_RGBA8UI);

  // compute shaders, etc...
}

static void HelpMarker(const char *desc) {
  ImGui::TextDisabled("(?)");
  if (ImGui::IsItemHovered()) {
    ImGui::BeginTooltip();
    ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
    ImGui::TextUnformatted(desc);
    ImGui::PopTextWrapPos();
    ImGui::EndTooltip();
  }
}

void engine::draw_everything() {
  ImGuiIO &io = ImGui::GetIO();
  (void)io; // void cast prevents unused variable warning
  // get the screen dimensions and pass in as uniforms

  glClearColor(clear_color.x, clear_color.y, clear_color.z,
               clear_color.w);                        // from hsv picker
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the background

  // draw the stuff on the GPU

  // texture display
  glUseProgram(display_shader);
  glBindVertexArray(display_vao);
  glBindBuffer(GL_ARRAY_BUFFER, display_vbo);

  glUniform2f(glGetUniformLocation(display_shader, "resolution"),
              io.DisplaySize.x, io.DisplaySize.y);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame(window);
  ImGui::NewFrame();

  // show quit confirm window
  quit_conf(&quitconfirm);

  // show the demo window
  static bool show_demo_window = true;
  if (show_demo_window)
    ImGui::ShowDemoWindow(&show_demo_window);

  // do my own windows
  ImGui::Begin("Controls0", NULL, 0);
  ImGui::Text("This is some text");
  ImGui::End();

  ImGui::Begin("Controls1", NULL, 0);
  ImGui::Text("This is some text");
  ImGui::End();

  ImGui::Begin("Editor", NULL, 0);

  static TextEditor editor;
  // static auto lang = TextEditor::LanguageDefinition::CPlusPlus();
  static auto lang = TextEditor::LanguageDefinition::GLSL();
  editor.SetLanguageDefinition(lang);

  auto cpos = editor.GetCursorPosition();
  // editor.SetPalette(TextEditor::GetLightPalette());
  editor.SetPalette(TextEditor::GetDarkPalette());
  // editor.SetPalette(TextEditor::GetRetroBluePalette());

  static const char *fileToEdit = "resources/engine_code/shaders/blit.vs.glsl";
  std::ifstream t(fileToEdit);
  static bool loaded = false;
  if (!loaded) {
    editor.SetLanguageDefinition(lang);
    if (t.good()) {
      editor.SetText(std::string((std::istreambuf_iterator<char>(t)),
                                 std::istreambuf_iterator<char>()));
      loaded = true;
    }
  }

  ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s | %s", cpos.mLine + 1,
              cpos.mColumn + 1, editor.GetTotalLines(),
              editor.IsOverwrite() ? "Ovr" : "Ins",
              editor.CanUndo() ? "*" : " ",
              editor.GetLanguageDefinition().mName.c_str(), fileToEdit);

  editor.Render("TextEditor");
  ImGui::End();

  // get it ready to put on the screen
  ImGui::Render();

  ImGui_ImplOpenGL3_RenderDrawData(
      ImGui::GetDrawData()); // put imgui data into the framebuffer



  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
    SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
  }

  SDL_GL_SwapWindow(window); // swap the double buffers

  // handle events

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    ImGui_ImplSDL2_ProcessEvent(&event);

    if (event.type == SDL_QUIT)
      pquit = true;

    if (event.type == SDL_WINDOWEVENT &&
        event.window.event == SDL_WINDOWEVENT_CLOSE &&
        event.window.windowID == SDL_GetWindowID(window))
      pquit = true;

    if ((event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE) ||
        (event.type == SDL_MOUSEBUTTONDOWN &&
         event.button.button ==
             SDL_BUTTON_X1)) // x1 is browser back on the mouse
      quitconfirm = !quitconfirm;

    if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE &&
        SDL_GetModState() & KMOD_SHIFT)
      pquit = true; // force quit
  }
}

void engine::quit() {
  // shutdown everything
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  // destroy window
  SDL_GL_DeleteContext(GLcontext);
  SDL_DestroyWindow(window);
  SDL_Quit();

  cout << "goodbye." << endl;
}
