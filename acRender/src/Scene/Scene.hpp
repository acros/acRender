//
//  Scene.hpp
//  OpenGL_ES_Lab
//
//  Created by ZhaoZhihui on 16/8/2.
//  Copyright © 2016年 ZhaoZhihui. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "Render/Renderer.h"
#include "Base/AcUtils.h"
#include "Render/AcLight.h"

using namespace std;

namespace Acros
{
	class AcObject;

	class Scene {
		friend class World;

	public:
		Scene();
		virtual ~Scene();

		const string& getVertexStr()const { return mVertStr; }
		const string& getFragmentStr()const { return mFragStr; }

		virtual void enter();
		virtual void update(float delta);
		virtual void exit();

		virtual void initRender(Renderer& r) {}

		virtual void preRender(Renderer& r);
		virtual void render(Renderer& r);
		virtual void postRender(Renderer& r) {}

		virtual void quitRender(Renderer& r) {}


#if ACROS_USE_IMGUI
		virtual void renderImgui() {}
#endif 

	protected:
		static Scene* CreateScene(int index);

		//TODO: Refactor  -[Material Params]
		string	mVertStr;
		string	mFragStr;
		GLuint	mShaderProgram;
		GLuint mBaseVAO;
		GLuint mBaseVtxBuffer;
		GLuint mBaseVboIndicesBuffer;

		vector<AcObject*>	mObjects;

		Acros::Light mDirLight;

	private:
		const static string SceneList[];
		const static int SceneListLen;
	};

}


#endif /* Scene_hpp */
