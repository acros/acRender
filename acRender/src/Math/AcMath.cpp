#include <string>
#include "AcMath.h"
#include "Base/AcUtils.h"
#include "AcTranform.h"

#define ACROS_PRINT_DEBUG_INFO 0

void AcMathUtils::printLog(const AcMatrix& mat,const std::string& prefix)
{
#if ACROS_PRINT_DEBUG_INFO
	const float* m = glm::value_ptr(mat);
	logMessage("Print matrix,%s",prefix.c_str());
	for (int i=0; i < 16; i +=4)
	{
		logMessage("\n %.2f, %.2f, %.2f,%.2f",m[i],m[i+1],m[i+2],m[i+3]);
	}
	logMessage("\n");
#endif
}

namespace Acros
{
	const AcMatrix AcTransform::MatIdentity = glm::identity<glm::mat4>();
	const AcVector AcTransform::VecOne = AcVector(1);
	const AcVector AcTransform::VecZero = AcVector(0);
	const AcVector AcTransform::VecX = AcVector(1, 0, 0);
	const AcVector AcTransform::VecY = AcVector(0, 1, 0);
	const AcVector AcTransform::VecZ = AcVector(0, 0, 1);

	const AcMatrix& AcTransform::getModelMat()
	{
		if (isModelMatrixDirty)
		{
			modelMatrix = glm::translate(MatIdentity, getTranslation());
			glm::mat4 RotationMatrix = glm::mat4_cast(getRotation());
			modelMatrix *= RotationMatrix;
			modelMatrix = glm::scale(modelMatrix, getScale());
			isModelMatrixDirty = false;
		}

		return modelMatrix;
	}
}
