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
