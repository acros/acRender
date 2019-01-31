#pragma once

#include <string>
#include "Math/AcMath.h"
#include "Math/AcTranform.h"

using namespace std;

namespace Acros
{
	enum ShapeType
	{
		ST_Cube,
		ST_Plane,
		ST_ColorTriangle,
		ST_Sphere
	};


	enum ShaderFlag
	{
		ReceiveLight = 1 << 1,

		EyePos = 1 << 3,
		Specular = 1 << 4,

		WorldSpace = 1 << 6,
		ScreenSpace = 1 << 7,

		//Attribute
		UVCoord = 1 << 8,
		Color = 1 << 9,
		Normal = 1 << 10
	};

	enum ShaderType
	{
		Invalid = 0,

		VertexColor,	//All from vertex data
		LightLambert,
		LightBlinnPhong,

		Screen_Color,
		Screen_Tex
	};



	class Renderer {
	public:
		Renderer();
		~Renderer();

		void checkRendererVersion()const;

		void	setViewport(int width, int height);
		AcUint	loadShaderProgram(const string& vertStr, const string& fragStr);

		void	beginDraw();

		void	draw();

		void	endDraw();

		GLuint createSimpleTexture2D(int w, int h, GLubyte* pixels);

	protected:

		AcUint loadShader(AcEnum type, const char *shaderSrc);

	};
}
