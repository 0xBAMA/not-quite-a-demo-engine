#pragma once
#ifndef IMAGE_H
#define IMAGE_H

// Image Handling Libs

// Lode Vandevenne's LodePNG PNG Load/Save lib
#include "../ImageHandling/LodePNG/lodepng.h"

// Rich Geldrich's fpng - public domain, https://github.com/richgel999/fpng
#include "../ImageHandling/fpng/fpng.h"

// Sean Barrett's public domain load, save, resize libs - need corresponding define in the ./stb/impl.cc file, before their inclusion,
	// which is done by the time compilation hits this point - they can be straight included, here, as follows:

// https://github.com/nothings/stb/blob/master/stb_image.h
#include "../ImageHandling/stb/stb_image.h"
//  https://github.com/nothings/stb/blob/master/stb_image_write.h
#include "../ImageHandling/stb/stb_image_write.h"
// https://github.com/nothings/stb/blob/master/stb_image_resize.h
#include "../ImageHandling/stb/stb_image_resize.h"

#include <vector>
#include <random>
#include <string>
#include <iostream>

// considering templating this, or else just defining another couple classes
	// I will need an equivalent float image type, and I will need 1 and 4 component buffers made from this type ( depth, color + alpha )


// adding additional backends is as simple as adding an enum, writing the corresponding load/save implementation
enum backend {
	FPNG = 0,
	STB = 1,
	LODEPNG = 2
};

struct rgba {
	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;
	uint8_t a = 0;
};

constexpr float positiveMax = 10000.0f;

struct rgbaF {
	float r = positiveMax;
	float g = positiveMax;
	float b = positiveMax;
	float a = positiveMax;
};

class Image {
public:
	Image () : width( 0 ), height( 0 ) {
		data.clear();
	}

	Image ( int x, int y, bool randomize = false ) : width( x ), height( y ) {
		data.resize( width * height * numChannels, 0 );
		if ( randomize ) {
			std::random_device r;
			std::seed_seq s{ r(), r(), r(), r(), r(), r(), r(), r(), r() };
			auto gen = std::mt19937_64( s );
			std::uniform_int_distribution< uint8_t > dist( 0, 255 );
			for ( auto it = data.begin(); it != data.end(); it++ ) {
				*it = dist( gen );
				// *it = 255;
			}
		}
	}

	Image ( std::string path, backend loader = LODEPNG ) {
		if ( !Load( path, loader ) ) {
			std::cout << "image load failed with path " << path << std::endl << std::flush;
		}
	}

	Image ( int x, int y, uint8_t* contents ) :
		width( x ), height( y ) {
		data.resize( 0 );
		const int numBytes = x * y * 4;
		data.reserve( numBytes );
		// use incoming ordering
		for ( int i = 0; i < numBytes; i++ ) {
			data.push_back( contents[ i ] );
		}
	}

	void Blend ( Image& other, float alphaOriginal ) {
		// lerp between two images of the same size ( or just general )
		if ( width == other.width && height == other.height ) {
			// do the blend across the whole image
		}
	}

	bool Load ( std::string path, backend loader = FPNG ) {
		// stb can load non-png, others cannot
		bool result = false;
		if ( path.substr( path.find_last_of( "." ) ) != ".png" ) loader = STB;
		Clear(); // remove existing data
		switch ( loader ) {
			case FPNG:		result = Load_fpng( path ); 	break;
			case STB:		result = Load_stb( path ); 		break;
			case LODEPNG:	result = Load_lodepng( path ); 	break;
			default: break;
		}
		if ( !result ) { std::cout << "Image::Load Failed" << std::endl; }
		return result;
	}

	bool Save ( std::string path, backend loader = FPNG ) {
		switch ( loader ) {
			case FPNG:		return Save_fpng( path );
			case STB:		return Save_stb( path );
			case LODEPNG:	return Save_lodepng( path );
			default: break;
		}
		return false;
	}

