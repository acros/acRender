#pragma once

#include <string>
#include <map>
#include "Renderer.h"

using namespace std;

enum ShaderFlag
{
	LightDir = 1 << 1,
	LightColor = 1 << 2,

	EyePos =  1 << 3,
	Specular = 1<<4,

	MV		= 1<<5,
	WorldMatrix = 1<<6,
};

enum ShaderType
{
	VertexColor = 0,
	LightLambert = 1,
	LightBlinnPhong = 2
};


class Material
{
public:
	static void InitCache();

	Material()
		: mMvpLoc(-1)
		, mMvLoc(-1)
		, mWorldMatrixLoc(-1)
		, mShaderProgram(-1)
		, mFlag(0)
		, mEyePos(0)
		, mSpecularParam(0)
	{}

	int	GetFlag()const { return mFlag; }

	void initShader(Renderer& context, ShaderType type);

	//Shader 
	AcUint	mShaderProgram;
	AcInt	mMvpLoc;
	AcInt	mMvLoc;
	AcInt	mWorldMatrixLoc;

	GLint	mLightColor;
	GLint	mLightDir;

	GLint	mEyePos;
	GLint	mSpecularParam;
protected:
	//Material Params
	AcColor3	mDiffuse;
	AcColor3	mSpecular;


	int		mFlag;

	static map<ShaderType, string> Verts;
	static map<ShaderType, string> Frags;
};

