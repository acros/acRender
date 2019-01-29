#pragma once

#include "Render/Renderer.h"
#include "Base/AcUtils.h"

//The basic object
class AcObject {
public:
	AcObject();
	virtual ~AcObject();

	void setPosition(const AcVector& pos) { mTransform.setTranslation(pos); }
	void setScale(const AcVector& scale) { mTransform.setScale(scale); }
	void setRotation(const AcVector& rot) { mTransform.setRotation(rot); }

	AcTransform& GetTransform() { return mTransform; }
	const AcTransform& GetTransform()const { return mTransform; }

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

	class Mesh* mMesh;
};