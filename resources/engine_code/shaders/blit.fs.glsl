#version 430 core
layout( binding = 0, rgba8ui ) uniform uimage2D current;

in vec2 v_pos;
out vec4 fragment_output;

void main()
{
	vec2 lv_pos = v_pos/2.0f + vec2(0.5);

	uvec4 s = imageLoad(current, ivec2(lv_pos.x*imageSize(current).x, lv_pos.y*imageSize(current).y));

	fragment_output = vec4(float(s.r)/256.0,float(s.g)/256.0,float(s.b)/256.0,float(s.a)/256.0);
}
