#include "AcFileManager.h"
#include "SDL_rwops.h"
#include "SDL_filesystem.h"
#include <cassert>
#include "utils.h"
#include "Render/Mesh.h"


#include <thread>
#include <chrono>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <iterator>

#include "tinyply\tinyply.h"

using namespace tinyply;
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
			Sint64 sz = file->size(file);
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
		if (shaderFile.empty())
			return -1;

		string prefix = SDL_GetBasePath();
		string fullName = prefix + ShaderPath + shaderFile;
		SDL_RWops *file = SDL_RWFromFile(fullName.c_str(), "r");
		if (file != nullptr)
		{
			char buf[1024];
			Sint64 sz = file->size(file);
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

	Mesh* FileManager::LoadModelPlyFile(const string & shaderFile)
	{
		try
		{
			string prefix = SDL_GetBasePath();
			string fullName = prefix + ShaderPath + shaderFile;

			std::ifstream ss(fullName, std::ios::binary);
			if (ss.fail()) throw std::runtime_error("failed to open " + fullName);

			PlyFile file;
			file.parse_header(ss);

			std::cout << "........................................................................\n";
			for (auto c : file.get_comments()) std::cout << "Comment: " << c << std::endl;
			for (auto e : file.get_elements())
			{
				std::cout << "element - " << e.name << " (" << e.size << ")" << std::endl;
				for (auto p : e.properties) std::cout << "\tproperty - " << p.name << " (" << tinyply::PropertyTable[p.propertyType].str << ")" << std::endl;
			}
			std::cout << "........................................................................\n";

			// Tinyply treats parsed data as untyped byte buffers. See below for examples.
			std::shared_ptr<PlyData> vertices, normals, faces, texcoords;

			// The header information can be used to programmatically extract properties on elements
			// known to exist in the header prior to reading the data. For brevity of this sample, properties 
			// like vertex position are hard-coded: 
			try { vertices = file.request_properties_from_element("vertex", { "x", "y", "z" }); }
			catch (const std::exception & e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }

			try { normals = file.request_properties_from_element("vertex", { "nx", "ny", "nz" }); }
			catch (const std::exception & e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }

			try { texcoords = file.request_properties_from_element("vertex", { "u", "v" }); }
			catch (const std::exception & e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }

			// Providing a list size hint (the last argument) is a 2x performance improvement. If you have 
			// arbitrary ply files, it is best to leave this 0. 
			try { faces = file.request_properties_from_element("face", { "vertex_indices" }, 3); }
			catch (const std::exception & e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }


//			manual_timer read_timer;
//			read_timer.start();
			file.read(ss);

//			read_timer.stop();
//			std::cout << "Reading took " << read_timer.get() / 1000.f << " seconds." << std::endl;

			if (vertices) std::cout << "\tRead " << vertices->count << " total vertices " << std::endl;
			if (normals) std::cout << "\tRead " << normals->count << " total vertex normals " << std::endl;
			if (texcoords) std::cout << "\tRead " << texcoords->count << " total vertex texcoords " << std::endl;
			if (faces) std::cout << "\tRead " << faces->count << " total faces (triangles) " << std::endl;

			// type casting to your own native types - Option A
			{
				const size_t numVerticesBytes = vertices->buffer.size_bytes();
				assert(vertices->t == Type::FLOAT32);
				int vertsCount = numVerticesBytes / sizeof(float);
				float* verts = (float*)malloc(sizeof(float) * vertsCount);
				std::memcpy(verts, vertices->buffer.get(), numVerticesBytes);

				const size_t numNormalBytes = normals->buffer.size_bytes();
				assert(normals->t == Type::FLOAT32);
				int normalCount = numNormalBytes / sizeof(float);
				float* norms = new float[normalCount];
				std::memcpy(norms, normals->buffer.get(), numNormalBytes);

				const size_t numTexCoordBytes = texcoords->buffer.size_bytes();
				assert(texcoords->t == Type::FLOAT32);
				int texCoordCount = numTexCoordBytes / sizeof(float);
				float* texCoords = new float[texCoordCount];
				std::memcpy(texCoords, texcoords->buffer.get(), numTexCoordBytes);

				const size_t numIndicesBytes = faces->buffer.size_bytes();
				assert(faces->t == Type::INT32);
				unsigned indicesCount = numIndicesBytes / sizeof(unsigned int);
				unsigned int* indices = new unsigned int[indicesCount];
				std::memcpy(indices, faces->buffer.get(), numIndicesBytes);

				Mesh* m = new Mesh();
				m->loadData(Acros::ShaderType::LightBlinnPhong,verts,vertsCount / 3 ,indices,indicesCount ,norms,texCoords);
			}
			
			// type casting to your own native types - Option B
// 			{
// 				std::vector<float3> verts_floats;
// 				std::vector<double3> verts_doubles;
// 				if (vertices->t == tinyply::Type::FLOAT32) { /* as floats ... */ }
// 				if (vertices->t == tinyply::Type::FLOAT64) { /* as doubles ... */ }
// 			}
		}
		catch (const std::exception & e)
		{
			std::cerr << "Caught tinyply exception: " << e.what() << std::endl;
		}

		return nullptr;
	}
}