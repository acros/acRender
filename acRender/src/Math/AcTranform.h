#pragma once

#include "AcMath.h"

struct AcTransform {
	
	AcVector translation;

	AcQuat	rot;
	
	AcVector scale;

	/*
	const static AcTransform Identity
	{
		translation = VecZero,
		rot = QuatIdentity,
		scale = VecIdentity
	};
	*/
};

