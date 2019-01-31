#pragma once

#include "Scene.hpp"

/*
	Vertex VBO Draw
*/
namespace Acros
{
	class VertexScene : public Scene
	{
	public:
		VertexScene();
		~VertexScene();

		virtual void enter()override;

		virtual void initRender(Renderer& r)override;
		virtual void render(Renderer& r)override;

		virtual void exit()override;

		virtual void update(float delta)override;

#if ACROS_USE_IMGUI
		virtual void renderImgui() override;
#endif

	protected:

		class AcObject*	mObj;
		class Camera*	mCam;
	};
}
