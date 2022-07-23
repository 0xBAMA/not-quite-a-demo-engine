#version 430
layout( local_size_x = 16, local_size_y = 16, local_size_z = 1 ) in;
layout( binding = 0, rgba8ui ) uniform uimage2D accumulatorTexture;
layout( binding = 1, rgba8ui ) uniform uimage2D displayTexture;
#include "tonemap.glsl" // tonemapping curves

// TODO: add uniform int for picking tonemapping curve + float for gamma
const int tonemapPicker = 6; // values are 0-15
const float gamma =  1.0;

// and then maybe the color temperature adjustment could be applied here

void main () {
	ivec2 loc = ivec2( gl_GlobalInvocationID.xy );
	uvec4 originalValue = imageLoad( accumulatorTexture, loc );

	vec3 color = tonemap( tonemapPicker, vec3( originalValue.xyz ) / 255.0 );
	color = gammaCorrect( gamma, color );
	uvec4 tonemappedValue = uvec4( uvec3( color * 255.0 ), originalValue.a );

	imageStore( displayTexture, loc, tonemappedValue );
}
