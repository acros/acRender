#version 400 core
in VS_OUT                  
{                          
    vec4 color;   
    float diff;
} fs_in;

uniform vec4 u_lightColor;
layout(location = 0) out vec4 outColor;

void main()
{
	outColor = fs_in.color * u_lightColor * fs_in.diff;
	outColor.a = 1;
}