	void CropTo ( int x, int y ) {
	// take this image data, and trim it, creating another image that is:
		// the original image data, within the bounds of the image data
		// black, 0 alpha, outside that bounds

		std::vector< uint8_t > newValues;
		newValues.resize( x * y * numChannels );
		for ( int yy = 0; yy < y; yy++ ) {
			for ( int xx = 0; xx < x; xx++ ) {
				rgba sample = GetAtXY( xx, yy );
				int index = 4 * ( xx + x * yy );
				newValues[ index + 0 ] = sample.r;
				newValues[ index + 1 ] = sample.g;
				newValues[ index + 2 ] = sample.b;
				newValues[ index + 3 ] = sample.a;
			}
		}
		data.resize( x * y * numChannels );
		for ( uint32_t i = 0; i < newValues.size(); i++ ) {
			data[ i ] = newValues[ i ];
		}
		width = x;
		height = y;
	}

	void FlipHorizontal () {
		// back up the existing state of the image
		std::vector< uint8_t > oldData;
		oldData.reserve( width * height * 4 );
		for ( auto c : data ) {
			oldData.push_back( c );
		}
		// flip it
		data.resize( 0 );
		data.reserve( width * height * 4 );
		for ( uint32_t y = 0; y < height; y++ ) {
			for ( uint32_t x = 0; x < width; x++ ) {
				data.push_back( oldData[ ( ( width - x - 1 ) + y * width ) * 4 + 0 ] );
				data.push_back( oldData[ ( ( width - x - 1 ) + y * width ) * 4 + 1 ] );
				data.push_back( oldData[ ( ( width - x - 1 ) + y * width ) * 4 + 2 ] );
				data.push_back( oldData[ ( ( width - x - 1 ) + y * width ) * 4 + 3 ] );
			}
		}
	}

	void FlipVertical () {
		// back up the existing state of the image
		std::vector< uint8_t > oldData;
		oldData.reserve( width * height * 4 );
		for ( auto c : data ) {
			oldData.push_back( c );
		}
		// flip it
		data.resize( 0 );
		data.reserve( width * height * 4 );
		for ( uint32_t y = 0; y < height; y++ ) {
			for ( uint32_t x = 0; x < width; x++ ) {
				data.push_back( oldData[ ( x + ( height - y - 1 ) * width ) * 4 + 0 ] );
				data.push_back( oldData[ ( x + ( height - y - 1 ) * width ) * 4 + 1 ] );
				data.push_back( oldData[ ( x + ( height - y - 1 ) * width ) * 4 + 2 ] );
				data.push_back( oldData[ ( x + ( height - y - 1 ) * width ) * 4 + 3 ] );
			}
		}
	}

	void Resize ( float scaleFactor ) {
		int newX = std::floor( scaleFactor * float( width ) );
	 	int newY = std::floor( scaleFactor * float( height ) );

		// do the resize
		const uint32_t oldSize = width * height * numChannels;
		uint8_t * oldData = ( uint8_t * ) malloc( oldSize );
		for ( uint32_t i = 0; i < oldSize; i++ ) {
			oldData[ i ] = data[ i ];
		}

		// buffer needs to be allocated before the resize function works
		uint8_t * newData = ( unsigned char * ) malloc( newX * newY * numChannels );
		stbir_resize_uint8( oldData, width, height, width * numChannels, newData, newX, newY, newX * numChannels, numChannels );

		// there's also a srgb version, would need to look at the extra parameters that it needs
			// stbir_resize_uint8_srgb( ... );

		// image dimensions are now scaled up by scaleFactor
		width = newX;
		height = newY;

		// copy new data back to the data vector
		data.resize( 0 );
		const uint32_t newSize = width * height * numChannels;
		data.reserve( newSize );
		for ( uint32_t i = 0; i < newSize; i++ ) {
			data.push_back( newData[ i ] );
		}
	}

	rgba GetAtXY ( uint32_t x, uint32_t y ) {
		rgba temp; // initialized with zeroes
		if ( x < 0 || x >= width || y < 0 || y >= height ) return temp;
		uint32_t index = ( x + y * width ) * numChannels;
		if ( index + 4 <= data.size() && index >= 0 && x < width && x >= 0 && y < height && y >= 0 ) {
			temp.r = data[ index + 0 ];
			temp.g = data[ index + 1 ];
			temp.b = data[ index + 2 ];
			temp.a = data[ index + 3 ];
		}
		return temp;
	}

