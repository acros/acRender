#pragma once

#include "Scene.hpp"

/*
	Example For GL Texture use
*/
class TextureScene : public Scene
{
public:
	TextureScene(Renderer& renderer);
	~TextureScene();

	virtual void enter()override;

	virtual void update(float delta)override;

	virtual void render()override;

	virtual void exit()override;

protected:

	GLuint createSimpleTexture2D();

	float	mTexUpdateDuration;
	float	mTimeAcculation;
	bool	mSubmitTex;

	GLint mSampleLocation;
	GLuint mTexId;
};