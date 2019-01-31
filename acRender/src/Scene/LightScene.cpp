#include "LightScene.h"
#include "Base/AcObject.h"

namespace Acros
{

	LightScene::LightScene()
		: Scene()
		, mCam(nullptr)
		, mCameraMoveTime(0.f)
	{}

	LightScene::~LightScene()
	{

	}

	void LightScene::enter()
	{
		Scene::enter();

		//Set camera 
		mCam = new Camera(1280 / 720.f, 60.f, 1.f, 1000.f);
		AcVector eyePos(-10.f, 3.f, 10.f);
		mCam->setViewMat(eyePos, AcVector(0, 0, -3), AcVector(0, 1, 0));
		const AcMatrix& vieMat = mCam->getViewMat();

		AcObject* mCube = new AcObject();
		mCube->setPosition(AcVector(0.0f, 0.f, 0.0f));
		mCube->createShape(ShapeType::ST_Sphere);

		mObjects.push_back(mCube);

		AcObject* mBlinnSphere = new AcObject();
		mBlinnSphere->setPosition(AcVector(2.0f, 1.f, 0.0f));
		mBlinnSphere->createShape(ShapeType::ST_Sphere);
		mObjects.push_back(mBlinnSphere);

		// Center the ground
		AcObject* mGround = new AcObject();
		AcTransform& transGround = mGround->GetTransform();
		transGround.setTranslation(AcVector(-5.0f, -1.0f, -5.0f));
		transGround.setScale(AcVector(10.0f, 10.0f, 10.0f));
		AcQuat quat = glm::angleAxis(glm::radians(90.0f), AcTransform::VecX);
		mGround->GetTransform().setRotation(quat);
		mGround->createShape(ShapeType::ST_Plane);
		mObjects.push_back(mGround);

	}

	void LightScene::update(float delta)
	{
		//Move the camera around
		float x = -10.f;
		float y = 3.f;
		float z = 10.f;
		x *= sin(mCameraMoveTime);
		z *= cos(mCameraMoveTime);
		mCam->setPosition(AcVector(x, y, z));
		mCameraMoveTime += (0.5f * delta);

		Scene::update(delta);
	}

	void LightScene::initRender(Renderer& r)
	{
		for (size_t i = 0; i < mObjects.size(); ++i)
		{
			mObjects[i]->initDraw(r);
		}
	}

	void LightScene::render(Renderer& r)
	{
		r.beginDraw();

		//	Scene::render();
		for (size_t i = 0; i < mObjects.size(); ++i)
		{
			mObjects[i]->draw(r, mCam, &mDirLight);
		}

		r.endDraw();
	}

	void LightScene::exit()
	{
		Scene::exit();

		SAFE_DELETE(mCam);
	}

#if ACROS_USE_IMGUI
	void LightScene::renderImgui()
	{
		Scene::renderImgui();
		// 	AcQuat quat = glm::angleAxis(glm::radians(angle), rot);
	}
#endif

}