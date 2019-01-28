#include "Material.h"

void Material::loadShader(Renderer& context,const string& vert, const string& frag)
{
#if USE_OGL_3_LATEST
	string vertStr =
		"#version 450 core									\n"
		"uniform mat4 u_mvpMatrix;                         \n"
		"layout(location = 0) in vec4 a_position;          \n"
		"layout(location = 1) in vec4 a_color;             \n"			//TODO: use texCoord here
		"out vec4 v_color;                                 \n"
		"													\n"
		"void main()                                       \n"
		"{                                                 \n"
		"   v_color = a_color;                             \n"
		"   gl_Position = u_mvpMatrix * a_position;        \n"
		"}                                                 \n";

	string fragStr =
		"#version 450 core                         \n"
		"in vec4 v_color;                                   \n"
		"layout(location = 0) out vec4 outColor;            \n"
		"                                                   \n"
		"void main()                                        \n"
		"{                                                  \n"
		"   outColor = v_color ;	                        \n"
		"}                                                  \n";
#else

	string vertStr =
		"#version 300 es                                   \n"
		"uniform mat4 u_mvpMatrix;                         \n"
		"layout(location = 0) in vec4 a_position;          \n"
		"layout(location = 1) in vec4 a_color;             \n"			//TODO: use texCoord here
		"out vec4 v_color;                                 \n"
		"													\n"
		"void main()                                       \n"
		"{                                                 \n"
		"   v_color = a_color;                             \n"
		"   gl_Position = u_mvpMatrix * a_position;        \n"
		"}                                                 \n";

	string fragStr =
		"#version 300 es                                    \n"
		"precision lowp float;                              \n"
		"in vec4 v_color;                                   \n"
		"layout(location = 0) out vec4 outColor;            \n"
		"                                                   \n"
		"void main()                                        \n"
		"{                                                  \n"
		"   outColor = v_color ;	                        \n"
		"}                                                  \n";
#endif
	if (vert.empty() || frag.empty())
	{
		mShaderProgram = context.loadShaderProgram(vertStr.c_str(), fragStr.c_str());
		mMvpLoc = glGetUniformLocation(mShaderProgram, "u_mvpMatrix");
	}
	else
	{
		mShaderProgram = context.loadShaderProgram(vert.c_str(), frag.c_str());
	}

}

/*
void Material::loadSimpleShader(Renderer & context)
{
	string vert, frag;
#if USE_OGL_3_LATEST
	vert =
		"#version 450 core                         \n"
		"uniform mat4 u_mvpMatrix;                  \n"
		"layout(location = 0) in vec4 a_position;   \n"
		"layout(location = 1) in vec4 a_color;      \n"
		"out vec4 v_color;\n"
		"void main()\n"
		"{\n"
		"    v_color = a_color;                     \n"
		"   gl_Position = u_mvpMatrix * a_position;        \n"
		"}\n";


	frag =
		"#version 450 core                         \n"
		"in vec4 v_color;\n"
		"out vec4 o_fragColor;\n"
		"void main()\n"
		"{\n"
		"    o_fragColor = v_color; \n"
		"}\n";
#else

	vert =
		"#version 300 es                            \n"
		"layout(location = 0) in vec4 a_position;   \n"
		"layout(location = 1) in vec4 a_color;      \n"
		"uniform float u_offset;                    \n"
		"out vec4 v_color;                          \n"
		"void main()                                \n"
		"{                                          \n"
		"    v_color = a_color;                     \n"
		"    gl_Position = a_position;              \n"
		"    gl_Position.x += u_offset;             \n"
		"}";

	frag =
		"#version 300 es            \n"
		"precision mediump float;   \n"
		"in vec4 v_color;           \n"
		"out vec4 o_fragColor;      \n"
		"void main()                \n"
		"{                          \n"
		"    o_fragColor = v_color; \n"
		"}";
#endif

	mShaderProgram = context.loadShaderProgram(vert.c_str(), frag.c_str());
	mMvpLoc = glGetUniformLocation(mShaderProgram, "u_mvpMatrix");
}
*/