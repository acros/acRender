#pragma once

#include <string>
#include "Base/Math.h"

using namespace std;


enum ShapeType
{
	ST_Cube,
	ST_Plane,
};

class Renderer {
public:
	Renderer();
	~Renderer();

	void checkRendererVersion()const;

	void	setViewport(int width,int height);
	AcUint	loadShaderProgram(const string& vertStr,const string& fragStr);

	void	beginDraw();

	void	draw();

	void	endDraw();

protected:

	AcUint loadShader(AcEnum type, const char *shaderSrc);

protected:

	AcUint mProgramObject;

};