#version 430
layout( local_size_x = 8, local_size_y = 16, local_size_z = 1 ) in;
layout( binding = 0, rgba8ui ) uniform uimage2D fontAtlas;
layout( binding = 1, rgba8ui ) uniform uimage2D dataTexture;
layout( binding = 2, rgba8ui ) uniform uimage2D writeTarget;

ivec2 getCurrentGlyphBase( uint index ) {
	// 16x16 array of glyphs, each of which is 8x16 pixels
	return ivec2( 0 );
}

void main () {
	// location within the compute dispatch
	ivec2 invokeLoc = ivec2( gl_GlobalInvocationID.xy );

	// which glyph ID/character color to pull dataTexture
	ivec2 bin = ivec2( invokeLoc.x / 8, invokeLoc.y / 16 );
	// where to reference the fontAtlas' glyph ( uv ), for the given character ID
	ivec2 loc = ivec2( invokeLoc.x % 8, invokeLoc.y % 16);

	// figure out which glyph is being used by reading the data texture ( +its color )
	uvec4 dataTexRead = imageLoad( dataTexture, bin );

	// dataTexRead.xyz is the desired color
	// dataTexRead.a is the index 0-255 of the current glyph

	// sample the atlas texture to get the sample on the glyph for this pixel
	// uvec4 color = imageLoad( fontAtlas, ivec2( invokeLoc ) );
	uvec4 color = dataTexRead;

	// if nonzero alpha, write to the write target
	if ( color.a > 0 ) imageStore( writeTarget, invokeLoc, color );
}
