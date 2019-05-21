#include "AcObject.h"
#include "Render/Mesh.h"
#include "Render/AcLight.h"
#include "Camera/Camera.h"
#include "File/AcFileManager.h"

namespace Acros
{
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

	void AcObject::draw(Renderer& context, Camera* cam, Light* l)
	{
		if (mMesh != nullptr)
		{
			mMesh->draw(mTransform,context,cam,l);
		}
	}

	void AcObject::createShape(ShapeType shape)
	{
		createShape(shape, ShaderType::Invalid);
	}

	void AcObject::createShape(ShapeType shape, ShaderType shader)
	{
		if (mMesh != nullptr)
			delete mMesh;

		mMesh = new Mesh();

		switch (shape)
		{
		case ST_Cube:
			mMesh->createCube(shader);
			break;
		case ST_Plane:
			mMesh->createPlane(shader);
			break;
		case ST_ColorTriangle:
			mMesh->createTriagle(shader);
			break;
		case ST_Sphere:
			mMesh->createSphere(shader);
			break;
		default:
			assert(false);
			break;
		}

	}

	void AcObject::loadMesh(const string & fileName, ShaderType shader)
	{
		if (mMesh != nullptr)
			SAFE_DELETE(mMesh);

		mMesh = Acros::FileManager::LoadModelPlyFile(fileName);
	}

#if ACROS_USE_IMGUI
	void AcObject::drawImgui()
	{

	}
	#endif
}
