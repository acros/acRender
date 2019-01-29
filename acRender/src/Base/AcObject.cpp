#include "AcObject.h"
#include "Render/Mesh.h"

AcObject::AcObject()
	: mMesh(nullptr) 
{

}

AcObject::~AcObject()
{
	if (mMesh != nullptr)
		delete mMesh;
}

void AcObject::rotate(const AcVector& rotAxis, float angle)
{
	mTransform.setRotation(glm::angleAxis(angle,rotAxis));
}

void AcObject::initDraw(Renderer& context)
{
	if (mMesh != nullptr)
	{
		mMesh->initDraw(context);
	}
}

void AcObject::draw(Renderer& context, const AcMatrix& viewMat,const AcMatrix& proj)
{
	if (mMesh != nullptr)
	{
		const AcMatrix& m = mTransform.getModelMat();
		mMesh->draw(context, proj * viewMat * m);
	}
}

void AcObject::createShape(ShapeType	shape)
{
	if (mMesh != nullptr)
		delete mMesh;

	mMesh = new Mesh();

	switch (shape)
	{
	case ST_Cube:
		mMesh->createCube();
		break;
	case ST_Plane:
		mMesh->createPlane();
		break;
	case ST_ColorTriangle:
		mMesh->createTriagle();
		break;
	case ST_Sphere:
		mMesh->createSphere();
		break;
	default:
		assert(false);
		break;
	}

}

#if ACROS_USE_IMGUI
void AcObject::drawImgui()
{

}
#endif
