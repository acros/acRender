#include "Material.h"
#include "File/AcFileManager.h"

using namespace Acros;
using namespace std;


void Material::loadShader(Renderer& context,const string& file)
{
	string vertStr,fragStr;
	FileManager::loadShaderFile("simple_color_mvp.vert", vertStr);
	FileManager::loadShaderFile("simple_color_mvp.frag", fragStr);

	mShaderProgram = context.loadShaderProgram(vertStr.c_str(), fragStr.c_str());
	mMvpLoc = glGetUniformLocation(mShaderProgram, "u_mvpMatrix");

}
