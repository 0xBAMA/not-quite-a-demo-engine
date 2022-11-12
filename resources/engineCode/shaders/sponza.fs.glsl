#version 430 core

in vec3 position;
in vec3 texCoord;
in vec3 normal;
in vec3 tangent;
in vec3 bitangent;

uniform mat4 transform;

layout( binding = 1 ) uniform sampler2DArray textures;

out vec4 fragmentOutput;

void main () {
	// texture array - use texcoord z value * 2 for color, * 2 + 1 for normals
	vec3 tcNormal = vec3( texCoord.xy, texCoord.z * 2.0f + 1.0f );
	vec3 tcColor = vec3( texCoord.xy, texCoord.z * 2.0f );

	vec4 texRefNormal = texture( textures, tcNormal );
	vec4 texRefColor = texture( textures, tcColor );

	// skip blending
	if( texRefColor.a < 0.01f ) discard;

	// fragmentOutput = vec4( ( texRefColor.xyz + texRefNormal.xyz ) / 2.0f, 1.0f );
	// fragmentOutput = vec4( ( normal.xyz * 0.5f ) + 0.5f, 1.0f );
	fragmentOutput = vec4( texRefColor.xyz, 1.0f );
}
