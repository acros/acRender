#include "VertexScene.h"
#include "utils.h"
#include "Base/AcUtils.h"
#include "Base/AcObject.h"
#include "Camera/Camera.h"

VertexScene::VertexScene(Renderer& renderer)
	: Scene(renderer)
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
	mCam = new Camera(800 / 600.f, 45.f, 1.f, 1000.f);
	AcVector eyePos(0.f, 0.f, 10.f);
	//AcVector eyePos(0.f, 0.f, 10.f);
//	mCam->setLookAt(AcVector());	mCam->setPosition(eyePos);
	mObj = new AcObject();
	mObj->createShape(ST_ColorTriangle);
	mObj->initDraw(mRendererRef);
}

void VertexScene::render()
{
	mRendererRef.beginDraw();

	mObj->draw(mRendererRef, mCam->getViewMat(), mCam->getProjMat());

	mRendererRef.endDraw();
}


void VertexScene::exit()
{
	Scene::exit();

	SAFE_DELETE(mObj);
}

