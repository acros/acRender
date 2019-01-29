#pragma once

#include "AcMath.h"

class AcTransform {
	
public:
	const static AcMatrix MatIdentity;
	const static AcVector VecOne;
	const static AcVector VecZero;
	const static AcVector VecX;
	const static AcVector VecY;
	const static AcVector VecZ;

public:
	AcTransform()
		: rot(glm::identity<glm::quat>())
		, scale(1, 1, 1)
		, translation(0)
		, isModelMatrixDirty(true)
	{}

	inline void setTranslation(const AcVector& pos) {
		this->translation = pos; isModelMatrixDirty = true;
	}

	inline void setScale(const AcVector& scale) { 
		this->scale = scale; isModelMatrixDirty = true;
	}

	inline void setRotation(const AcQuat& rot) { 
		this->rot = rot; isModelMatrixDirty = true;
	}

	inline void setEulerRotation(const AcVector& e)
	{
		isModelMatrixDirty = true;
		/*
		AcQuat QuatAroundX = AcQuat(r.x, AcVector(1.0, 0.0, 0.0));
		AcQuat QuatAroundY = AcQuat(r.y, AcVector(0.0, 1.0, 0.0));
		AcQuat QuatAroundZ = AcQuat(r.z, AcVector(0.0, 0.0, 1.0));
		this->rot = QuatAroundX * QuatAroundY * QuatAroundZ;
		*/
		AcVector r(glm::radians(e[0]), glm::radians(e[1]), glm::radians(e[2]));
		float qx = sin(r[2] / 2) * cos(r[1] / 2) * cos(r[0] / 2) - cos(r[2] / 2) * sin(r[1] / 2) * sin(r[0] / 2);
		float qy = cos(r[2] / 2) * sin(r[1] / 2) * cos(r[0] / 2) + sin(r[2] / 2) * cos(r[1] / 2) * sin(r[0] / 2);
		float qz = cos(r[2] / 2) * cos(r[1] / 2) * sin(r[0] / 2) - sin(r[2] / 2) * sin(r[1] / 2) * cos(r[0] / 2);
		float qw = cos(r[2] / 2) * cos(r[1] / 2) * cos(r[0] / 2) + sin(r[2] / 2) * sin(r[1] / 2) * sin(r[0] / 2);
		this->rot = AcQuat(qw, qx, qy, qz);
	}

	const AcVector&	getTranslation()const { return this->translation; }
	const AcVector&	getScale()const { return this->scale; }
	const AcQuat&	getRotation()const { return this->rot; }

	const AcMatrix&	getModelMat();

protected:
	AcVector translation;

	AcQuat	rot;

	AcVector scale;

	bool isModelMatrixDirty;
	AcMatrix modelMatrix;
};



