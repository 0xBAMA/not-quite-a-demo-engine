#ifndef INCLUDES
#define INCLUDES

#include <stdio.h>

// stl includes
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <deque>
// #include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

// iostream stuff
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::flush;
using std::string;
using std::stringstream;
using std::unordered_map;
constexpr char newline = '\n';

// pi definition - definitely sufficient precision
constexpr double pi = 3.14159265358979323846;

// vector math library GLM
#define GLM_FORCE_SWIZZLE
#define GLM_SWIZZLE_XYZW
#include "../GLM/glm.hpp"					// general vector types
#include "../GLM/gtc/matrix_transform.hpp"	// for glm::ortho
#include "../GLM/gtc/type_ptr.hpp"			// to send matricies gpu-side
#include "../GLM/gtx/rotate_vector.hpp"
#include "../GLM/gtx/transform.hpp"
#include "../GLM/gtx/string_cast.hpp"		// to_string for glm types

// not sure as to the utility of this
// #define GLX_GLEXT_PROTOTYPES

// convenience defines for GLM
using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::ivec2;
using glm::ivec3;
using glm::ivec4;
using glm::mat3;
using glm::mat4;

// OpenGL Loader
#include "../ImGUI/gl3w.h"

// GUI library (dear ImGUI)
#include "../ImGUI/TextEditor.h"
#include "../ImGUI/imgui.h"
#include "../ImGUI/imgui_impl_sdl.h"
#include "../ImGUI/imgui_impl_opengl3.h"

// SDL includes - windowing, gl context, system info
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
// #include <SDL2/SDL_opengl_glext.h>

// managing bindings of textures to binding points
#include "./coreUtils/bindset.h"

// image load/save/resize/access/manipulation wrapper
#include "./coreUtils/image.h"

// simple std::chrono wrapper
#include "./coreUtils/timer.h"

// tracy profiler annotation
#include "../tracy/public/tracy/Tracy.hpp"

// font rendering header
#include "../fonts/fontRenderer/renderer.h"

// wrapper for TinyOBJLoader
#include "../ModelLoading/TinyOBJLoader/tiny_obj_loader.h"

// software rasterizer reimplementation
#include "../SoftRast/SoftRast.h"

// shader compilation wrapper
#include "shaders/lib/shaderWrapper.h"

// coloring of CLI output
#include "../data/colors.h"

// bayer patterns 2, 4, 8 + four channel helper func
#include "../data/bayer.h"

// palette list
#include "../data/paletteLoader.h"

// glyph list
#include "../data/glyphLoader.h"

// diamond square heightmap generation
#include "../noise/diamondSquare/diamond_square.h"

// Brent Werness' Voxel Automata Terrain
#include "../noise/VAT/VAT.h"

// more general noise solution
#include "../noise/FastNoise2/include/FastNoise/FastNoise.h"

// bringing the old perlin impl back
#include "../noise/perlin.h"

// Niels Lohmann - JSON for Modern C++
#include "../Serialization/JSON/json.hpp"
using json = nlohmann::json;

// tinyXML2 XML parser
#include "../Serialization/tinyXML2/tinyxml2.h"
using XMLDocument = tinyxml2::XMLDocument;

struct configData {
	uint32_t windowFlags = 0;
	string windowTitle = string( "NQADE" );
	int32_t width = 0;
	int32_t height = 0;
	bool linearFilter = false;
	ivec2 windowOffset = ivec2( 0, 0 );
	uint8_t startOnScreen = 0;
	int reportWidth = 64;

	uint8_t MSAACount = 0;
	vec4 clearColor = vec4( 0.0f );
	bool vSyncEnable = true;
	int numMsDelayAfterCallback = 10;
	uint8_t OpenGLVersionMajor = 4;
	uint8_t OpenGLVersionMinor = 3;
	bool reportPlatformInfo = true;
	bool enableDepthTesting = false;

	// anything else ... ?
};

struct colorGradeParameters {
	int tonemapMode = 6; // todo: write an enum for this
	float gamma = 1.1f;
	float colorTemp = 6500.0f;
};

#endif
