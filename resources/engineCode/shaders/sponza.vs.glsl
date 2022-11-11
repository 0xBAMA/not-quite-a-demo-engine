#version 430

layout( location = 0 ) in vec3 vPosition;
layout( location = 1 ) in vec3 vTexCoord;
layout( location = 2 ) in vec3 vNormal;

out vec3 position;
out vec3 texCoord;
out vec3 normal;

uniform mat4 perspective;
uniform vec3 offset;

void main () {
	position = mat3( 0.0024f ) * vPosition;
	// position = vPosition;
	texCoord = vTexCoord;
	normal = vNormal;

	gl_Position = perspective * vec4( position, 1.0f );
}
