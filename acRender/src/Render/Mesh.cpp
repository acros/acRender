#include "Mesh.h"
#include "Material.h"
#include "Base/AcUtils.h"

const int POSTITION_LOC = 0;
const int COLOR_LOC = 1;

GLfloat vtx[3 * 7] =
{
	0.0f,  0.5f, 0.0f,        // v0
	1.0f,  0.0f, 0.0f, 1.0f,  // c0
	-0.5f, -0.5f, 0.0f,       // v1
	0.0f,  1.0f, 0.0f, 1.0f,  // c1
	0.5f, -0.5f, 0.0f,        // v2
	0.0f,  0.0f, 1.0f, 1.0f,  // c2
};
GLuint idx[3] = { 0, 1, 2 };

Mesh::Mesh() 
	: vertices(nullptr)
	, indices(nullptr)
	, vertexSize(0)
	, indexSize(0)
	, mMaterial(nullptr)
	, mVao(0)
{
	mVbo[0] = 0;
	mVbo[1] = 0;
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &mVao);
	glDeleteBuffers(2, mVbo);

	if (mShape == ST_ColorTriangle)
	{

	}
	else
	{
		if (vertices)
			free(vertices);

		if (indices)
			free(indices);
	}

	SAFE_DELETE(mMaterial);
}

void Mesh::createTriagle()
{
	mShape = ST_ColorTriangle;

	vertices = vtx;
	indices = idx;
	indexSize = 3;
	vertexSize = 7;

	mMaterial = new Material();
}

void Mesh::createCube()
{
	mShape = ST_Cube;

	//Load the index and init buffer, use VBO here
	indexSize = esGenCube(1.0f, &vertices, NULL, NULL, &indices);

	//Hack: Cube has 24 vertex
	vertexSize = 24;

	mMaterial = new Material();
}

void Mesh::createPlane()
{
	mShape = ST_Plane;

	int edgeTrigleNums = 3;
	indexSize = esGenSquareGrid(edgeTrigleNums, &vertices, &indices);
	vertexSize = edgeTrigleNums * edgeTrigleNums;

	mMaterial = new Material();
}

void Mesh::initDraw(Renderer& context,const string& vertStr,const string& fragStr)
{
// 	if (mShape == ST_ColorTriangle)
// 		mMaterial->loadSimpleShader(context);
// 	else
		mMaterial->loadShader(context,vertStr, fragStr);

	//VBO rely on VAO
	glGenVertexArrays(1, &mVao);
	glBindVertexArray(mVao);

	glGenBuffers(2, mVbo);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVbo[1]);

	if (mShape == ST_ColorTriangle)
	{
		ACROS_GL_CHECK_ERROR("VBO init");

		//Init VBO (Vertex Buffer Object)
		glEnableVertexAttribArray(0);//For Vertex
		glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat) * vertexSize, vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(POSTITION_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * (3 + 4), 0);

		ACROS_GL_CHECK_ERROR("VBO bind vertex");

		GLint offset = sizeof(GLfloat) * 3;
		glVertexAttribPointer(COLOR_LOC, 4, GL_FLOAT, GL_FALSE,sizeof(GLfloat) * (3 + 4), (const void*)offset);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLuint), indices, GL_STATIC_DRAW);

		glBindVertexArray(0);
	}
	else
	{
		glBufferData(GL_ARRAY_BUFFER, vertexSize * 3 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize * sizeof(GLuint), indices, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

void Mesh::draw(Renderer& context,const AcMatrix& mvp)
{
	glUseProgram(mMaterial->mShaderProgram);

	if (mShape == ST_ColorTriangle)
	{
		glBindVertexArray(mVao);
		glBindBuffer(GL_ARRAY_BUFFER, mVbo[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVbo[1]);

		ACROS_GL_CHECK_ERROR("VBO bind");

		glEnableVertexAttribArray(POSTITION_LOC);
		glEnableVertexAttribArray(COLOR_LOC);

//		const float* mats = glm::value_ptr(glm::identity<glm::mat4>());
		const float* mats = glm::value_ptr(mvp);
		glUniformMatrix4fv(mMaterial->mMvpLoc, 1, GL_FALSE, mats);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		ACROS_GL_CHECK_ERROR("VBO draw");

		//Close attribute
		glDisableVertexAttribArray(POSTITION_LOC);
		glDisableVertexAttribArray(COLOR_LOC);

		//Reset VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}
	else
	{
		//Render a cube
		glBindBuffer(GL_ARRAY_BUFFER, mVbo[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVbo[1]);

		glEnableVertexAttribArray(POSTITION_LOC);	// Pos
		glVertexAttribPointer(POSTITION_LOC, 3, GL_FLOAT, GL_FALSE, (3 /*+ 2*/) * sizeof(GLfloat), (const void*)NULL);	//Pure position vertex array

		if (mShape == ST_Cube)
			glVertexAttrib4f(COLOR_LOC, 0.8f, 0.6f, 0.0f, 1.0f);		//Set the color to a Const value
		else if (mShape == ST_Plane)
			glVertexAttrib4f(COLOR_LOC, 0.7f, 0.7f, 0.7f, 1.0f);

		glUniformMatrix4fv(mMaterial->mMvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

		glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(POSTITION_LOC);	// Pos
		glDisableVertexAttribArray(COLOR_LOC);	// Color

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}
