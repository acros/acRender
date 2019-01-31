#include "TriangleScene.h"
#include "Base/AcUtils.h"
#include "File/AcFileManager.h"

TriangleScene::TriangleScene()
	: Scene()
{
	Acros::FileManager::loadShaderFile("simple_color_2d.vert", mVertStr);
	Acros::FileManager::loadShaderFile("simple_color_2d.frag", mFragStr);
}

TriangleScene::~TriangleScene()
{

}

void TriangleScene::enter()
{
	Scene::enter();

	GLfloat vVertices[] = {
		0.0f,  1.f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f };


	GLfloat vColors[] = {
		1.0f, 0.0f,0.0f,
		0.0f, 1.0f,0.0f,
		0.0f, 0.0f,1.0f,
	};

	glGenVertexArrays(1, &mBaseVAO);
	glBindVertexArray(mBaseVAO);

	glEnableVertexAttribArray(0);
	glGenBuffers(1, &mBaseVtxBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mBaseVtxBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vVertices), vVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);

	glEnableVertexAttribArray(1);
	glGenBuffers(1, &mColorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mColorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vColors), vColors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),NULL);

	GLushort vertex_indices[] = {
		0, 1, 2,
	};

	glGenBuffers(1, &mBaseVboIndicesBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBaseVboIndicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indices), vertex_indices, GL_STATIC_DRAW);

}

void TriangleScene::render(Renderer & r)
{
	r.beginDraw();

	glUseProgram(mShaderProgram);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBaseVboIndicesBuffer);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	r.endDraw();
}

void TriangleScene::exit()
{
	Scene::exit();

	glDeleteBuffers(1, &mColorBuffer);
}
