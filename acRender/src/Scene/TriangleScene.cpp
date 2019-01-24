#include "TriangleScene.h"
#include "Base/AcUtils.h"

static const GLushort vertex_indices[] =
{
	0, 1, 2,
};

TriangleScene::TriangleScene(Renderer& renderer)
	: Scene(renderer)
	, mUseElementDraw(false)
{
#if USE_OGL_3_LATEST
	mVertStr =
		"#version 330 core                         \n"
		"layout(location = 0) in vec4 vPosition;  \n"
		"layout (location = 1) in vec4 vColor;		\n"
		"out VS_OUT                                                         \n"
		"{                                                                  \n"
		"    vec4 color;                                                    \n"
		"} vs_out;                                                          \n"
		"void main()                              \n"
		"{                                        \n"
		"    vs_out.color = vColor;      \n"
		"   gl_Position = vPosition;              \n"
		"}                                        \n";

	mFragStr =
		"#version 330 core								\n"
		"out vec4 fragColor;                          \n"
		"in VS_OUT                                                                      \n"
		"{                                                                              \n"
		"    vec4 color;                                                                \n"
		"} fs_in;                                                                       \n"
		"void main()                                  \n"
		"{                                            \n"
		"   fragColor = fs_in.color;  \n"
		"}                                            \n";
#else
	mVertStr =
		"#version 300 es                          \n"
		"layout(location = 0) in vec4 vPosition;  \n"
		"layout (location = 1) in vec4 vColor;		\n"
		"void main()                              \n"
		"{                                        \n"
		"   gl_Position = vPosition;              \n"
		"}                                        \n";

	mFragStr =
		"#version 300 es                              \n"
		"precision mediump float;                     \n"
		"out vec4 fragColor;                          \n"
		"void main()                                  \n"
		"{                                            \n"
		"   fragColor = vColor;  \n"
		"}                                            \n";
#endif
}

TriangleScene::~TriangleScene()
{

}

void TriangleScene::enter()
{
	Scene::enter();
#if USE_OGL_3_LATEST

	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	GLfloat vVertices[] = {
		0.0f,  1.f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f };


	GLfloat vColors[] = {
		1.0f, 0.0f,0.0f,
		0.0f, 1.0f,0.0f,
		0.0f, 0.0f,1.0f,
	};

	glEnableVertexAttribArray(0);//For Vertex
	glGenBuffers(1, &mPosBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mPosBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vVertices), vVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);

	glEnableVertexAttribArray(1);//For Color
	glGenBuffers(1, &mColorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mColorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vColors), vColors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),NULL /*(GLvoid *)(3 * sizeof(GLfloat))*/);

	if (!mUseElementDraw)
	{
		glGenBuffers(1, &mIdxBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIdxBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indices), vertex_indices, GL_STATIC_DRAW);
	}

#endif
}

void TriangleScene::render()
{
	mRendererRef.beginDraw();

	// Use the program object
	glUseProgram(mShaderProgram);

#if USE_OGL_3_LATEST
	glUseProgram(mShaderProgram);

	//Warning: After OpenGL 3.3 , VAO is deprecated
	if (mUseElementDraw)
	{
		//Always update the indices
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, vertex_indices);
	}
	else
	{
		//Use the preset indices , better performance
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIdxBuffer);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

#else
	GLint Posid = 0;
	glVertexAttribPointer(Posid, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
	glEnableVertexAttribArray(Posid);
	
	//the next triangle
	// 	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, vColors);
	// 	glEnableVertexAttribArray(1);

	glDrawArrays(GL_TRIANGLES, 0, 3);
#endif

	mRendererRef.endDraw();
}

void TriangleScene::exit()
{
	Scene::exit();

	glDeleteVertexArrays(1, &mVAO);
	glDeleteBuffers(1, &mPosBuffer);
	glDeleteBuffers(1, &mColorBuffer);
	
//	glDeleteFramebuffers(1, &mFBO);

}
