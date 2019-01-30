#pragma once

#include "Math/AcMath.h"

namespace Acros{

	enum LightType
	{
		Directional
	};

	class Light {
	public:
		Light(LightType t,const AcVector& dir,const AcColor3& c)
			: mType(t)
			, mDir(dir)
			, mColor(c)
		{
			glm::normalize(mDir);
		}

		LightType getType()const { return mType; }
		const AcVector& getDir()const { return mDir; }
		const AcColor3& getColor()const { return mColor; }

		void setDir(const AcVector& dir) { 
			glm::normalize(mDir);
			mDir = dir; 
		}
		void setColor(const AcColor3& c) { mColor = c; }

	private:
		LightType	mType;
		AcVector	mDir;
		AcColor3	mColor;
	};
}