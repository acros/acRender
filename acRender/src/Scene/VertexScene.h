#pragma once

#include "Scene.hpp"

/*
	Vertex VBO Draw
*/
class VertexScene : public Scene
{
public:
	VertexScene(Renderer& renderer);
	~VertexScene();

	virtual void enter()override;

	virtual void render()override;

	virtual void exit()override;

	virtual void update(float delta)override;

#if ACROS_USE_IMGUI
	virtual void renderImgui() override;
#endif

protected:

	class AcObject*	mObj;
	class Camera*	mCam;

};