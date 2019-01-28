#pragma once

#include "Render/Renderer.h"
#include "Math/AcTranform.h"
#include "Base/AcUtils.h"

//The basic object
class AcObject {
public:
	AcObject();
	virtual ~AcObject();

	const AcMatrix&	getModelMat();

	const AcVector&	getPosition()const { return mTransform.translation; }
	const AcVector&	getScale()const { return mTransform.scale; }
	const AcQuat&	getRotation()const { return mTransform.rot; }

	void setPosition(const AcVector& pos) { mTransform.translation = pos; }
	void setScale(const AcVector& scale) { mTransform.scale = scale; }
	void setRotation(const AcVector& rot) { mTransform.rot = rot; }

	void rotate(const AcVector& rotAxis, float angle);

	virtual void update(float delta)	{}
	
	void initDraw(Renderer& context);
	virtual void draw(Renderer& context, const AcMatrix& viewMat,const AcMatrix& proj);

	const class Mesh* getMesh()const { return mMesh; }

	//Debug use
	void createShape(ShapeType	shape);

#if ACROS_USE_IMGUI
	virtual void drawImgui();
#endif

protected:

	AcTransform mTransform;

	AcMatrix	mModelMat;

	class Mesh* mMesh;
};