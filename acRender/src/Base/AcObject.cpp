#include "AcObject.h"
#include "Render/Mesh.h"

AcObject::AcObject()
	: mMesh(nullptr) 
{
 	mTransform.rot = glm::identity<glm::quat>();
 	mTransform.scale = AcVector(1,1,1);
	mTransform.translation = AcVector(0);
}


AcObject::~AcObject()
{
	if (mMesh != nullptr)
		delete mMesh;
}

const AcMatrix& AcObject::getModelMat()
{
	mModelMat = glm::identity<glm::mat4>();
	
	mModelMat = glm::translate(mModelMat, mTransform.translation);
	glm::mat4 RotationMatrix = glm::mat4_cast(mTransform.rot);
	mModelMat *= RotationMatrix;
	mModelMat = glm::scale(mModelMat, mTransform.scale);

	return mModelMat;
}

void AcObject::rotate(const AcVector& rotAxis, float angle)
{
	mTransform.rot = glm::angleAxis(angle,rotAxis);
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
		AcMatrix modelview;
		AcMatrix mvpMatrix;

		AcMathUtils::printLog(viewMat, "Camera View Mat");
		AcMathUtils::printLog(proj, "Camera Project Mat");

		// Compute MVP for scene rendering by multiplying the modelview and perspective matrices together
		const AcMatrix& m = getModelMat();
		AcMathUtils::printLog(m, "Triangle Model Mat");

		modelview =  m * viewMat;
		mvpMatrix = proj * viewMat * m;

		AcMathUtils::printLog(mvpMatrix, "MVP");

		mMesh->draw(context, mvpMatrix);
	}
}

void AcObject::createShape(ShapeType	shape)
{
	if (mMesh != nullptr)
		delete mMesh;

	mMesh = new Mesh();

	if (shape == ST_Cube)
	{
		mMesh->createCube();
	}
	else if (shape == ST_Plane)
	{
		mMesh->createPlane();
	}
	else if (shape == ST_ColorTriangle)
	{
		mMesh->createTriagle();
	}
	else
	{
		assert(false);
	}

}

#if ACROS_USE_IMGUI
void AcObject::drawImgui()
{

}
#endif
