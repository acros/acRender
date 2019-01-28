#pragma once

#include "Render/Renderer.h"
#include "Math.h"


//The basic object
class AcObject {
public:
	AcObject() : mAngleY(0.f),mScale(1,1,1), mMesh(nullptr){}
	virtual ~AcObject();

	const AcMatrix&	getModelMat();
//	const AcMatrix& getViewMat();

	const AcVector&	getPosition()const { return mPos; }
	const AcVector&	getScale()const { return mScale; }
	const AcVector&	getRotation()const { return mRot; }

//	void setLookAt(const AcVector& vec) { mLookAt = vec; }

	void setPosition(const AcVector& pos) { mPos = pos; }
	void setScale(const AcVector& scale) { mScale = scale; }
	void setRotation(const AcVector& rot) { mRot = rot; }

	void rotate(const AcVector& rotAxis, float angle);

	virtual void update(float delta)	{}
	
	void initDraw(Renderer& context);
	virtual void draw(Renderer& context, const AcMatrix& viewMat,const AcMatrix& proj);

	const class Mesh* getMesh()const { return mMesh; }

	//Debug use
	void createShape(ShapeType	shape);

protected:
	AcVector	mPos;
	AcVector	mRot;
	AcVector	mScale;

	AcVector    mLookAt;

	//Temp use
	float		mAngleY;

	AcMatrix	mModelMat;
//	AcMatrix    mViewMat;

	class Mesh* mMesh;
};