#pragma once

#include "Scene.hpp"

/*
	Basic Example
*/
using Acros::Scene;
using Acros::Renderer;

class TriangleScene : public Scene
{
public:
	TriangleScene();
	~TriangleScene();

	virtual void enter()override;

	virtual void render(Renderer& r)override;

	virtual void exit()override;
protected:

	GLuint          mColorBuffer;
};