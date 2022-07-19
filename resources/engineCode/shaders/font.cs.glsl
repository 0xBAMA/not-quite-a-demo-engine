#version 430
layout( local_size_x = 8, local_size_y = 8, local_size_z = 1 ) in;
layout( binding = 0, rgba8ui ) uniform uimage2D fontAtlas;
layout( binding = 1, rgba8ui ) uniform uimage2D dataTexture;
layout( binding = 2, rgba8ui ) uniform uimage2D writeTarget;

void main () {
	// location within the compute dispatch
	uvec2 invokeLoc = uvec2( gl_GlobalInvocationID.xy );

	// which glyph ID/character color to pull dataTexture
	uvec2 bin = uvec2( invokeLoc.x / 8, invokeLoc.y / 16 );
	// where to reference the fontAtlas' glyph ( uv ), for the given character ID
	uvec2 loc = uvec2( invokeLoc.x % 8, invokeLoc.y % 16);

	// figure out which glyph is being used

	// sample the atlas texture

	// if nonzero alpha, write to the write target

}