	void SetAtXY ( uint32_t x, uint32_t y, rgba set ) {
		if ( x < 0 || x >= width || y < 0 || y >= height ) return;
		uint32_t index = ( x + y * width ) * numChannels;
		if ( index + 4 <= data.size() ) {
			data[ index + 0 ] = set.r;
			data[ index + 1 ] = set.g;
			data[ index + 2 ] = set.b;
			data[ index + 3 ] = set.a;
		}
	}

	enum class sortCriteria {
		red, green, blue, luma
	};

	struct {
		bool operator()( rgba a, rgba b ) const {
			// compute luma and compare
			float ra = ( a.r / 255.0 );
			float rb = ( b.r / 255.0 );

			float ga = ( a.g / 255.0 );
			float gb = ( b.g / 255.0 );

			float ba = ( a.b / 255.0 );
			float bb = ( b.b / 255.0 );

			float lumaA = sqrt( 0.299 * ra * ra + 0.587 * ga * ga + 0.114 * ba * ba );
			float lumaB = sqrt( 0.299 * rb * rb + 0.587 * gb * gb + 0.114 * bb * bb );
			return lumaA < lumaB;
		}
	} lumaLess;

	// color channel comparisons
	struct {
		bool operator()( rgba a, rgba b ) const {
			return a.r < b.r;
		}
	} redLess;

	struct {
		bool operator()( rgba a, rgba b ) const {
			return a.g < b.g;
		}
	} greenLess;

	struct {
		bool operator()( rgba a, rgba b ) const {
			return a.b < b.b;
		}
	} blueLess;

	void SortByRows ( sortCriteria howWeSortin ) {
		for ( uint32_t entry = 0; entry < height; entry++ ) {
			// collect the colors
			std::vector< rgba > row;
			for ( uint32_t x = 0; x < width; x++ )
				if ( GetAtXY( x, entry ).a == 0 ) {
					break;
				} else {
					row.push_back( GetAtXY( x, entry ) );
				}

			// sort them and put them back
			switch ( howWeSortin ) {
				case sortCriteria::luma:	std::sort( row.begin(), row.end(), lumaLess );	break;
				case sortCriteria::red:		std::sort( row.begin(), row.end(), redLess );		break;
				case sortCriteria::green:	std::sort( row.begin(), row.end(), greenLess );	break;
				case sortCriteria::blue:	std::sort( row.begin(), row.end(), blueLess );	break;
			}
			for ( uint32_t x = 0; x < row.size(); x++ )
				SetAtXY( x, entry, row[ x ] );
		}
	}

	void SortByCols ( sortCriteria howWeSortin ) {
		for ( uint32_t entry = 0; entry < width; entry++ ) {
			// collect the colors
			std::vector< rgba > col;
			for ( uint32_t y = 0; y < width; y++ )
				if ( GetAtXY( entry, y ).a == 0 ) {
					break;
				} else {
					col.push_back( GetAtXY( entry, y ) );
				}

			// sort them and put them back
			switch ( howWeSortin ) {
				case sortCriteria::luma:	std::sort( col.begin(), col.end(), lumaLess );	break;
				case sortCriteria::red:		std::sort( col.begin(), col.end(), redLess );		break;
				case sortCriteria::green:	std::sort( col.begin(), col.end(), greenLess );	break;
				case sortCriteria::blue:	std::sort( col.begin(), col.end(), blueLess );	break;
			}
			for ( uint32_t y = 0; y < col.size(); y++ )
				SetAtXY( entry, y, col[ y ] );
		}
	}

	void LumaSortByRows () {
		SortByRows( sortCriteria::luma );
	}

	void LumaSortByCols () {
		SortByCols( sortCriteria::luma );
	}

	std::vector< uint8_t > data;
	uint32_t width, height;

	// primarily deal with 8-bit, RGBA
	uint32_t bitDepth = 8;
	uint32_t numChannels = 4;

