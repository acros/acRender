#version 400 core
in VS_OUT                  
{                          
    vec4 color;   
    float diff;
	float spec;
} fs_in;

uniform vec4 u_lightColor;
uniform vec4 u_specualr_color;
layout(location = 0) out vec4 outColor;

void main()
{
	outColor = fs_in.color * u_lightColor * fs_in.diff +
	u_specualr_color * u_lightColor * spec;

	outColor.a = 1;
}
