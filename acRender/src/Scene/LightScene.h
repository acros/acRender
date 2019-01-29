#pragma once

#include "Scene.hpp"
#include "Camera/Camera.h"

/*
	The Light scene
*/
class LightScene : public Scene
{
public:
	LightScene(Renderer& renderer);
	~LightScene();

	virtual void enter()override;

	virtual void update(float delta);

	virtual void render()override;

	virtual void exit()override;

#if ACROS_USE_IMGUI
	virtual void renderImgui();
#endif 


protected:

//	GLuint		mFbo;

	float		mCameraMoveTime;

	Camera*		mCam;

	AcObject*	mCube;
	AcObject*	mGround;

};