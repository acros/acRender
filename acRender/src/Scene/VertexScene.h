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

protected:

	class AcObject*	mObj;

};