	rgba AverageColor () {
		float sums[ 4 ] = { 0, 0, 0, 0 };
		for( uint32_t y = 0; y < height; y++ ) {
			for( uint32_t x = 0; x < width; x++ ) {
				rgba val = GetAtXY( x, y );
				sums[ 0 ] += val.r / 255.0;
				sums[ 1 ] += val.g / 255.0;
				sums[ 2 ] += val.b / 255.0;
				sums[ 3 ] += val.a / 255.0;
			}
		}
		const float numPixels = width * height;
		rgba result;
		result.r = ( sums[ 0 ] / numPixels ) * 255;
		result.g = ( sums[ 1 ] / numPixels ) * 255;
		result.b = ( sums[ 2 ] / numPixels ) * 255;
		result.a = ( sums[ 3 ] / numPixels ) * 255;
		return result;
	}

private:

	void Reset () { data.resize( 0 ); width = 0; height = 0; };
	void Clear () { data.resize( 0 ); };

// ==== FPNG =========================================
	bool Load_fpng ( std::string path ) {
		uint32_t desired_channels = numChannels;
		int check = fpng::fpng_decode_file( path.c_str(), data, width, height, numChannels, desired_channels );
		if ( !check )
			return true;
		else {
			std::cout << "failed with error " << check << std::endl << std::flush;
			return false;
		}
	}

	bool Save_fpng ( std::string path ) {
		return fpng::fpng_encode_image_to_file( path.c_str(), &data[ 0 ], width, height, uint32_t( numChannels ) );
	}

// ==== STB_Image / STB_Image_Write =================
	// if extension is anything other than '.png', this is the only option
	bool Load_stb ( std::string path ) {
		int w = width;
		int h = height;
		int n = 0;
		unsigned char *image = stbi_load( path.c_str(), &w, &h, &n, STBI_rgb_alpha );
		data.resize( 0 );
		width = ( uint32_t ) w;
		height = ( uint32_t ) h;
		const uint32_t numPixels = width * height;
		data.reserve( numPixels * numChannels );
		for ( uint32_t i = 0; i < numPixels; i++ ) {
			data.push_back( image[ i * 4 + 0 ] );
			data.push_back( image[ i * 4 + 1 ] );
			data.push_back( image[ i * 4 + 2 ] );
			data.push_back( n == 4 ? image[ i * 4 + 3 ] : 255 );
		}
		return true;
	}

	bool Save_stb ( std::string path ) {
		// TODO: figure out return value semantics for error reporting, it's an int, I didn't read the header very closely
		return stbi_write_png( path.c_str(), width, height, 8, &data[ 0 ], width * numChannels );
	}

	// ==== LodePNG ======================================
	bool Load_lodepng ( std::string path ) {
		unsigned error = lodepng::decode( data, width, height, path.c_str() );
		if ( !error )
			return true;
		else {
			std::cout << "lodepng load error: " << lodepng_error_text( error ) << std::endl;
			return false;
		}
	}

	bool Save_lodepng ( std::string path ) {
		unsigned error = lodepng::encode( path.c_str(), data, width, height );
		if ( !error )
			return true;
		else {
			std::cout << "lodepng save error: " << lodepng_error_text( error ) << std::endl;
			return false;
		}
	}
};

class ImageF {
public:
	ImageF () : width( 0 ), height( 0 ) {
		data.clear();
	}

	ImageF ( int x, int y, bool randomize = false ) : width( x ), height( y ) {
		data.resize( width * height * numChannels, positiveMax );
		if ( randomize ) {
			std::random_device r;
			std::seed_seq s{ r(), r(), r(), r(), r(), r(), r(), r(), r() };
			auto gen = std::mt19937_64( s );
			std::uniform_real_distribution< float > dist( 0.0f, 1.0f );
			for ( auto it = data.begin(); it != data.end(); it++ ) {
				*it = dist( gen );
			}
		}
	}

	ImageF ( std::string path, backend loader = LODEPNG ) {
		Image temp( path, loader );
		width = temp.width;
		height = temp.height;
		data.resize( width * height * numChannels );
		for ( uint32_t y = 0; y < height; y++ ) {
			for ( uint32_t x = 0; x < width; x++ ) {
				rgba tempVal = temp.GetAtXY( x, y );
				rgbaF tempValF;
				tempValF.r = tempVal.r / 255.0;
				tempValF.g = tempVal.g / 255.0;
				tempValF.b = tempVal.b / 255.0;
				tempValF.a = tempVal.a / 255.0;
				SetAtXY( x, y, tempValF );
			}
		}
	}

