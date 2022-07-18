#include "../../engineCode/includes.h"

#ifndef FONTRENDERER_H
#define FONTRENDERER_H

class Layer {

};

class layerManager {
public:
	layerManager () {}

	void Init ( int w, int h ) {
		width = w;
		height = h;

		// how many complete 8x16px glyphs to cover the image ( x and y )
		numBinsWidth = std::floor( width / 8 );
		numBinsHeight = std::floor( height / 16 );

		// currently just two layers, background and foreground
		layers.resize( 2 );

		// compile the shader

		// get the uniform handles

		// allocate the textures

	}

	int width, height;
	int numBinsWidth;
	int numBinsHeight;

	GLuint writeTargetTexture;
	GLuint atlasTexture;

	std::vector< Layer > layers;
};

#endif
