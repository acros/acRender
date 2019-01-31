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

		Verts.insert(make_pair(SimpleVertex, "simple_color_mvp.vert"));
		Frags.insert(make_pair(SimpleVertex, "simple_color_mvp.frag"));

		Verts.insert(make_pair(VertexColor, "simple_color_mvp.vert"));
		Frags.insert(make_pair(VertexColor, "simple_color_mvp.frag"));

		Verts.insert(make_pair(LightLambert, "lambert_mvp.vert"));
		Frags.insert(make_pair(LightLambert, "lambert_mvp.frag"));

		Verts.insert(make_pair(LightBlinnPhong, "blinn_phong_mvp.vert"));
		Frags.insert(make_pair(LightBlinnPhong, "blinn_phong_mvp.frag"));

		Verts.insert(make_pair(Screen_Color, "simple_color_2d.vert"));
		Frags.insert(make_pair(Screen_Color, "simple_color_2d.frag"));

		Verts.insert(make_pair(Screen_Tex, "tex_2d.vert"));
		Frags.insert(make_pair(Screen_Tex, "tex_2d.frag"));

		
	}

	void Material::initShader(Renderer& context)
	{
		assert(Verts.find(mType) != Verts.end() && Frags.find(mType) != Frags.end());

		string vertStr, fragStr;
		FileManager::loadShaderFile(Verts[mType], vertStr);
		FileManager::loadShaderFile(Frags[mType], fragStr);
		mShaderProgram = context.loadShaderProgram(vertStr, fragStr);

		switch (mType)
		{
		case SimpleVertex:
			break;
		case VertexColor:
			break;
		case LightLambert:
			mFlag = LightDir | LightColor | WorldMatrix;
			break;
		case LightBlinnPhong:
			mFlag = LightDir | LightColor | EyePos | Specular | WorldMatrix;
			break;
		case Screen_Tex:
			mFlag = TexCoord | ScreenSpace;
			break;
		case Screen_Color:
			mFlag = Color | ScreenSpace;
			break;
		default:
			assert(false);
			break;
		}

		if(!(mFlag & ScreenSpace))
			mMvpLoc = glGetUniformLocation(mShaderProgram, "u_mvpMatrix");

		if (mFlag & MV)
			mMvLoc = glGetUniformLocation(mShaderProgram, "u_mvMatrix");

		if (mFlag & WorldMatrix)
			mWorldMatrixLoc = glGetUniformLocation(mShaderProgram, "u_WorldMatrix");

		if (mFlag & LightDir)
			mLightDir = glGetUniformLocation(mShaderProgram, "u_light_dir");

		if (mFlag & LightColor)
			mLightColor = glGetUniformLocation(mShaderProgram, "u_lightColor");

		if (mFlag & EyePos)
			mEyePos = glGetUniformLocation(mShaderProgram, "u_eye_pos");

		if (mFlag & Specular)
			mSpecularParam = glGetUniformLocation(mShaderProgram, "u_specular");
	}
}
