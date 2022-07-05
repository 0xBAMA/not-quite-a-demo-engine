#pragma once
#ifndef IMAGE_H
#define IMAGE_H

// Image Handling Libs

// Lode Vandevenne's LodePNG PNG Load/Save lib
// key functions:
	// load: unsigned error = lodepng::decode( byte vector, unsigned width, unsigned height, cstr path )
	// save: unsigned error = lodepng::encode( cstr path, byte vector, unsigned width, unsigned height, channel count enum, bit depth )
#include "../ImageHandling/LodePNG/lodepng.h"

// Sean Barrett's public domain load, save, resize libs - need corresponding define in the stb/impl.cc file, before their inclusion,
	// which is done by the time compilation hits this point - they can be straight included, here, as follows:
#include "../ImageHandling/stb/stb_image.h"					// stb_image - https://github.com/nothings/stb/blob/master/stb_image.h
#include "../ImageHandling/stb/stb_image_write.h"		// stb_image_write - https://github.com/nothings/stb/blob/master/stb_image_write.h
#include "../ImageHandling/stb/stb_image_resize.h"	// stb_image_resize - https://github.com/nothings/stb/blob/master/stb_image_resize.h

// Rich Geldrich's fpng - public domain, https://github.com/richgel999/fpng
#include "../ImageHandling/fpng/fpng.h"

#include <vector>
#include <random>
#include <string>

// adding additional backends is as simple as adding an enum, writing the corresponding load/save implementation
enum backend {
	FPNG = 0,
	STB = 1,
	LODEPNG = 2
};

class Image {
public:
	Image () : width( 0 ), height( 0 ) {
		data.clear();
	}

	Image ( int x, int y, bool randomize = false ) : width( x ), height( y ) {
		data.resize( width * height * numChannels );
		if ( randomize ) {
			std::random_device r;
			std::seed_seq s{ r(), r(), r(), r(), r(), r(), r(), r(), r() };
			auto gen = std::mt19937_64( s );
			std::uniform_int_distribution< uint8_t > dist( 0, 255 );
			for ( auto it = data.begin(); it != data.end(); it++ ) {
				*it = dist( gen );
			}
		}
	}

	Image ( std::string path, backend loader = FPNG ) {
		Load( path, loader );
	}

	Image ( int x, int y, uint8_t* contents, bool invertY = false ) :
		width( x ), height( y ) {
		// sometimes stuff coming from OpenGL is upside down, handy to have
		data.resize( 0 );
		const int numBytes = x * y * 4;
		data.reserve( numBytes );
		if ( invertY ) {
			// flip the image on the y

		} else {
			for ( int i = 0; i < numBytes; i++ ) {
				data.push_back( contents[ i ] );
			}
		}
	}

	bool Load ( std::string path, backend loader = FPNG ) {
		// check the extension, if not equal to .png, set loader = STB
		switch ( loader ) {
			case FPNG:		return Load_fpng( path );
			case STB:			return Load_stb( path );
			case LODEPNG: return Load_lodepng( path );
			default: break;
		}
		return false;
	}

	bool Save ( std::string path, backend loader = FPNG ) {
		// check the extension, if not equal to .png, set loader = STB
		switch ( loader ) {
			case FPNG:		return Save_fpng( path );
			case STB:			return Save_stb( path );
			case LODEPNG:	return Save_lodepng( path );
			default: break;
		}
		return false;
	}

	void Resize ( float scaleFactor ) {
		// tbd, uses stb_image_resize
	}

	std::vector< uint8_t > data;
	uint32_t width, height;

	// primarily deal with 8-bit, RGBA
	uint8_t bitDepth = 8;
	uint8_t numChannels = 4;

private:
// ==== FPNG =========================================
	bool Load_fpng ( std::string path ) {

		return false;
	}
	bool Save_fpng ( std::string path ) {

		return false;
	}

// ==== STB_Image / STB_Image_Write =================
	// if extension is anything other than '.png', this is the only option
	bool Load_stb ( std::string path ) {

		return false;
	}

	bool Save_stb ( std::string path ) {

		return false;
	}

	// ==== LodePNG ======================================
	bool Load_lodepng ( std::string path ) {

		return false;
	}
	bool Save_lodepng ( std::string path ) {

		return false;
	}
};

#endif
