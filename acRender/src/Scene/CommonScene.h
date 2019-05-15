#pragma once

#include "Scene.hpp"
#include "Camera/Camera.h"

/*
	The common scene
*/
namespace Acros
{
	class CommonScene : public Scene
	{
	public:
		CommonScene();
		~CommonScene();

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
