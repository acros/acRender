#pragma once

#include "Base/AcObject.h"

namespace Acros
{
	class Camera : public AcObject
	{
	public:
		Camera(float aspect, float fov, float nearPlane, float farPlane);
		~Camera();

//		virtual void update(float delta)override;

		void setPersp(float aspect, float fov, float nearPlane, float farPlane);
		void setViewMat(const AcVector& pos, const AcVector& target, const AcVector& up);

		const AcMatrix&	getViewMat();
		const AcMatrix&	getProjMat()const;

		const float getFov()const { return mFov; }

		//TODO: Wrap in Transform
		const AcVector& GetForward()const { return mLookAt; }
		const AcVector& GetRight()const { return mRight; }
		const AcVector& GetUp()const { return mUp; }

	protected:

		float		mNear;
		float		mFar;
		float		mFov;
		float		mAspect;

		AcVector	mLookAt;
		AcVector	mRight;
		AcVector	mUp;

		bool		mViewMatDirty;
		AcMatrix	mViewMat;
		AcMatrix	mProjMat;
	};

}
