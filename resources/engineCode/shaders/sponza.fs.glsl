#version 430 core

in vec3 position;
in vec3 texCoord;
in vec3 normal;

// texture array - use texcoord z value * 2 for color, * 2 + 1 for normals
uniform sampler2DArray textures;

out vec4 fragmentOutput;

void main () {
	// fragmentOutput = vec4( 0.5f * normal + 0.5f, 1.0f );

	vec3 t = vec3( texCoord.xy, texCoord.z * 2.0f );

	vec4 texRef = texture( textures, t );
	if( texRef.a < 0.01f ) discard;

	fragmentOutput = vec4( texRef );
}
