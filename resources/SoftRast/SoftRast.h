#ifndef SOFTRAST
#define SOFTRAST

#include "../engineCode/includes.h"

static const float remapRange ( const float value, const float iMin, const float iMax, const float oMin, const float oMax ) {
	return ( oMin + ( ( oMax - oMin ) / ( iMax - iMin ) ) * ( value - iMin ) );
}

class SoftRast {
public:
	SoftRast( uint32_t x = 0, uint32_t y = 0 ) : width( x ), height( y ) {
		Depth = ImageF( x, y );
		Color = Image( x, y );
	}

	// draw dot - draw smooth? tbd, some kind of gaussian distribution, how do you handle depth?
	// draw line
	// draw triangle

	// something to draw a model, using TinyOBJLoader wrapper

	uint32_t width = 0;
	uint32_t height = 0;
	ImageF Depth;
	Image Color;
};

#endif
