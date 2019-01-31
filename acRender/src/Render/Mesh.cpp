#include "Mesh.h"
#include "Material.h"
#include "Base/AcUtils.h"
#include "Camera/Camera.h"

const int POSTITION_LOC = 0;
const int COLOR_LOC = 1;
const int NORMAL_LOC = 2;

Mesh::Mesh() 
	: vertices(nullptr)
	, indices(nullptr)
	, normals(nullptr)
	, colors(nullptr)
	, vertexSize(0)
	, indexSize(0)
	, mMaterial(nullptr)
	, mVao(0)
	, mNormBuf(0)
	, mColorBuf(0)
{
	mVbo[0] = 0;
	mVbo[1] = 0;
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &mVao);
	glDeleteBuffers(2, mVbo);
	glDeleteBuffers(1, &mNormBuf);
	glDeleteBuffers(1, &mColorBuf);

	if (mShape == ST_ColorTriangle)
	{

	}
	else
	{
		SAFE_FREE(vertices);
		SAFE_FREE(indices);
		SAFE_FREE(normals);
		SAFE_FREE(colors);
	}

	SAFE_DELETE(mMaterial);
}

void Mesh::createTriagle()
{
	mShape = ST_ColorTriangle;

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

void Mesh::createSphere()
{
	mShape = ST_Sphere;

	int numSlices = 40;
	indexSize = esGenSphere(numSlices,1.0f, &vertices, &normals,&colors, NULL, &indices);
	int numParallels = numSlices / 2;
	vertexSize = (numParallels + 1) * (numSlices + 1);

	normSize = vertexSize;

	mMaterial = new Material();
}

void Mesh::initDraw(Renderer& context)
{
	ShaderType sType = (mShape == ST_Sphere) ? LightLambert : VertexColor;
	mMaterial->initShader(context, sType);

	//VBO rely on VAO
	glGenVertexArrays(1, &mVao);
	glBindVertexArray(mVao);

	glGenBuffers(2, mVbo);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVbo[1]);

	if (mShape == ST_ColorTriangle)
	{
		GLfloat vtx[3 * 7] =	{
			0.0f,  0.5f, 0.0f,        // v0
			1.0f,  0.0f, 0.0f, 1.0f,  // c0
			-0.5f, -0.5f, 0.0f,       // v1
			0.0f,  1.0f, 0.0f, 1.0f,  // c1
			0.5f, -0.5f, 0.0f,        // v2
			0.0f,  0.0f, 1.0f, 1.0f,  // c2
		};
		GLuint idx[3] = { 0, 1, 2 }; //Must Remain a copy in memory

		vertices = vtx;
		indices = idx;
		indexSize = 3;
		vertexSize = 7;

		//Mix Pos&Color Vertex - One VertexBuff
		glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat) * vertexSize, vertices, GL_STATIC_DRAW);
		
		glVertexAttribPointer(POSTITION_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * (3 + 4), 0);
		GLint offset = sizeof(GLfloat) * 3;
		glVertexAttribPointer(COLOR_LOC, 4, GL_FLOAT, GL_FALSE,sizeof(GLfloat) * (3 + 4), (const void*)offset);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLuint), indices, GL_STATIC_DRAW);
	}
	else if (mShape == ST_Sphere)
	{
		//A element array with multiple vertex buffers
		glBindBuffer(GL_ARRAY_BUFFER, mVbo[0]);
		glBufferData(GL_ARRAY_BUFFER, vertexSize * 3 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(POSTITION_LOC);
		glVertexAttribPointer(POSTITION_LOC, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);

		glGenBuffers(1, &mColorBuf);
		glBindBuffer(GL_ARRAY_BUFFER, mColorBuf);
		glBufferData(GL_ARRAY_BUFFER, normSize * 3 * sizeof(GLfloat), colors, GL_STATIC_DRAW);
		glEnableVertexAttribArray(COLOR_LOC);
		glVertexAttribPointer(COLOR_LOC, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);

		glGenBuffers(1, &mNormBuf);
		glBindBuffer(GL_ARRAY_BUFFER, mNormBuf);
		glBufferData(GL_ARRAY_BUFFER, normSize * 3 * sizeof(GLfloat), normals, GL_STATIC_DRAW);
		glEnableVertexAttribArray(NORMAL_LOC);
		glVertexAttribPointer(NORMAL_LOC, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVbo[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize * sizeof(GLuint), indices, GL_STATIC_DRAW);
	}
	else
	{
		glBufferData(GL_ARRAY_BUFFER, vertexSize * 3 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize * sizeof(GLuint), indices, GL_STATIC_DRAW);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::draw(AcTransform& selfTransform, Renderer& context, Camera * cam, const Acros::Light * light)
{
	const AcMatrix& m = selfTransform.getModelMat();
	const AcMatrix& mv = cam->getViewMat() * m;
	const AcMatrix mvp = cam->getProjMat() * cam->getViewMat() * m;

	glUseProgram(mMaterial->mShaderProgram);
	glBindVertexArray(mVao);

	int shaderFlag = mMaterial->GetFlag();
	if (shaderFlag & ShaderFlag::MV)
	{
		glUniform4fv(mMaterial->mMvLoc, 1, glm::value_ptr(mv));
	}

	if (shaderFlag & ShaderFlag::WorldMatrix)
	{
		glUniform4fv(mMaterial->mWorldMatrixLoc, 1, glm::value_ptr(m));
	}

	if (light != nullptr)
	{
		if (shaderFlag & ShaderFlag::LightDir){
			const AcVector& lDir = light->getDir();
			glUniform4fv(mMaterial->mLightDir, 1, glm::value_ptr(lDir));
		}

		if (shaderFlag & ShaderFlag::LightColor){
			const AcColor3& lColor = light->getColor();
			glUniform4fv(mMaterial->mLightColor, 1, glm::value_ptr(lColor));
		}
	}

	if (mShape == ST_ColorTriangle)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVbo[1]);

		glEnableVertexAttribArray(POSTITION_LOC);
		glEnableVertexAttribArray(COLOR_LOC);

		const float* mats = glm::value_ptr(mvp);
		glUniformMatrix4fv(mMaterial->mMvpLoc, 1, GL_FALSE, mats);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(POSTITION_LOC);
		glDisableVertexAttribArray(COLOR_LOC);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	else if (mShape == ST_Sphere)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVbo[1]);

		glUniformMatrix4fv(mMaterial->mMvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

		glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, mVbo[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVbo[1]);

		glEnableVertexAttribArray(POSTITION_LOC);	
		glVertexAttribPointer(POSTITION_LOC, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (const void*)NULL);	//Pure position vertex array

		if (mShape == ST_Cube)
			glVertexAttrib4f(COLOR_LOC, 0.8f, 0.6f, 0.0f, 1.0f);		//Set the color to a Const value
		else if (mShape == ST_Plane)
			glVertexAttrib4f(COLOR_LOC, 0.7f, 0.7f, 0.7f, 1.0f);
		else
			assert(false);

		glUniformMatrix4fv(mMaterial->mMvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
		glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(POSTITION_LOC);	
		glDisableVertexAttribArray(COLOR_LOC);	

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}
