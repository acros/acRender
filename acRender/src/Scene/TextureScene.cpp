#include "TextureScene.h"
#include "Base/AcUtils.h"
#include "File/AcFileManager.h"

const GLsizei width = 3;
const GLsizei height = 3;
GLubyte pixels[width * height * 3];

TextureScene::TextureScene(Renderer& renderer)
	: Scene(renderer)
	, mSampleLocation(0)
	, mTexId(0)
	, mTexUpdateDuration(3)
	, mTimeAcculation(0)
	, mSubmitTex(false)
{
	Acros::FileManager::loadShaderFile("tex_2d.vert", mVertStr);
	Acros::FileManager::loadShaderFile("tex_2d.frag", mFragStr);
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

void TextureScene::update(float delta)
{
	Scene::update(delta);

	mTimeAcculation += delta;
	if (mTimeAcculation > mTexUpdateDuration)
	{
		mTimeAcculation = 0;

		for (int i = 0; i < width * height * 3; ++i)
		{
			pixels[i] = rand() % 256;
		}

		mSubmitTex = true;
	}
}

void TextureScene::render()
{
	mRendererRef.beginDraw();

	// Bind the texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTexId);

	if (mSubmitTex)
	{
		mSubmitTex = false;
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	}

	glUseProgram(mShaderProgram);

 	glBindBuffer(GL_ARRAY_BUFFER, mBaseVtxBuffer);
 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBaseVboIndicesBuffer);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

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

	for (int i=0; i < width * height *3 ; ++i)
	{
		pixels[i] = rand() % 256;
	}

	// Use tightly packed data
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Generate a texture object
	glGenTextures(1, &textureId);

	// Bind the texture object
	glBindTexture(GL_TEXTURE_2D, textureId);

	// Load the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);


	// Set the filtering mode
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	return textureId;
}
