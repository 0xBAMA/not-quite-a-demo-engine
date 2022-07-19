#include "../../engineCode/includes.h"

#ifndef FONTRENDERER_H
#define FONTRENDERER_H

struct cChar {
	unsigned char data[ 4 ] = { 255, 255, 255, 0 };
	cChar() {}
	cChar( unsigned char c ) {
		data[ 3 ] = c;
	}
	cChar( glm::ivec3 color, unsigned char c ) {
		data[ 0 ] = color.x;
		data[ 1 ] = color.y;
		data[ 2 ] = color.z;
		data[ 3 ] = c;
	}
};

class Layer {
public:
	Layer ( int w, int h ) : width( w ), height( h ) {
		Resize( w, h );
	}

	void Resize ( int w, int h ) {
		if ( bufferBase != nullptr ) { free( bufferBase ); }
		bufferBase = ( cChar * ) malloc( sizeof( cChar ) * w * h );
	}

	void Draw () {
		// dispatch the compute shader
	}

	int width, height;
	GLuint textureHandle;
	bool bufferDirty;
	cChar * bufferBase = nullptr;
};

class layerManager {
public:
	layerManager () {}
	void Init ( int w, int h, GLuint shader ) {
		width = w;
		height = h;

		// how many complete 8x16px glyphs to cover the image ( x and y )
		numBinsWidth = std::floor( width / 8 );
		numBinsHeight = std::floor( height / 16 );

		// currently just two layers, background and foreground
		layers.push_back( Layer( numBinsWidth, numBinsHeight ) );
		layers.push_back( Layer( numBinsWidth, numBinsHeight ) );

		// get the compiled shader
		fontWriteShader = shader;

		// generate the altas texture - only ever needed in the context of layerManager
		Image fontAtlas( "resources/fonts/fontRenderer/whiteOnClear.png", LODEPNG );
		// fontAtlas.FlipHorizontal();
		fontAtlas.FlipVertical();

		glGenTextures( 1, &atlasTexture );
		glActiveTexture( GL_TEXTURE0 );
		glBindTexture( GL_TEXTURE_2D, atlasTexture );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, fontAtlas.width, fontAtlas.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &fontAtlas.data.data()[ 0 ] );
		glBindImageTexture( 1, atlasTexture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA8UI );

	}

	void Draw ( GLuint writeTarget ) {
		glUseProgram( fontWriteShader );
		// bind the appropriate textures ( atlas + write target )
		for ( auto layer : layers ) {
			layer.Draw(); // data texture is bound internal to this function
		}
	}

	int width, height;
	int numBinsWidth;
	int numBinsHeight;

	GLuint fontWriteShader;
	GLuint atlasTexture;

	// allocation of the textures happens in Layer()
	std::vector< Layer > layers;
};

#endif
