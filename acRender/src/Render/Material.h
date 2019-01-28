#pragma once

#include <string>
#include "Renderer.h"

using namespace std;

class Material
{
public:
	Material():mMvpLoc(-1), mShaderProgram(-1)
	{}

	void loadShader(Renderer& context,const string& vert,const string& frag);

//	void loadSimpleShader(Renderer& context);

	AcUint	mShaderProgram;

	//default value
	AcInt	mMvpLoc;

};

