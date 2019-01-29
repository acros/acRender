#pragma once

#include "Math/AcMath.h"

namespace Acros{

	enum LightType
	{
		Directional
	};

	class Light {
	public:
		Light(LightType t,const AcVector& dir,const AcColor4& c)
			: mType(t)
			, mDir(dir)
			, mColor(c)
		{}

		LightType getType()const { return mType; }
		const AcVector& getDir()const { return mDir; }
		const AcColor4& getColor()const { return mColor; }

	private:
		LightType	mType;
		AcVector	mDir;
		AcColor4	mColor;
	};
}