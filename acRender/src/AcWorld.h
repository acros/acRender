#pragma once

#include "Render/Renderer.h"
#include "Base/AcUtils.h"

namespace Acros
{
	class World
	{
	public:
		World();

		void setViewSize(int x, int y);

		void update(float deltaTime);

		void render();

#if ACROS_USE_IMGUI
		void drawImGui();
#endif 

		void quit();

	protected:
		void quitScene();
			
		Renderer	mRenderer;

	private:
		class Scene* mRunningScene;
		int mSceneSelection;
		int mCurrenSceneIdx;
	};
}