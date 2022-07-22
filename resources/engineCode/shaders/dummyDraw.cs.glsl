#version 430
layout( local_size_x = 16, local_size_y = 16, local_size_z = 1 ) in;
layout( binding = 0, rgba8ui ) uniform uimage2D blueNoiseTexture;
layout( binding = 1, rgba8ui ) uniform uimage2D accumulatorTexture;

void main () {
	// basic XOR pattern
	uint x = uint( gl_GlobalInvocationID.x ) % 256;
	uint y = uint( gl_GlobalInvocationID.y ) % 256;
	uvec3 result = uvec3( x ^ y );

	ivec2 writeLoc = ivec2( gl_GlobalInvocationID.xy );

	imageStore( accumulatorTexture, writeLoc, uvec4( result, 255 ) );
}
