#include "VertexScene.h"
#include "utils.h"
#include "Base/AcUtils.h"
#include "Base/AcObject.h"
#include "Camera/Camera.h"

namespace Acros
{

	VertexScene::VertexScene()
		: Scene()
		, mObj(nullptr)
		, mCam(nullptr)
	{

	}

	VertexScene::~VertexScene()
	{

	}

	void VertexScene::enter()
	{
		Scene::enter();

		//Set camera 
		mCam = new Camera(1280 / 720.f, 45, 1.f, 1000.f);
		AcVector eyePos(0.f, 0.f, -5.f);
		mCam->setViewMat(eyePos, AcVector(0), AcVector(0, 1, 0));
		mObj = new AcObject();
		mObj->createShape(ST_ColorTriangle);
	}

	void VertexScene::initRender(Renderer & r)
	{
		mObj->initDraw(r);
	}

	void VertexScene::render(Renderer& r)
	{
		r.beginDraw();

		mObj->draw(r, mCam);

		r.endDraw();
	}


	void VertexScene::exit()
	{
		Scene::exit();

		SAFE_DELETE(mObj);
		SAFE_DELETE(mCam);
	}

	void VertexScene::update(float delta)
	{
		static float angle = 0;
		static float spd = 2;
		angle += (spd * delta);

		if (mObj != nullptr)
		{
			mObj->rotate(AcVector(0, 1, 0), angle);
		}
	}

#if ACROS_USE_IMGUI
	void VertexScene::renderImgui()
	{
		static float fov = 45;
		ImGui::SliderFloat("FOV", &fov, 30.0f, 120.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

		if (mCam->getFov() != fov)
		{
			mCam->setPersp(1280 / 720.f, fov, 1.f, 1000.f);
		}
	}
#endif
}