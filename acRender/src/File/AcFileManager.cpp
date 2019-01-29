#include "AcFileManager.h"
#include "SDL_rwops.h"
#include "SDL_filesystem.h"
#include <cassert>
#include "utils.h"

using namespace std;

#if USE_OGL_3_LATEST
const string ShaderPath = "res/shader/desktop/";
#else
const string ShaderPath = "res/shader/mobile/";
#endif

namespace Acros {
	int FileManager::loadStringFromFile(const string& fileName, string & content)
	{
		string prefix = SDL_GetBasePath();
		string fullName = prefix + fileName;
		SDL_RWops *file = SDL_RWFromFile(fullName.c_str(), "r");
		if (file != nullptr)
		{
			char buf[1024];
			int sz = file->size(file);
			assert(1024 > sz);
			int blocks = SDL_RWread(file, buf, 16, 1024 / 16);
			SDL_RWclose(file);
			if (blocks < 0) {
				fprintf(stderr, "Couldn't read from %s.\n", fullName.c_str());
				return -2;
			}

			buf[sz] = '\0';
			content = buf;
			SDL_RWclose(file);
			return 0;
		}

		return -1;
	}

	int FileManager::loadShaderFile(const string& shaderFile,string& content)
	{
		string prefix = SDL_GetBasePath();
		string fullName = prefix + ShaderPath + shaderFile;
		SDL_RWops *file = SDL_RWFromFile(fullName.c_str(), "r");
		if (file != nullptr)
		{
			char buf[1024];
			int sz = file->size(file);
			assert(1024 > sz);
			int blocks = SDL_RWread(file, buf, 16, 1024 / 16);
			SDL_RWclose(file);
			if (blocks < 0) {
				fprintf(stderr, "Couldn't read from %s.\n", fullName.c_str());
				return -2;
			}

			buf[sz] = '\0';
			content = buf;
			SDL_RWclose(file);
			return 0;
		}

		return -1;
	}
}