#version 400 core
uniform mat4 u_mvpMatrix;
uniform mat4 u_WorldMatrix;
uniform vec4 u_light_dir;
uniform vec4 u_lightColor;

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec4 a_normal;

out VS_OUT                             
{                                      
    vec4 color;       
} vs_out; 

void main()
{
//    world_normal = normalize(mat3(u_WorldMatrix) *world_normal);
    float diff = max(0, dot(u_light_dir,a_normal));
	vs_out.color = diff * a_color *  u_lightColor ;
    gl_Position = u_mvpMatrix * a_position;
}
