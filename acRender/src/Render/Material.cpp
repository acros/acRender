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

		Verts.insert(make_pair(Screen_Color, "screen_color_2d.vert"));
		Frags.insert(make_pair(Screen_Color, "screen_color_2d.frag"));

		Verts.insert(make_pair(Screen_Tex, "screen_tex_2d.vert"));
		Frags.insert(make_pair(Screen_Tex, "screen_tex_2d.frag"));

		
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
		case VertexColor:
			mFlag = WorldSpace | Color;
			break;
		case LightLambert:
			mFlag = ReceiveLight | WorldSpace | Normal;
			break;
		case LightBlinnPhong:
			mFlag = ReceiveLight | EyePos | Specular | WorldSpace | Normal;
			break;
		case Screen_Tex:
			mFlag = UVCoord | ScreenSpace;
			break;
		case Screen_Color:
			mFlag = Color | ScreenSpace;
			break;
		default:
			assert(false);
			break;
		}

		assert((mFlag & ScreenSpace & WorldSpace) == 0);

		if(mFlag & WorldSpace)
			mMvpLoc = glGetUniformLocation(mShaderProgram, "u_mvpMatrix");

// 		if (mFlag & MV)
// 			mMvLoc = glGetUniformLocation(mShaderProgram, "u_mvMatrix");

// 		if (mFlag & WorldMatrix)
// 			mWorldMatrixLoc = glGetUniformLocation(mShaderProgram, "u_WorldMatrix");

		if (mFlag & ReceiveLight)
		{
			mLightDir = glGetUniformLocation(mShaderProgram, "u_light_dir");
			mLightColor = glGetUniformLocation(mShaderProgram, "u_lightColor");
		}

		if (mFlag & EyePos)
			mEyePos = glGetUniformLocation(mShaderProgram, "u_eye_pos");

		if (mFlag & Specular)
			mSpecularParam = glGetUniformLocation(mShaderProgram, "u_specular");
	}
}
