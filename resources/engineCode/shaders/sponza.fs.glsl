#version 430 core

in vec3 position;
in vec3 texCoord;
in vec3 normal;
in vec3 tangent;
in vec3 bitangent;
out vec4 fragmentOutput;

layout( binding = 1 ) uniform sampler2DArray textures;

uniform mat4 transform;
uniform vec3 lightPosition;

void main () {
	// texture array - use texcoord z value * 2 for color, * 2 + 1 for normals
	vec3 tcNormal = vec3( texCoord.xy, texCoord.z * 2.0f + 1.0f );
	vec3 tcColor = vec3( texCoord.xy, texCoord.z * 2.0f );

	vec4 texRefNormal = texture( textures, tcNormal );
	vec4 texRefColor = texture( textures, tcColor );

	// construct TBN locally, with interpolated normal
	mat3 TBN = mat3( tangent, bitangent, normal );
	vec3 nMappedNormal = normalize( TBN * ( texRefNormal.xyz * 2.0f - 1.0f ) );

	// skip blending, treat as 1-bit alpha
	if( texRefColor.a < 0.01f ) discard;

	// fragmentOutput = vec4( ( texRefColor.xyz + texRefNormal.xyz ) / 2.0f, 1.0f );
	// fragmentOutput = vec4( ( normal.xyz * 0.5f ) + 0.5f, 1.0f );
	// fragmentOutput = vec4( texRefColor.xyz, 1.0f );
	// fragmentOutput = vec4( bitangent, 1.0f );
	fragmentOutput = vec4( nMappedNormal * 0.5f + 0.5f, 1.0f );

}
