#include "Material.h"
#include "File/AcFileManager.h"

using namespace Acros;
using namespace std;

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
}

void Material::initShader(Renderer& context, ShaderType type)
{
	assert(Verts.find(type) != Verts.end() && Frags.find(type) != Frags.end());

	string vertStr,fragStr;
	FileManager::loadShaderFile(Verts[type], vertStr);
	FileManager::loadShaderFile(Frags[type], fragStr);
	mShaderProgram = context.loadShaderProgram(vertStr, fragStr);

	mMvpLoc = glGetUniformLocation(mShaderProgram, "u_mvpMatrix");

	if (type == LightLambert)
	{
		mLightDir = glGetUniformLocation(mShaderProgram, "u_light_dir");
		mLightColor = glGetUniformLocation(mShaderProgram, "u_lightColor");

		flag = LightDir  | LightColor;
	}
}
