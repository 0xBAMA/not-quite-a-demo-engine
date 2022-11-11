#version 430 core

in vec3 position;
in vec3 texCoord;
in vec3 normal;

// texture array - use texcoord z value * 2 for color, * 2 + 1 for normals
// sampler2DArray

out vec4 fragmentOutput;

void main () {
	fragmentOutput = vec4( 0.5f * normal + 0.5f, 1.0f );
}
