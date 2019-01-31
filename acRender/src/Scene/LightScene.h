#pragma once

#include "Scene.hpp"
#include "Camera/Camera.h"

/*
	The Light scene
*/
namespace Acros
{
	class LightScene : public Scene
	{
	public:
		LightScene();
		~LightScene();

		virtual void enter()override;

		virtual void update(float delta);

		virtual void initRender(Renderer& r)override;
		virtual void render(Renderer& r)override;

		virtual void exit()override;

#if ACROS_USE_IMGUI
		virtual void renderImgui();
#endif 


	protected:

		float		mCameraMoveTime;

		Camera*		mCam;
	};
}
