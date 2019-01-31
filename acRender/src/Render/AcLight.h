#pragma once

#include "Math/AcMath.h"

namespace Acros{

	enum LightType
	{
		Directional
	};

	//TODO: Inherit from AcObject
	class Light {
	public:
		Light(LightType t,const AcVector& dir,const AcColor3& c)
			: mType(t)
			, mDir(dir)
			, mColor(c)
		{
			mDir = glm::normalize(mDir);
		}

		LightType getType()const { return mType; }
		const AcVector& getDir()const { return mDir; }
		const AcColor3& getColor()const { return mColor; }

		void setDir(const AcVector& dir) { 
			mDir = glm::normalize(dir);
		}
		void setColor(const AcColor3& c) { mColor = c; }

	private:
		LightType	mType;
		AcVector	mDir;
		AcColor3	mColor;
	};
}