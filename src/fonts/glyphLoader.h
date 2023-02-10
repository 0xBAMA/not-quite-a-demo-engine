#pragma once
#ifndef GLYPH_H
#define GLYPH_H

// #include "../GLM/glm.hpp"
#include "../ImageHandling/Image.h"

struct glyph {
	int index = 0;
	std::vector< std::vector< bool > > glyphData;
};

constexpr rgba clear {   0,   0,   0,   0 };
constexpr rgba black {  69,  69,  69, 255 };
constexpr rgba white { 205, 205, 205, 255 };
static bool isBlackOrWhite( rgba check ) {
	return check == black || check == white;
}


static std::vector< glyph > glyphList;

static void readGlyphAt ( uint32_t x, uint32_t y, Image &buffer ) {
	// find the footprint of the glyph
	glyph g;


	// because of how we iterate across the image we know that x,y is the top left corner
	uint32_t xcur = x, ycur = y;

	// determine x extent
	while ( 1 ) {
		if ( isBlackOrWhite( buffer.GetAtXY( xcur, y ) ) ) {
			xcur++;
		} else {
			xcur--;
			break;
		}
	}

	// determine y extent
	while ( 1 ) {
		if ( isBlackOrWhite( buffer.GetAtXY( x, ycur ) ) ) {
			ycur++;
		} else {
			ycur--;
			break;
		}
	}

	// size the arrays
	const int xdim = xcur - x + 1;
	const int ydim = ycur - y + 1;

	g.glyphData.resize( ydim );
	for ( unsigned int i = 0; i < g.glyphData.size(); i++ ) { g.glyphData[ i ].resize( xdim ); }

	std::cout << "reading in a glyph of size " << xdim << " by " << ydim << std::endl;

	// read in the footprint of the glyph, store it in the glyph object
	for ( uint32_t yy = y; yy <= ycur; yy++ ) {
		for ( uint32_t xx = x; xx <= xcur; xx++ ) {
			rgba read = buffer.GetAtXY( xx, yy );
			if ( read == black ) {
				g.glyphData[ yy ][ xx ] = false;
			} else if ( read == white ) {
				g.glyphData[ yy ][ xx ] = true;
			} else {
				std::cout << "you fucked up... i fucked up...." << std::endl;
			}

			// zero out the footprint of the glyph, so it is not recounted
			buffer.SetAtXY( xx, yy, clear );
		}
	}

	std::cout << "done" << std::endl;

	// get the index from the colored drop shadow
	rgba dexx = buffer.GetAtXY( xcur + 1, ycur + 1 );
	g.index = dexx.b * 255 * 255 + dexx.g * 255 + dexx.r;

	glyphList.push_back( g );
}

static void loadGlyphs () {
	Image glyphRecord( "./src/fonts/bitfontCore2.png" );
	// iterate through all the pixels in the image
	for ( uint32_t y = 0; y < glyphRecord.height; y++ ) {
		for ( uint32_t x = 0; x < glyphRecord.width; x++ ) {
			if ( isBlackOrWhite( glyphRecord.GetAtXY( x, y ) ) ) {
				readGlyphAt( x, y, glyphRecord );
			}
		}
	}
	glyphRecord.Save( "./src/fonts/afterOne.png" );
}

#endif // GLYPH_H