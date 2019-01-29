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

	void draw(Renderer& context,const AcMatrix& mat);

protected:
	ShapeType	mShape;

	GLuint		mVao;
	GLuint		mVbo[2];

	GLuint		vertexSize;
	GLuint		indexSize;

	GLfloat*	normals;
	GLfloat*	vertices;
	GLuint*		indices;

	class Material*	mMaterial;
};