#pragma once

#include "Scene.hpp"
#include "Camera/Camera.h"

/*
	The 3D scene

*/
namespace Acros
{
	class FboScene : public Scene
	{
	public:
		FboScene();
		~FboScene();

		virtual void enter()override;

		virtual void update(float delta);

		virtual void initRender(Renderer& r)override;

		virtual void render(Renderer& r)override;

		virtual void exit()override;

	protected:

		void drawMiniWindow();

	protected:
		bool		mRenderToTexture;
		GLuint		mFbo;
		GLuint		mTexId[2];

		float		mCameraMoveTime;

		Camera*		mCam;

		AcObject*	mCube;
		AcObject*	mGround;

	};
}
