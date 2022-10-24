#include "../ImageHandling/Image.h"

class SoftRast {
public:
	SoftRast( uint32_t x = 0, uint32_t y = 0 ) : width( x ), height( y ) {
		Depth = Image( x, y );
		Color = Image( x, y );
	}
	Image Depth;
	Image Color;

	uint32_t width = 0;
	uint32_t height = 0;
};
