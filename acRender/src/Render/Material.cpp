#include "Material.h"
#include "File/AcFileManager.h"

using namespace Acros;
using namespace std;

void initShader(Renderer& context, ShaderType type)
{
	string vertStr,fragStr;
	FileManager::loadShaderFile("simple_color_mvp.vert", vertStr);
	FileManager::loadShaderFile("simple_color_mvp.frag", fragStr);

	mShaderProgram = context.loadShaderProgram(vertStr, fragStr);
	mMvpLoc = glGetUniformLocation(mShaderProgram, "u_mvpMatrix");

}
