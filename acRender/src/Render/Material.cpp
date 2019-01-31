#include "Material.h"
#include "File/AcFileManager.h"

using namespace std;

namespace Acros
{
	std::map<ShaderType, std::string> Material::Verts;
	std::map<ShaderType, std::string> Material::Frags;

	void Material::InitCache()
	{
		Verts.clear();
		Frags.clear();

		Verts.insert(make_pair(VertexColor, "simple_color_mvp.vert"));
		Frags.insert(make_pair(VertexColor, "simple_color_mvp.frag"));

		Verts.insert(make_pair(LightLambert, "lambert_mvp.vert"));
		Frags.insert(make_pair(LightLambert, "lambert_mvp.frag"));

		Verts.insert(make_pair(LightBlinnPhong, "blinn_phong_mvp.vert"));
		Frags.insert(make_pair(LightBlinnPhong, "blinn_phong_mvp.frag"));
	}

	void Material::initShader(Renderer& context, ShaderType type)
	{
		assert(Verts.find(type) != Verts.end() && Frags.find(type) != Frags.end());

		string vertStr, fragStr;
		FileManager::loadShaderFile(Verts[type], vertStr);
		FileManager::loadShaderFile(Frags[type], fragStr);
		mShaderProgram = context.loadShaderProgram(vertStr, fragStr);

		switch (type)
		{
		case VertexColor:
			break;
		case LightLambert:
			mFlag = LightDir | LightColor | WorldMatrix;
			break;
		case LightBlinnPhong:
			mFlag = LightDir | LightColor | EyePos | Specular | WorldMatrix;
			break;
		default:
			break;
		}

		mMvpLoc = glGetUniformLocation(mShaderProgram, "u_mvpMatrix");

		if (mFlag | MV)
			mMvLoc = glGetUniformLocation(mShaderProgram, "u_mvMatrix");

		if (mFlag | WorldMatrix)
			mWorldMatrixLoc = glGetUniformLocation(mShaderProgram, "u_WorldMatrix");

		if (mFlag | LightDir)
			mLightDir = glGetUniformLocation(mShaderProgram, "u_light_dir");

		if (mFlag | LightColor)
			mLightColor = glGetUniformLocation(mShaderProgram, "u_lightColor");

		if (mFlag | EyePos)
			mEyePos = glGetUniformLocation(mShaderProgram, "u_eye_pos");

		if (mFlag | Specular)
			mSpecularParam = glGetUniformLocation(mShaderProgram, "u_specular");
	}
}
