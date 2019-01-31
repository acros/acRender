#include "Mesh.h"
#include "Material.h"
#include "Base/AcUtils.h"
#include "Camera/Camera.h"

const int POSTITION_LOC = 0;
const int COLOR_LOC = 1;
const int NORMAL_LOC = 2;
const int UV_COORD_LOC = 3;

const int POS_SIZE = 3;
const int COLOR_APLHPA_SIZE = 4;
const int COLOR_SIZE = 3;
const int NORMAL_SIZE = 3;

namespace Acros
{
	Mesh::Mesh() 
		: vertices(nullptr)
		, indices(nullptr)
		, normals(nullptr)
		, colors(nullptr)
		, mBufferStride(0)
		, indexSize(0)
		, mMaterial(nullptr)
		, mVao(0)
		, mNormBuf(0)
		, mColorBuf(0)
		, mMeshType(MeshType::MultiBuffer)
	{
		mVbo[0] = 0;
		mVbo[1] = 0;

		for (int i = 0 ; i < 4; ++i)
		{
			mPropertySource[i] = MeshPropertyDataSource::None;
		}
	}

	Mesh::~Mesh()
	{
		glDeleteVertexArrays(1, &mVao);
		glDeleteBuffers(2, mVbo);
		glDeleteBuffers(1, &mNormBuf);
		glDeleteBuffers(1, &mColorBuf);

		SAFE_FREE(vertices);
		SAFE_FREE(indices);
		SAFE_FREE(normals);
		SAFE_FREE(colors);

		SAFE_DELETE(mMaterial);
	}

	void Mesh::createTriagle(ShaderType shader)
	{
		mShape = ST_ColorTriangle;
		mMeshType = SingleBuffer;
		indexSize = esGenMitureBufferTriangle(&vertices, &colors, &indices);
		mBufferStride = 7;
		if (shader == Invalid)
			shader = VertexColor;
		mMaterial = new Material(shader);
	}

	void Mesh::createCube(ShaderType shader)
	{
		mShape = ST_Cube;

		//Load the index and init buffer, use VBO here
		indexSize = esGenCube(1.0f, &vertices, &normals, NULL, &indices);
		mBufferStride = 24;
		if (shader == Invalid)
		{
			shader = LightLambert;
			mPropertySource[COLOR_LOC] = MeshPropertyDataSource::Constant;
		}

		mMaterial = new Material(shader);
		mMaterial->setDiffuse(AcColor4(0.8f, 0.6f, 0.0f, 1.0f));
	}

	void Mesh::createPlane(ShaderType shader)
	{
		mShape = ST_Plane;

		int edgeTrigleNums = 3;
		indexSize = esGenSquareGrid(edgeTrigleNums, &vertices, &indices);
		mBufferStride = edgeTrigleNums * edgeTrigleNums;

		if (shader == Invalid)
		{
			shader = VertexColor;
			mPropertySource[COLOR_LOC] = MeshPropertyDataSource::Constant;
		}

		mMaterial = new Material(shader);
		mMaterial->setDiffuse(AcColor4(0.7f, 0.7f, 0.7f, 1.0f));
	}

	void Mesh::createSphere(ShaderType shader)
	{
		mShape = ST_Sphere;

		int numSlices = 40;
		indexSize = esGenSphere(numSlices,1.0f, &vertices, &normals,&colors, NULL, &indices);
		mBufferStride = (numSlices / 2 + 1) * (numSlices + 1);
		if (shader == Invalid)
		{
			shader = LightLambert;
		}

		mMaterial = new Material(shader);
		mMaterial->setDiffuse(AcColor4(0.7f, 0.7f, 0.7f, 1.0f));
	}

