#include "AcObject.h"
#include "Render/Mesh.h"

AcObject::~AcObject()
{
	if (mMesh != nullptr)
		delete mMesh;
}

const AcMatrix& AcObject::getModelMat()
{
// 	esMatrixLoadIdentity(&mModelMat);
// 	esTranslate(&mModelMat, mPos.x, mPos.y, mPos.z);
// 	esScale(&mModelMat, mScale.x, mScale.y, mScale.z);
//	esRotate(&mModelMat, mAngleY, mRot.x, mRot.y, mRot.z);

	glm::mat4 newMat = glm::mat4(1.0);
	mModelMat = newMat;
	mModelMat = glm::translate(mModelMat, mPos);
	mModelMat = glm::scale(mModelMat,mScale);
	mModelMat = glm::rotate(mModelMat,mAngleY, mRot);

	return mModelMat;
}

void AcObject::rotate(const AcVector& rotAxis, float angle)
{
	mRot = rotAxis;
	mAngleY = angle;
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

		// Compute MVP for scene rendering by multiplying the modelview and perspective matrices together
		modelview = getModelMat() * viewMat;
		mvpMatrix = modelview * proj;

// 		esMatrixMultiply(&modelview, &getModelMat(), &viewMat);
// 		esMatrixMultiply(&mvpMatrix, &modelview, &proj);

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

}
