#pragma once

#include <string>
#include <map>
#include "Renderer.h"

using namespace std;

namespace Acros
{
	enum ShaderFlag
	{
		LightDir = 1 << 1,
		LightColor = 1 << 2,

		EyePos =  1 << 3,
		Specular = 1<<4,

		MV		= 1<<5,
		WorldMatrix = 1<<6,
		ScreenSpace =  1 << 7,

		TexCoord	= 1 << 8,
		Color		= 1 << 9
	};

	enum ShaderType
	{
		Invalid = 0,

		SimpleVertex,
		VertexColor,	//All from vertex data
		LightLambert,
		LightBlinnPhong,

		Screen_Color,
		Screen_Tex
	};


	class Material
	{
	public:
		static void InitCache();

		Material(ShaderType type)
			: mMvpLoc(-1)
			, mMvLoc(-1)
			, mWorldMatrixLoc(-1)
			, mShaderProgram(-1)
			, mFlag(0)
			, mEyePos(0)
			, mSpecularParam(0)
			, mType(type)
		{}

		int	GetFlag()const { return mFlag; }

		void initShader(Renderer& context);

		void setDiffuse(const AcColor4& c) { mDiffuse = c; }
		const AcColor4& getDiffuse()const { return mDiffuse; }

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
		ShaderType	mType;

		//Material Params
		AcColor4	mDiffuse;
		AcColor4	mSpecular;


		int		mFlag;

		static map<ShaderType, string> Verts;
		static map<ShaderType, string> Frags;
	};

}