	void Mesh::initDraw(Renderer& context)
	{
		mMaterial->initShader(context);

		glGenVertexArrays(1, &mVao);
		glBindVertexArray(mVao);

		glGenBuffers(2, mVbo);
		glBindBuffer(GL_ARRAY_BUFFER, mVbo[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVbo[1]);

		if (mMeshType == SingleBuffer)
		{
			prepareBufferData();
		}
		else
		{
			prepareMultiBufferData();
		}

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize * sizeof(GLuint), indices, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}


	void Mesh::prepareBufferData()
	{
		//Mixture Vertex Array - One VertexBuff - 
		//顶点数据来自同一缓冲,只需要使用一个GL_ARRAY_BUFFER,并在属性中指定偏移量
		glBufferData(GL_ARRAY_BUFFER, POS_SIZE * sizeof(GLfloat) * mBufferStride, vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(POSTITION_LOC);
		glVertexAttribPointer(POSTITION_LOC, POS_SIZE, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * mBufferStride, 0);
		mPropertySource[POSTITION_LOC] = MeshPropertyDataSource::Buffer;

		glEnableVertexAttribArray(COLOR_LOC);
		GLint offset = sizeof(GLfloat) * POS_SIZE;
		glVertexAttribPointer(COLOR_LOC, COLOR_APLHPA_SIZE, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * mBufferStride, (const void*)offset);
		mPropertySource[COLOR_LOC] = MeshPropertyDataSource::Buffer;
	}

	void Mesh::prepareMultiBufferData()
	{
		//Data from different buffs
			//An element array with multiple vertex buffers
			//顶点数据来个多个缓冲，需要为每个缓冲设定一个GL_ARRAY_BUFFER
		if (vertices != nullptr) {
			glBufferData(GL_ARRAY_BUFFER, mBufferStride * POS_SIZE * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(POSTITION_LOC);
			glVertexAttribPointer(POSTITION_LOC, POS_SIZE, GL_FLOAT, GL_FALSE, POS_SIZE * sizeof(GLfloat), NULL);
			mPropertySource[POSTITION_LOC] = MeshPropertyDataSource::Buffer;
		}

		if (colors != nullptr) {
			glGenBuffers(1, &mColorBuf);
			glBindBuffer(GL_ARRAY_BUFFER, mColorBuf);
			glBufferData(GL_ARRAY_BUFFER, mBufferStride * COLOR_SIZE * sizeof(GLfloat), colors, GL_STATIC_DRAW);
			glEnableVertexAttribArray(COLOR_LOC);
			glVertexAttribPointer(COLOR_LOC, COLOR_SIZE, GL_FLOAT, GL_FALSE, COLOR_SIZE * sizeof(GLfloat), NULL);
			mPropertySource[COLOR_LOC] = MeshPropertyDataSource::Buffer;
		}

		if (normals != nullptr) {
			glGenBuffers(1, &mNormBuf);
			glBindBuffer(GL_ARRAY_BUFFER, mNormBuf);
			glBufferData(GL_ARRAY_BUFFER, mBufferStride * NORMAL_SIZE * sizeof(GLfloat), normals, GL_STATIC_DRAW);
			glEnableVertexAttribArray(NORMAL_LOC);
			glVertexAttribPointer(NORMAL_LOC, NORMAL_SIZE, GL_FLOAT, GL_FALSE, NORMAL_SIZE * sizeof(GLfloat), NULL);
			mPropertySource[NORMAL_LOC] = MeshPropertyDataSource::Buffer;
		}
	}

	void Mesh::draw(AcTransform& selfTransform, Renderer& context, Camera * cam, const Light * light)
	{
		const AcMatrix& m = selfTransform.getModelMat();
		const AcMatrix mvp = cam->getProjMat() * cam->getViewMat() * m;

		glUseProgram(mMaterial->mShaderProgram);

 		int shaderFlag = mMaterial->GetFlag();
		if (light != nullptr)
		{
			if (shaderFlag & ShaderFlag::ReceiveLight){
				const AcVector& lDir = light->getDir();
				glUniform4fv(mMaterial->mLightDir, 1, glm::value_ptr(lDir));
				const AcColor3& lColor = light->getColor();
				glUniform4fv(mMaterial->mLightColor, 1, glm::value_ptr(lColor));
			}
		}

		glBindVertexArray(mVao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVbo[1]);
		if (shaderFlag & WorldSpace)
		{
			const float* mats = glm::value_ptr(mvp);
			glUniformMatrix4fv(mMaterial->mMvpLoc, 1, GL_FALSE, mats);
		}

		if (/*(shaderFlag & ShaderFlag::Color) &&*/ mPropertySource[COLOR_LOC] == MeshPropertyDataSource::Constant)
		{
			//No color buff, use material value
			const AcVector4& c = mMaterial->getDiffuse();
			glVertexAttrib4f(COLOR_LOC, c.r, c.g, c.b, c.a);
		}

		glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}
