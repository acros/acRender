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

		GLuint		mVao;
		GLuint		mVbo[2];

		GLuint		mColorBuf;
		GLuint		mNormBuf;

		GLuint		mBufferStride;
		GLuint		indexSize;

		GLfloat*	normals;
		GLfloat*	vertices;
		GLfloat*	colors;
		GLuint*		indices;

		MeshPropertyDataSource	mPropertySource[4];

		class Material*	mMaterial;
	};

}
