#pragma once

#include "Scene.hpp"
using Acros::Scene;
using Acros::Renderer;

class SimpleTriangle : public Scene
{
public:
	SimpleTriangle();
	~SimpleTriangle();

	virtual void enter()override;

	virtual void render(Renderer& r)override;

	virtual void exit()override;

protected:

	void drawWithVertexArray();
	void drawWithVBO();

};