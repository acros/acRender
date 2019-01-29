#pragma once

#include "Scene.hpp"

class SimpleTriangle : public Scene
{
public:
	SimpleTriangle(Renderer& renderer);
	~SimpleTriangle();

	virtual void enter()override;

	virtual void render()override;

	virtual void exit()override;

protected:

	void drawWithVertexArray();
	void drawWithVBO();

};