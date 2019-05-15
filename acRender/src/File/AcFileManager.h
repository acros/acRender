#pragma once

#include <string>

using namespace std;

namespace Acros
{
	class FileManager
	{
	public:
		static int loadStringFromFile(const string& fileName, string& content);

		static int loadShaderFile(const string& shaderFile,string& content);

		static class Mesh* LoadModelPlyFile(const string& fileName);
	};


}
