#include "CommonScene.h"
#include "Base/AcObject.h"

namespace Acros
{

	CommonScene::CommonScene()
		: Scene()
		, mCam(nullptr)
		, mCameraMoveTime(0.f)
	{}

	CommonScene::~CommonScene()
	{

	}

	void CommonScene::enter()
	{
		Scene::enter();

		//Set camera 
		mCam = new Camera(1280 / 720.f, 60.f, 1.f, 100000.f);
		AcVector eyePos(-100.f, 30.f, 100.f);
		mCam->setViewMat(eyePos, AcVector(0, 0, -3), AcVector(0, 1, 0));
		const AcMatrix& vieMat = mCam->getViewMat();

		AcObject* plyModel = new AcObject();
		plyModel->setPosition(AcVector(0.0f, 0.f, 0.0f));
		plyModel->loadMesh("sofa.ply", Acros::ShaderType::LightBlinnPhong);

		mObjects.push_back(plyModel);
	}

	void CommonScene::update(float delta)
	{
		//Move the camera around
		static float k =1.0f;
		float x = k * -100.f;
		float y = 0.f;
		float z = k * 100.f;
		x *= sin(mCameraMoveTime);
		z *= cos(mCameraMoveTime);
		mCam->setPosition(AcVector(x, y, z));
		mCameraMoveTime += (0.5f * delta);

		Scene::update(delta);
	}

	void CommonScene::initRender(Renderer& r)
	{
		for (size_t i = 0; i < mObjects.size(); ++i)
		{
			mObjects[i]->initDraw(r);
		}
	}
	
	void CommonScene::render(Renderer& r)
	{
		r.beginDraw();

		//	Scene::render();
		for (size_t i = 0; i < mObjects.size(); ++i)
		{
			mObjects[i]->draw(r, mCam, &mDirLight);
		}

		r.endDraw();
	}

	void CommonScene::exit()
	{
		Scene::exit();

		SAFE_DELETE(mCam);
	}

#if ACROS_USE_IMGUI
	void CommonScene::renderImgui()
	{
		Scene::renderImgui();
		// 	AcQuat quat = glm::angleAxis(glm::radians(angle), rot);
	}
#endif

}