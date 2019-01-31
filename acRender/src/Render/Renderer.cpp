#include "Renderer.h"
#include "Base/AcUtils.h"
#include "Material.h"

namespace Acros
{
	Renderer::Renderer()
	{
		Material::InitCache();
	}

	Renderer::~Renderer()
	{

	}

	void Renderer::setViewport(int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void Renderer::checkRendererVersion() const
	{
		//Check glVersion
		const char* glVer = (const char*)glGetString(GL_VERSION);
		logMessage("OpenGL-ES version is : %s.\n", glVer);

		const char* glShaderVer = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
		logMessage("OpenGL-ES shader version is : %s.\n", glShaderVer);
	}

	GLuint Renderer::loadShaderProgram(const string& vertStr, const string& fragStr)
	{
		GLuint vertexShader;
		GLuint fragmentShader;
		GLint linked;

		// Load the vertex/fragment shaders
		vertexShader = loadShader(GL_VERTEX_SHADER, vertStr.c_str());
		fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragStr.c_str());

		// Create the program object
		AcInt programObject = glCreateProgram();

		if (programObject == 0)
		{
			return 0;
		}

		glAttachShader(programObject, vertexShader);
		glAttachShader(programObject, fragmentShader);

		// Link the program
		glLinkProgram(programObject);

		// Check the link status
		glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

		if (!linked)
		{
			GLint infoLen = 0;

			glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);

			if (infoLen > 1)
			{
				char *infoLog = (char*)malloc(sizeof(char) * infoLen);

				glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
				logMessage("Error linking program:\n%s\n", infoLog);

				free(infoLog);
			}

			glDeleteProgram(programObject);
			return 0;
		}

		return programObject;
	}


	void Renderer::beginDraw()
	{
		glUseProgram(0);
		glClearColor(0.2f, 0.2f, 0.2f, 0.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Renderer::draw()
	{

	}

	void Renderer::endDraw()
	{

	}

	AcUint Renderer::loadShader(AcEnum type, const char *shaderSrc)
	{
		GLuint shader;
		GLint compiled;

		// Create the shader object
		shader = glCreateShader(type);

		if (shader == 0)
		{
			return 0;
		}

		// Load the shader source
		glShaderSource(shader, 1, &shaderSrc, NULL);

		// Compile the shader
		glCompileShader(shader);

		// Check the compile status
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

		if (!compiled)
		{
			GLint infoLen = 0;

			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

			GLenum sx = glGetError();
			logMessage("GL state error: %d", sx);

			if (infoLen > 1)
			{
				char *infoLog = (char*)malloc(sizeof(char) * infoLen);

				glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
				logMessage("Error compiling shader:\n%s\n", infoLog);

				free(infoLog);
			}

			glDeleteShader(shader);
			return 0;
		}

		return shader;
	}


	GLuint Renderer::createSimpleTexture2D(int w,int h,GLubyte* pixels)
	{
		GLuint textureId;

		for (int i = 0; i < w * h * 3; ++i)
		{
			pixels[i] = rand() % 256;
		}

		// Use tightly packed data
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// Generate a texture object
		glGenTextures(1, &textureId);

		// Bind the texture object
		glBindTexture(GL_TEXTURE_2D, textureId);

		// Load the texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);


		// Set the filtering mode
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		return textureId;
	}

}