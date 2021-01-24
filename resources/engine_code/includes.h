#ifndef INCLUDES
#define INCLUDES

#include <stdio.h>

//stl includes
#include <vector>
#include <cmath>
#include <numeric>
#include <random>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <deque>
#include <chrono>
#include <cstdint>
#include <cstdlib>
//#include <filesystem> //c++20 support not quite universal yet

//iostream aliases
using std::cin;
using std::cout;
using std::cerr;

using std::flush;
using std::endl;

//vector math library GLM
#define GLM_FORCE_SWIZZLE
#define GLM_SWIZZLE_XYZW
#include "../glm/glm.hpp" //general vector types
#include "../glm/gtc/matrix_transform.hpp" // for glm::ortho
#include "../glm/gtc/type_ptr.hpp" //to send matricies gpu-side
#include "../glm/gtx/transform.hpp"

//not sure as to the utility of this
#define GLX_GLEXT_PROTOTYPES


//GUI library (dear ImGUI)
#include "../ocornut_imgui/imgui.h"
#include "../ocornut_imgui/imgui_impl_sdl.h"
#include "../ocornut_imgui/imgui_impl_opengl3.h"


// Initialize glew loader with glewInit()
// #include <GL/glew.h>

// now handled differently with imgui
#include "../ocornut_imgui/gl3w.h"

//SDL includes - windowing, gl context, system info
#include <SDL2/SDL.h>
//allows you to run OpenGL inside of SDL2
#include <SDL2/SDL_opengl.h>


//png loading library - very powerful
#include "../lodev_lodePNG/lodepng.h"


//shader compilation wrapper - may need to be extended
#include "shader.h"


//up to 3d perlin noise generation
#include "../perlin/perlin.h"


//diamond square heightmap generation
#include "../mafford_diamond_square/diamond_square.h"


//Brent Werness' Voxel Automata Terrain
#include "../VAT/VAT.h"


// Niels Lohmann - JSON for Modern C++
#include "../nlohmann_JSON/json.hpp"
using json = nlohmann::json;


#define WIDTH  640
#define HEIGHT 480


#endif
