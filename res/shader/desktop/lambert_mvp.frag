#version 400 core
/*    
in VS_OUT                  
{                          
    vec4 color;       
	float diff;
} fs_in;
*/
//uniform vec4 lightColor;
in vec4 v_color;
layout(location = 0) out vec4 outColor;

void main()
{
    outColor = v_color;
//	outColor = fs.color * lightColor * diff;
//	outColor.a = 1;
}
