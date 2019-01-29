#include "TextureScene.h"
#include "Base/AcUtils.h"


TextureScene::TextureScene(Renderer& renderer)
	: Scene(renderer)
	, mSampleLocation(0)
	, mTexId(0)
{

#if USE_OGL_3_LATEST
	mVertStr =
		"#version 450 core                         \n"
		"                                           \n"
		"layout(location = 0) in vec4 a_position;   \n"
		"layout(location = 1) in vec2 a_texCoord;   \n"
		"                                           \n"
		"out vec2 v_texCoord;                       \n"
		"void main()                                \n"
		"{                                          \n"
		"   gl_Position = a_position;               \n"
		"   v_texCoord = a_texCoord;                \n"
		"}                                          \n";

	mFragStr =
		"#version 450 core                         \n"
		"in vec2 v_texCoord;                                 \n"
		"layout(location = 0) out vec4 outColor;             \n"
		"uniform sampler2D s_texture;                        \n"
		"void main()                                         \n"
		"{                                                   \n"
		"  outColor = texture( s_texture, v_texCoord );      \n"
		"}                                                   \n";
#else
	mVertStr =
		"#version 300 es                            \n"
		"layout(location = 0) in vec4 a_position;   \n"
		"layout(location = 1) in vec2 a_texCoord;   \n"
		"out vec2 v_texCoord;                       \n"
		"void main()                                \n"
		"{                                          \n"
		"   gl_Position = a_position;               \n"
		"   v_texCoord = a_texCoord;                \n"
		"}                                          \n";

	mFragStr =
		"#version 300 es                                     \n"
		"precision mediump float;                            \n"
		"in vec2 v_texCoord;                                 \n"
		"layout(location = 0) out vec4 outColor;             \n"
		"uniform sampler2D s_texture;                        \n"
		"void main()                                         \n"
		"{                                                   \n"
		"  outColor = texture( s_texture, v_texCoord );      \n"
		"}                                                   \n";
#endif
}


TextureScene::~TextureScene()
{
	// Delete texture object
	glDeleteTextures(1, &mTexId);
}

void TextureScene::enter()
{
	Scene::enter();

	glUseProgram(mShaderProgram);

	// Set the sampler texture unit to 0
//	mSampleLocation = glGetUniformLocation(mShaderProgram, "s_texture");
	mTexId = createSimpleTexture2D();

	//VBO rely on VAO
	glGenVertexArrays(1, &mBaseVAO);
	glBindVertexArray(mBaseVAO);
	GLfloat vVertices[] = {
			-0.5f,  0.5f, 0.0f,  // Position 0
			0.0f,  0.0f,        // TexCoord 0 

			-0.5f, -0.5f, 0.0f,  // Position 1
			0.0f,  1.0f,        // TexCoord 1

			0.5f, -0.5f, 0.0f,  // Position 2
			1.0f,  1.0f,        // TexCoord 2

			0.5f,  0.5f, 0.0f,  // Position 3
			1.0f,  0.0f         // TexCoord 3
	};
	GLushort rect_indices[] = { 0, 1, 2, 0, 2, 3 };

	glGenBuffers(1, &mBaseVtxBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mBaseVtxBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vVertices), vVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), NULL);// (GLfloat*)vVertices);
	glEnableVertexAttribArray(0);//For Vertex

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));// offset);
	glEnableVertexAttribArray(1);//For UV

	glGenBuffers(1, &mBaseVboIndicesBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBaseVboIndicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,  sizeof(rect_indices), rect_indices, GL_STATIC_DRAW);

}

void TextureScene::render()
{
	mRendererRef.beginDraw();

	// Bind the texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTexId);

	glUseProgram(mShaderProgram);

//  glBindVertexArray(mVaoId);
 	glBindBuffer(GL_ARRAY_BUFFER, mBaseVtxBuffer);
 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBaseVboIndicesBuffer);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

//	glUniform1i(mSampleLocation, 0);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
//	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	mRendererRef.endDraw();
}

void TextureScene::exit()
{
	Scene::exit();



}


GLuint TextureScene::createSimpleTexture2D()
{
	// Texture object handle
	GLuint textureId;

	// 2x2 Image, 3 bytes per pixel (R, G, B)
	GLubyte pixels[4 * 3] =
	{
		255,   0,   0, // Red
		0, 255,   0, // Green
		0,   0, 255, // Blue
		255, 255,   0  // Yellow
	};

	// Use tightly packed data
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Generate a texture object
	glGenTextures(1, &textureId);

	// Bind the texture object
	glBindTexture(GL_TEXTURE_2D, textureId);

	// Load the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	// Set the filtering mode
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	return textureId;
}
