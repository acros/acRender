#include "LightScene.h"

LightScene::LightScene(Renderer& renderer)
	: Scene(renderer)
	, mCam(nullptr)
	, mCube(nullptr)
	, mGround(nullptr)
	, mCameraMoveTime(0.f)
	, mDirLight(Acros::Directional,AcVector(1,-1,1),AcColor3(0.5f,0.5f,0.5f))
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

	mCube = new AcObject();
	mCube->setPosition(AcVector(0.0f, 0.f, 0.0f));
	mCube->rotate(AcVector(0.0f, 1.0f, 0.0f),-15.f);
	mCube->createShape(ShapeType::ST_Sphere);
	mCube->initDraw(mRendererRef);

	// Center the ground
	mGround = new AcObject();
	AcTransform& transGround = mGround->GetTransform();
	transGround.setTranslation(AcVector(-5.0f, -1.0f, -5.0f));
	transGround.setScale(AcVector(10.0f, 10.0f, 10.0f));
	AcQuat quat = glm::angleAxis(glm::radians(90.0f), AcTransform::VecX);
	mGround->GetTransform().setRotation(quat);

	mGround->createShape(ShapeType::ST_Plane);
	mGround->initDraw(mRendererRef);
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
}

void LightScene::render()
{
	glUseProgram(0);
	glClearColor(0.2f, 0.2f, 0.2f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	mCube->draw(mRendererRef, mCam,&mDirLight);
	mGround->draw(mRendererRef, mCam);
}

void LightScene::exit()
{
	Scene::exit();

	SAFE_DELETE(mCam);
	SAFE_DELETE(mCube);
	SAFE_DELETE(mGround);
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
