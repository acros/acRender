#include "LightScene.h"

LightScene::LightScene(Renderer& renderer)
	: Scene(renderer)
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
	mCam = new Camera(1280/720.f,60.f,1.f,1000.f);
	AcVector eyePos(-10.f, 3.f, 10.f);
	mCam->setViewMat(eyePos, AcVector(0, 0, -3), AcVector(0, 1, 0));
	const AcMatrix& vieMat = mCam->getViewMat();

	AcObject* mCube = new AcObject();
	mCube->setPosition(AcVector(0.0f, 0.f, 0.0f));
	mCube->createShape(ShapeType::ST_Sphere);
	mCube->initDraw(mRendererRef);

	mObjects.push_back(mCube);

	AcObject* mBlinnSphere = new AcObject();
	mBlinnSphere->setPosition(AcVector(2.0f, 1.f, 0.0f));
	mBlinnSphere->createShape(ShapeType::ST_Sphere);
	mBlinnSphere->initDraw(mRendererRef);
	mObjects.push_back(mBlinnSphere);

	// Center the ground
	AcObject* mGround = new AcObject();
	AcTransform& transGround = mGround->GetTransform();
	transGround.setTranslation(AcVector(-5.0f, -1.0f, -5.0f));
	transGround.setScale(AcVector(10.0f, 10.0f, 10.0f));
	AcQuat quat = glm::angleAxis(glm::radians(90.0f), AcTransform::VecX);
	mGround->GetTransform().setRotation(quat);
	mGround->createShape(ShapeType::ST_Plane);
	mGround->initDraw(mRendererRef);
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
	mCam->setPosition(AcVector(x,y,z));
	mCameraMoveTime += (0.5f * delta);

	Scene::update(delta);
}

void LightScene::render()
{
	mRendererRef.beginDraw();

//	Scene::render();
	for (size_t i = 0; i < mObjects.size(); ++i)
	{
		mObjects[i]->draw(mRendererRef, mCam, &mDirLight);
	}

	mRendererRef.endDraw();
}

void LightScene::exit()
{
	Scene::exit();

	SAFE_DELETE(mCam);
}

#if ACROS_USE_IMGUI
void LightScene::renderImgui()
{
	static AcVector LDIR(1, -1, 1);
	ImGui::SliderFloat("X", &LDIR.x, -1, 1);
	ImGui::SliderFloat("Y", &LDIR.y, -1, 1);
	ImGui::SliderFloat("Z", &LDIR.z, -1, 1);
 	mDirLight.setDir(LDIR);

	static float color[3]{1,1,1};
	ImGui::ColorEdit3("Light Color", color);
	mDirLight.setColor(AcColor3(color[0],color[1],color[2]));
// 	AcQuat quat = glm::angleAxis(glm::radians(angle), rot);
}
#endif
