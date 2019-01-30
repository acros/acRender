#pragma once

//#include "AcObject.h"
#include "Renderer.h"
#include "Math/AcMath.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	void createTriagle();
	void createCube();
	void createPlane();
	void createSphere();

	void initDraw(Renderer& context);

	void draw(Renderer& context,const AcMatrix& mvp,const class Light* l = nullptr);

protected:
	ShapeType	mShape;

	GLuint		mVao;
	GLuint		mVbo[2];

	GLuint		mColorBuf;
	GLuint		mNormBuf;

	GLuint		normSize;
	GLuint		vertexSize;
	GLuint		indexSize;

	GLfloat*	normals;
	GLfloat*	vertices;
	GLfloat*	colors;
	GLuint*		indices;

	class Material*	mMaterial;
};