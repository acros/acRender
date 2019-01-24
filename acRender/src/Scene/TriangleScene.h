#pragma once

#include "Scene.hpp"

/*
	Basic Example
*/
class TriangleScene : public Scene
{
public:
	TriangleScene(Renderer& renderer);
	~TriangleScene();

	virtual void enter()override;

	virtual void render()override;

	virtual void exit()override;
protected:


	GLuint          mVAO;
	GLuint          mPosBuffer;
	GLuint          mColorBuffer;
	GLuint          mIdxBuffer;

//	GLuint mFBO;
};