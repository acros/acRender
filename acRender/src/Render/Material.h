#pragma once

#include <string>
#include "Renderer.h"

using namespace std;

enum ShaderFlag
{
	MVP  = 0x1,
	
	Vertex = 0x10,
	Color = 0x20,
	Normal = 0x30,
};

enum ShaderType
{
	VertexColor = 0,
	LightLambert = 1
};


class Material
{
public:
	Material():mMvpLoc(-1), mShaderProgram(-1)
	{}

	void initShader(Renderer& context, ShaderType type);

	//Shader 
	AcUint	mShaderProgram;
	AcInt	mMvpLoc;

protected:
	//Material Params
	AcColor3	mDiffuse;
	AcColor3	mSpecular;



};

