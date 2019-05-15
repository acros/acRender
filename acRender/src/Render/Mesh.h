#pragma once

#include "Renderer.h"
#include "Math/AcMath.h"
#include "Render/AcLight.h"

namespace Acros
{
	class Mesh
	{
		enum MeshType
		{
			Unknown,
			SingleBuffer,
			MultiBuffer,
		};

		enum MeshPropertyDataSource
		{
			None,
			Buffer,
			Constant
		};

	public:

		Mesh();
		~Mesh();

		void loadData(ShaderType shader, GLfloat* v, GLint vStride, GLuint* i, int iSize, GLfloat* n, GLfloat* crd);

		void createTriagle(ShaderType shader);
		void createCube(ShaderType shader);
		void createPlane(ShaderType shader);
		void createSphere(ShaderType shader);

		void initDraw(Renderer& context);

		void draw(AcTransform& selfTransform, Renderer& context, class Camera* cam, const Light* l = nullptr);

	protected:
		void prepareBufferData();

		void prepareMultiBufferData();

	protected:
		MeshType	mMeshType;
		ShapeType	mShape;


		//TODO: Wrapping in RenderState
		GLuint		mVao;
		GLuint		mVbo[2];
		GLuint		mColorBuf;
		GLuint		mNormBuf;

		GLuint		mBufferStride;
		GLuint		indexSize;

		GLfloat*	vertices;
		GLfloat*	normals;
		GLfloat*	colors;
		GLuint*		indices;
		GLfloat*	coords;

		MeshPropertyDataSource	mPropertySource[4];

		class Material*	mMaterial;
	};

}
