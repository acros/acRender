#include "SimpleTriangle.h"
#include "utils.h"
#include "Base/AcUtils.h"
#include "File/AcFileManager.h"

const int VERTEX_POS_INDX = 0;
const int VERTEX_COLOR_INDX = 1;

//Set the vertex we need to draw
const int VERTEX_POS_SIZE = 3;
const int VERTEX_COLOR_SIZE = 4;

GLfloat vertices[3 * (VERTEX_POS_SIZE + VERTEX_COLOR_SIZE)] =
{
	0.0f,  0.5f, 0.0f,        // v0
	1.0f,  0.0f, 0.0f, 1.0f,  // c0

	-0.5f, -0.5f, 0.0f,       // v1
	0.0f,  1.0f, 0.0f, 1.0f,  // c1

	0.5f, -0.5f, 0.0f,        // v2
	0.0f,  0.0f, 1.0f, 1.0f,  // c2
};

GLushort indices[3] = { 0, 1, 2 };

SimpleTriangle::SimpleTriangle(Renderer& renderer)
	: Scene(renderer)
#if !USE_OGL_3_LATEST
	, mVaoId(0)
#endif
{
	Acros::FileManager::loadShaderFile("simple_color_2d.vert", mVertStr);
	Acros::FileManager::loadShaderFile("simple_color_2d.frag", mFragStr);
}

SimpleTriangle::~SimpleTriangle()
{

}

void SimpleTriangle::enter()
{
	Scene::enter();

	//VBO rely on VAO
	glGenVertexArrays(1, &mBaseVAO);
	glBindVertexArray(mBaseVAO);

	//Init VBO (Vertex Buffer Object)
	glEnableVertexAttribArray(VERTEX_POS_INDX);//For Vertex
	glGenBuffers(1, &mBaseVboIndicesBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mBaseVboIndicesBuffer);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat) * (VERTEX_COLOR_SIZE + VERTEX_POS_SIZE), vertices,GL_STATIC_DRAW);
	glVertexAttribPointer(VERTEX_POS_INDX, VERTEX_POS_SIZE, GL_FLOAT, GL_FALSE,sizeof(GLfloat) * (VERTEX_POS_SIZE + VERTEX_COLOR_SIZE), 0);

	ACROS_GL_CHECK_ERROR("VBO bind vertex");

	GLint offset = sizeof(GLfloat) * VERTEX_POS_SIZE;
	glVertexAttribPointer(VERTEX_COLOR_INDX, VERTEX_COLOR_SIZE, GL_FLOAT, GL_FALSE,
		sizeof(GLfloat) * (VERTEX_POS_SIZE + VERTEX_COLOR_SIZE), (const void*)offset);

	glGenBuffers(1, &mBaseVboIndicesBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBaseVboIndicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLushort) ,indices,GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void SimpleTriangle::render()
{
	mRendererRef.beginDraw();

	drawWithVBO();

	mRendererRef.endDraw();
}


void SimpleTriangle::drawWithVBO()
{
	glUseProgram(mShaderProgram);

	float offsetLoc = glGetUniformLocation(mShaderProgram, "u_offset");
	glUniform1f(offsetLoc, 0.5f);

	glBindVertexArray(mBaseVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mBaseVtxBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBaseVboIndicesBuffer);

	glEnableVertexAttribArray(VERTEX_POS_INDX);
	glEnableVertexAttribArray(VERTEX_COLOR_INDX);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);

	//Close attribute
	glDisableVertexAttribArray(VERTEX_POS_INDX);
	glDisableVertexAttribArray(VERTEX_COLOR_INDX);

	//Reset VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void SimpleTriangle::exit()
{
	Scene::exit();
}

