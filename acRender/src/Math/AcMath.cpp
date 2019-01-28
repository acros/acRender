#include "AcMath.h"
#include "Base/AcUtils.h"
#include "string"

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
