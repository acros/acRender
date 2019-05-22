#pragma once

#include "utils.h"

#define ACROS_USE_GLM_MATH 1

#if ACROS_USE_GLM_MATH

#include "glm\glm.hpp"  // Core GLM stuff, same as GLSL math.
#include "glm\ext.hpp"	// GLM extensions.

typedef glm::mat4 AcMatrix;
typedef glm::vec2 AcVector2;
typedef glm::vec3 AcVector;
typedef glm::vec3 AcColor3;
typedef glm::vec4 AcVector4;
typedef glm::vec4 AcColor4;
typedef glm::quat AcQuat;

// AcMatrix MatIdentiy = glm::identity<glm::mat4>();
// AcQuat QuatIdentity = glm::identity<glm::quat>();
// AcVector VecIdentity = glm::identity<glm::vec3>();
// AcVector VecZero = glm::vec3(0.f);

typedef GLint AcInt;
typedef GLuint AcUint;
typedef GLenum AcEnum;

#endif

class AcMathUtils 
{
public:
	static AcMatrix lookAt(const AcVector& eye, const AcVector& center, const AcVector& up)
	{
		return glm::lookAt(eye, center, up);
	}

	static void AcMathUtils::printLog(const AcMatrix& mat, const std::string& prefix);

};
