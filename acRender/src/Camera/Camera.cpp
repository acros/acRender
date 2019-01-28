#include "Camera.h"

Camera::Camera(float aspect, float fov, float nearPlane, float farPlane)
	: mAspect(aspect)
	, mFov(fov)
	, mNear(nearPlane)
	, mFar(farPlane)
	, mLookAt(0.f,0.f,0.f)
	, mUp (0.0f, 1.0f, 0.0f)
{

	mProjMat = glm::perspective(mFov, mAspect, mNear, mFar);
	mViewMat = glm::lookAt(mLookAt, mPos, glm::vec3(0, 1, 0));
}

Camera::~Camera()
{

}

void Camera::update(float delta)
{
	//TODO: Do sth to control the camera

}

const AcMatrix& Camera::getViewMat()
{
	mProjMat = glm::perspective(mFov, mAspect, mNear, mFar);
	mViewMat = glm::lookAt(mLookAt, mPos, glm::vec3(0, 1, 0));

	return mViewMat;
}

const AcMatrix& Camera::getProjMat() const
{
	return mProjMat;
}
