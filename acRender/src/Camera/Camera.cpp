#include "Camera.h"

Camera::Camera(float aspect, float fov, float nearPlane, float farPlane)
	: mAspect(aspect)
	, mFov(fov)
	, mNear(nearPlane)
	, mFar(farPlane)
	, mLookAt(0.f,0.f,0.f)
	, mUp (0.0f, 1.0f, 0.0f)
	, mViewMatDirty(false)
{
	mProjMat = glm::perspective(mFov, mAspect, mNear, mFar);
}

Camera::~Camera()
{

}

void Camera::update(float delta)
{
	//TODO: Do sth to control the camera

}

void Camera::setPersp(float aspect, float fov, float nearPlane, float farPlane)
{
	mAspect = aspect;
	mFov = fov;
	mNear = nearPlane;
	mFar = farPlane;

	mProjMat = glm::perspective(glm::radians(mFov), mAspect, mNear, mFar);
}

void Camera::setViewMat(const AcVector& pos, const AcVector& target, const AcVector& up)
{
	mTransform.translation = pos;
	mLookAt = target;
	mUp = up;
	mViewMat = glm::lookAt(mTransform.translation, mLookAt, mUp);
}

const AcMatrix& Camera::getViewMat()
{
	mViewMat = glm::lookAt(mTransform.translation, mLookAt, mUp);
	return mViewMat;
}

const AcMatrix& Camera::getProjMat() const
{
	return mProjMat;
}
