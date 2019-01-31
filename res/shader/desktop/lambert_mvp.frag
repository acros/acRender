#version 400 core
in VS_OUT                  
{                          
    vec4 color;   
} fs_in;

layout(location = 0) out vec4 outColor;

void main()
{
    outColor = fs_in.color;
	outColor.a = 1;
}
