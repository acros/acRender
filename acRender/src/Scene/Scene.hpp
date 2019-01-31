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

class Scene{
public:
	Scene(Renderer&	render);
	virtual ~Scene();

	const string& getVertexStr()const { return mVertStr; }
	const string& getFragmentStr()const { return mFragStr; }

    virtual void enter();
    
    virtual void update(float delta);
    
    virtual void render();
    
    virtual void exit();

#if ACROS_USE_IMGUI
	virtual void renderImgui() {}
	static void	DrawImGui();
#endif 

	static void UpdateScene(Renderer& r);
	static void ClearScene();

	static Scene*	GetScene() { return sShowingScene; }

protected:
    
	//TODO: Refactor  -[Material Params]
	string	mVertStr;
	string	mFragStr;
	GLuint	mShaderProgram;
	GLuint mBaseVAO;
	GLuint mBaseVtxBuffer;
	GLuint mBaseVboIndicesBuffer;

	Renderer&	mRendererRef;

	vector<class AcObject*>	mObjects;

	Acros::Light mDirLight;

private:
	static class Scene*	sShowingScene;
	static int sSceneSelection;
	static int sCurrenSceneIdx;
	const static string SceneList[];
};


#endif /* Scene_hpp */
