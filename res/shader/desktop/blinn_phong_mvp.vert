#version 400 core
uniform mat4 u_mvpMatrix;
uniform vec4 u_light_dir;
uniform vec4 u_eye_pos;
uniform float u_specular;

layout(location = 0) in vec4 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec4 a_normal;

out VS_OUT                             
{                                      
    vec4 color;       
    float diff;
	float spec;
} vs_out; 

void main()
{
    viewDir = normalize(a_position - u_eye_pos);
    float h = normalize (light.dir + viewDir);
    float nh = max (0, dot (a_normal, h));

	vs_out.spec = pow (nh, u_specular*128.0) ; //* gloss;
    vs_out.color = a_color;
    vs_out.diff = max (0, dot(a_normal, u_light_dir));
    gl_Position = u_mvpMatrix * a_position;
}
