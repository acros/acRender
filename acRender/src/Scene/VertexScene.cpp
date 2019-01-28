#include "VertexScene.h"
#include "utils.h"
#include "Base/AcUtils.h"
#include "Base/AcObject.h"

VertexScene::VertexScene(Renderer& renderer)
	: Scene(renderer)
{

}

VertexScene::~VertexScene()
{

}

void VertexScene::enter()
{
	Scene::enter();

	mObj = new AcObject();
	mObj->createShape(ST_ColorTriangle);
	mObj->initDraw(mRendererRef);
}

void VertexScene::render()
{
	mRendererRef.beginDraw();

	AcMatrix sx,xx;
	mObj->draw(mRendererRef,sx,xx);

	mRendererRef.endDraw();
}


void VertexScene::exit()
{
	Scene::exit();

	SAFE_DELETE(mObj);
}

