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
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <sstream>
#include <string>
#include <vector>

// iostream stuff
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::flush;

// pi definition - definitely sufficient precision
constexpr double pi = 3.14159265358979323846;

// MSAA count - effects OpenGL geometry evaluation
constexpr int MSAACount = 1;

// vector math library GLM
#define GLM_FORCE_SWIZZLE
#define GLM_SWIZZLE_XYZW
#include "../GLM/glm.hpp"                  //general vector types
#include "../GLM/gtc/matrix_transform.hpp" // for glm::ortho
#include "../GLM/gtc/type_ptr.hpp"         //to send matricies gpu-side
#include "../GLM/gtx/rotate_vector.hpp"
#include "../GLM/gtx/transform.hpp"

// not sure as to the utility of this
#define GLX_GLEXT_PROTOTYPES

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

// LodePNG PNG Load/Save lib
// key functions:
// load: unsigned error = lodepng::decode( byte vector, unsigned width, unsigned height, cstr path )
// save: unsigned error = lodepng::encode( cstr path, byte vector, unsigned width, unsigned height, channel count enum, bit depth )
#include "../ImageHandling/LodePNG/lodepng.h"


// Sean Barrett's load, save, resize libs - need corresponding define in a .cc file, before their inclusion
	// they are public domain licensed, source available at links - structure for inclusion here wip, due to how they compile

// stb_image - https://github.com/nothings/stb/blob/master/stb_image.h
	// #define STB_IMAGE_IMPLEMENTATION

// stb_image_write - https://github.com/nothings/stb/blob/master/stb_image_write.h
	// #define STB_IMAGE_WRITE_IMPLEMENTATION

// stb_image_resize - https://github.com/nothings/stb/blob/master/stb_image_resize.h
	// #define STB_IMAGE_RESIZE_IMPLEMENTATION


// Rich Geldrich's fpng - public domain, https://github.com/richgel999/fpng


// wrapper for TinyOBJLoader
#include "../TinyOBJLoader/objLoader.h"

// shader #include prepreocessor
#include "shaders/lib/stb_include.h"

// shader compilation wrapper
#include "shaders/lib/shader.h"

// coloring of CLI output
#include "../fonts/colors.h"

// diamond square heightmap generation
#include "../noise/diamondSquare/diamond_square.h"

// Brent Werness' Voxel Automata Terrain
#include "../noise/VAT/VAT.h"

// more general noise solution
#include "../noise/FastNoise2/include/FastNoise/FastNoise.h"

// bringing the old perlin impl back
#include "../noise/perlin.h"

// Niels Lohmann - JSON for Modern C++
#include "../JSON/json.hpp"
using json = nlohmann::json;

#define WIDTH 640
#define HEIGHT 480

// Function to get color temperature from shadertoy user BeRo
// from the author:
//   Color temperature (sRGB) stuff
//   Copyright (C) 2014 by Benjamin 'BeRo' Rosseaux
//   Because the german law knows no public domain in the usual sense,
//   this code is licensed under the CC0 license
//   http://creativecommons.org/publicdomain/zero/1.0/
// Valid from 1000 to 40000 K (and additionally 0 for pure full white)
inline glm::vec3 get_color_for_temp( double temperature ) {
	// Values from:
	// http://blenderartists.org/forum/showthread.php?270332-OSL-Goodness&p=2268693&viewfull=1#post2268693
	glm::mat3 m =
		( temperature <= 6500.0 )
			? glm::mat3(glm::vec3( 0.0, -2902.1955373783176, -8257.7997278925690 ),
									glm::vec3( 0.0, 1669.5803561666639, 2575.2827530017594 ),
									glm::vec3( 1.0, 1.3302673723350029, 1.8993753891711275 ) )
			: glm::mat3(glm::vec3( 1745.0425298314172, 1216.6168361476490, -8257.7997278925690 ),
									glm::vec3( -2666.3474220535695, -2173.1012343082230, 2575.2827530017594 ),
									glm::vec3( 0.55995389139931482, 0.70381203140554553, 1.8993753891711275 ) );

	return glm::mix( glm::clamp( glm::vec3( m[ 0 ] / ( glm::vec3( glm::clamp( temperature, 1000.0, 40000.0 ) ) +
		m[ 1 ] ) + m[ 2 ] ), glm::vec3( 0.0 ), glm::vec3( 1.0 ) ), glm::vec3( 1.0 ), glm::smoothstep( 1000.0, 0.0, temperature ) );
}

#endif
