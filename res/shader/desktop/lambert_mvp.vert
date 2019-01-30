#version 400 core
uniform mat4 u_mvpMatrix;
//uniform vec4 light_dir;

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec4 a_normal;

/*
out VS_OUT                             
{                                      
    vec4 color;       
	float diff;
} vs_out; 
*/
out vec4 v_color;
void main()
{
    v_color = a_color;
//	vs_out.diff = max (0, dot(a_normal, light_dir));
    gl_Position = u_mvpMatrix * a_position;
}