	ImageF ( int x, int y, float* contents ) : width( x ), height( y ) {
		data.resize( 0 );
		const int numElements = x * y * 4;
		data.reserve( numElements );
		// use incoming ordering directly
		for ( int i = 0; i < numElements; i++ ) {
			data.push_back( contents[ i ] );
		}
	}

	// will need a save function, to save higher bitrate, maybe 16 bit png? LodePNG will do it

	void CropTo ( int x, int y ) {
	// take this image data, and trim it, creating another image that is:
		// the original image data, within the bounds of the image data
		// black, 0 alpha, outside that bounds
		std::vector< float > newValues;
		newValues.resize( x * y * numChannels );
		for ( int yy = 0; yy < y; yy++ ) {
			for ( int xx = 0; xx < x; xx++ ) {
				rgbaF sample = GetAtXY( xx, yy );
				int index = 4 * ( xx + x * yy );
				newValues[ index + 0 ] = sample.r;
				newValues[ index + 1 ] = sample.g;
				newValues[ index + 2 ] = sample.b;
				newValues[ index + 3 ] = sample.a;
			}
		}
		data.resize( x * y * numChannels );
		for ( uint32_t i = 0; i < newValues.size(); i++ ) {
			data[ i ] = newValues[ i ];
		}
		width = x;
		height = y;
	}

	void FlipHorizontal () {
		// back up the existing state of the image
		std::vector< float > oldData;
		oldData.reserve( width * height * 4 );
		for ( auto c : data ) {
			oldData.push_back( c );
		}
		// flip it
		data.resize( 0 );
		data.reserve( width * height * 4 );
		for ( uint32_t y = 0; y < height; y++ ) {
			for ( uint32_t x = 0; x < width; x++ ) {
				data.push_back( oldData[ ( ( width - x - 1 ) + y * width ) * 4 + 0 ] );
				data.push_back( oldData[ ( ( width - x - 1 ) + y * width ) * 4 + 1 ] );
				data.push_back( oldData[ ( ( width - x - 1 ) + y * width ) * 4 + 2 ] );
				data.push_back( oldData[ ( ( width - x - 1 ) + y * width ) * 4 + 3 ] );
			}
		}
	}

	void FlipVertical () {
		// back up the existing state of the image
		std::vector< float > oldData;
		oldData.reserve( width * height * 4 );
		for ( auto c : data ) {
			oldData.push_back( c );
		}
		// flip it
		data.resize( 0 );
		data.reserve( width * height * 4 );
		for ( uint32_t y = 0; y < height; y++ ) {
			for ( uint32_t x = 0; x < width; x++ ) {
				data.push_back( oldData[ ( x + ( height - y - 1 ) * width ) * 4 + 0 ] );
				data.push_back( oldData[ ( x + ( height - y - 1 ) * width ) * 4 + 1 ] );
				data.push_back( oldData[ ( x + ( height - y - 1 ) * width ) * 4 + 2 ] );
				data.push_back( oldData[ ( x + ( height - y - 1 ) * width ) * 4 + 3 ] );
			}
		}
	}

	rgbaF GetAtXY ( uint32_t x, uint32_t y ) {
		rgbaF temp; // initialized with zeroes
		if ( x < 0 || x >= width || y < 0 || y >= height ) return temp;
		uint32_t index = ( x + y * width ) * numChannels;
		if ( index + 4 <= data.size() && index >= 0 && x < width && x >= 0 && y < height && y >= 0 ) {
			temp.r = data[ index + 0 ];
			temp.g = data[ index + 1 ];
			temp.b = data[ index + 2 ];
			temp.a = data[ index + 3 ];
		}
		return temp;
	}

	void SetAtXY ( uint32_t x, uint32_t y, rgbaF set ) {
		if ( x < 0 || x >= width || y < 0 || y >= height ) return;
		uint32_t index = ( x + y * width ) * numChannels;
		if ( index + 4 <= data.size() ) {
			data[ index + 0 ] = set.r;
			data[ index + 1 ] = set.g;
			data[ index + 2 ] = set.b;
			data[ index + 3 ] = set.a;
		}
	}

