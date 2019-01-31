#include "Mesh.h"
#include "Material.h"
#include "Base/AcUtils.h"
#include "Camera/Camera.h"

const int POSTITION_LOC = 0;
const int COLOR_LOC = 1;
const int NORMAL_LOC = 2;

namespace Acros
{
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

		mMaterial = new Material(VertexColor);
	}

	void Mesh::createCube()
	{
		mShape = ST_Cube;

		//Load the index and init buffer, use VBO here
		indexSize = esGenCube(1.0f, &vertices, NULL, NULL, &indices);

		//Hack: Cube has 24 vertex
		vertexSize = 24;

		mMaterial = new Material(VertexColor);
		mMaterial->setDiffuse(AcColor4(0.8f, 0.6f, 0.0f, 1.0f));
	}

	void Mesh::createPlane()
	{
		mShape = ST_Plane;

		int edgeTrigleNums = 3;
		indexSize = esGenSquareGrid(edgeTrigleNums, &vertices, &indices);
		vertexSize = edgeTrigleNums * edgeTrigleNums;

		mMaterial = new Material(VertexColor);
	}

	void Mesh::createSphere()
	{
		mShape = ST_Sphere;

		int numSlices = 40;
		indexSize = esGenSphere(numSlices,1.0f, &vertices, &normals,&colors, NULL, &indices);
		int numParallels = numSlices / 2;
		vertexSize = (numParallels + 1) * (numSlices + 1);

		normSize = vertexSize;

		mMaterial = new Material(LightLambert);
		mMaterial->setDiffuse(AcColor4(0.7f, 0.7f, 0.7f, 1.0f));
	}

	void Mesh::initDraw(Renderer& context)
	{
		mMaterial->initShader(context);

		//VBO rely on VAO
		glGenVertexArrays(1, &mVao);
		glBindVertexArray(mVao);

		glGenBuffers(2, mVbo);
		glBindBuffer(GL_ARRAY_BUFFER, mVbo[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVbo[1]);

		if (mShape == ST_ColorTriangle)
		{
			//All vertex data from one buffer
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

			//Mixture Vertex Array - One VertexBuff
			glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat) * vertexSize, vertices, GL_STATIC_DRAW);
		
			glEnableVertexAttribArray(POSTITION_LOC);
			glVertexAttribPointer(POSTITION_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * (3 + 4), 0);
			GLint offset = sizeof(GLfloat) * 3;
			glEnableVertexAttribArray(COLOR_LOC);
			glVertexAttribPointer(COLOR_LOC, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * (3 + 4), (const void*)offset);

			glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLuint), indices, GL_STATIC_DRAW);
		}
		else if (mShape == ST_Sphere)
		{
			//Data from different buffs
			//An element array with multiple vertex buffers
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

			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize * sizeof(GLuint), indices, GL_STATIC_DRAW);
		}
		else
		{
			//Vertex buffers & Constants
			glBufferData(GL_ARRAY_BUFFER, vertexSize * 3 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize * sizeof(GLuint), indices, GL_STATIC_DRAW);
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Mesh::draw(AcTransform& selfTransform, Renderer& context, Camera * cam, const Light * light)
	{
		const AcMatrix& m = selfTransform.getModelMat();
		const AcMatrix& mv = cam->getViewMat() * m;
		const AcMatrix mvp = cam->getProjMat() * cam->getViewMat() * m;

		glUseProgram(mMaterial->mShaderProgram);

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

		glBindVertexArray(mVao);
		if (mShape == ST_ColorTriangle || mShape == ST_Sphere)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVbo[1]);
			if (!(shaderFlag & ScreenSpace))
			{
				const float* mats = glm::value_ptr(mvp);
				glUniformMatrix4fv(mMaterial->mMvpLoc, 1, GL_FALSE, mats);
			}
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
				glVertexAttrib4f(COLOR_LOC, 0.8f, 0.6f, 0.0f, 1.0f);		
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
		glBindVertexArray(0);

	}
}
