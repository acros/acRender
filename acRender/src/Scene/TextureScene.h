#pragma once

#include "Scene.hpp"

/*
	Example For GL Texture use
*/
using Acros::Scene;
using Acros::Renderer;

class TextureScene : public Scene
{
public:
	TextureScene();
	~TextureScene();

	virtual void enter()override;

	virtual void update(float delta)override;

	virtual void render(Renderer& r)override;

	virtual void exit()override;

protected:

	GLuint createSimpleTexture2D();

	float	mTexUpdateDuration;
	float	mTimeAcculation;
	bool	mSubmitTex;

	GLint mSampleLocation;
	GLuint mTexId;
};