	enum class sortCriteria {
		red, green, blue, luma
	};

	struct {
		bool operator()( rgbaF a, rgbaF b ) const {
			// compute luma and compare
			float lumaA = sqrt( 0.299 * a.r * a.r + 0.587 * a.g * a.g + 0.114 * a.b * a.b );
			float lumaB = sqrt( 0.299 * b.r * b.r + 0.587 * b.g * b.g + 0.114 * b.b * b.b );
			return lumaA < lumaB;
		}
	} lumaLess;

	// color channel comparisons
	struct {
		bool operator()( rgbaF a, rgbaF b ) const {
			return a.r < b.r;
		}
	} redLess;

	struct {
		bool operator()( rgbaF a, rgbaF b ) const {
			return a.g < b.g;
		}
	} greenLess;

	struct {
		bool operator()( rgbaF a, rgbaF b ) const {
			return a.b < b.b;
		}
	} blueLess;

	void SortByRows ( sortCriteria howWeSortin ) {
		for ( uint32_t entry = 0; entry < height; entry++ ) {
			// collect the colors
			std::vector< rgbaF > row;
			for ( uint32_t x = 0; x < width; x++ )
				if ( GetAtXY( x, entry ).a == 0 ) {
					break;
				} else {
					row.push_back( GetAtXY( x, entry ) );
				}

			// sort them and put them back
			switch ( howWeSortin ) {
				case sortCriteria::luma:	std::sort( row.begin(), row.end(), lumaLess );	break;
				case sortCriteria::red:		std::sort( row.begin(), row.end(), redLess );	break;
				case sortCriteria::green:	std::sort( row.begin(), row.end(), greenLess );	break;
				case sortCriteria::blue:	std::sort( row.begin(), row.end(), blueLess );	break;
			}
			for ( uint32_t x = 0; x < row.size(); x++ )
				SetAtXY( x, entry, row[ x ] );
		}
	}

	void SortByCols ( sortCriteria howWeSortin ) {
		for ( uint32_t entry = 0; entry < width; entry++ ) {
			// collect the colors
			std::vector< rgbaF > col;
			for ( uint32_t y = 0; y < width; y++ )
				if ( GetAtXY( entry, y ).a == 0 ) {
					break;
				} else {
					col.push_back( GetAtXY( entry, y ) );
				}

			// sort them and put them back
			switch ( howWeSortin ) {
				case sortCriteria::luma:	std::sort( col.begin(), col.end(), lumaLess );	break;
				case sortCriteria::red:		std::sort( col.begin(), col.end(), redLess );	break;
				case sortCriteria::green:	std::sort( col.begin(), col.end(), greenLess );	break;
				case sortCriteria::blue:	std::sort( col.begin(), col.end(), blueLess );	break;
			}
			for ( uint32_t y = 0; y < col.size(); y++ )
				SetAtXY( entry, y, col[ y ] );
		}
	}

	void LumaSortByRows () {
		SortByRows( sortCriteria::luma );
	}

	void LumaSortByCols () {
		SortByCols( sortCriteria::luma );
	}

	std::vector< float > data;
	uint32_t width, height;

	// primarily deal with 8-bit, RGBA
	uint32_t bitDepth = 8;
	uint32_t numChannels = 4;

	rgba AverageColor () {
		float sums[ 4 ] = { 0, 0, 0, 0 };
		for( uint32_t y = 0; y < height; y++ ) {
			for( uint32_t x = 0; x < width; x++ ) {
				rgbaF val = GetAtXY( x, y );
				sums[ 0 ] += val.r;
				sums[ 1 ] += val.g;
				sums[ 2 ] += val.b;
				sums[ 3 ] += val.a;
			}
		}
		const float numPixels = width * height;
		rgba result;
		result.r = ( sums[ 0 ] / numPixels );
		result.g = ( sums[ 1 ] / numPixels );
		result.b = ( sums[ 2 ] / numPixels );
		result.a = ( sums[ 3 ] / numPixels );
		return result;
	}

private:
	void Reset () { data.resize( 0.0f ); width = 0; height = 0; };
	void Clear () { data.resize( 0.0f ); };
};

#endif
