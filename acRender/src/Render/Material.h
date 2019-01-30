#pragma once

#include <string>
#include <map>
#include "Renderer.h"

using namespace std;

enum ShaderFlag
{
	LightDir = 1 << 1,
	LightColor = 1 << 2,
};

enum ShaderType
{
	VertexColor = 0,
	LightLambert = 1
};


class Material
{
public:
	static void InitCache();

	Material():mMvpLoc(-1), mShaderProgram(-1), flag(0)
	{}

	void initShader(Renderer& context, ShaderType type);

	//Shader 
	AcUint	mShaderProgram;
	AcInt	mMvpLoc;

	GLint	mLightColor;
	GLint	mLightDir;

protected:
	//Material Params
	AcColor3	mDiffuse;
	AcColor3	mSpecular;

	int		flag;

	static map<ShaderType, string> Verts;
	static map<ShaderType, string> Frags;
};

