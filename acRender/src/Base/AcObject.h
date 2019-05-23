#pragma once

#include "Render/Renderer.h"
#include "Base/AcUtils.h"
#include "Render/Mesh.h"
#include <vector>

namespace Acros
{
	enum ShaderType;

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

		virtual void update(float delta);
	
		void initDraw(Renderer& context);
		virtual void draw(Renderer& context, class Camera* cam,class Light* l = nullptr);

		const class Mesh* getMesh()const { return mMesh; }

		//Debug use
		void createShape(ShapeType	shape);
		void createShape(ShapeType	shape,ShaderType shader);

		void loadMesh(const string& fileName,ShaderType shader);

		void setMoveable();

	#if ACROS_USE_IMGUI
		virtual void drawImgui();
	#endif

	protected:

		AcTransform mTransform;

		vector<class BaseComponent*> mComps;

		class Mesh* mMesh;
	};

}
