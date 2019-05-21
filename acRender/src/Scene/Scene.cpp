//
//  Scene.cpp
//  OpenGL_ES_Lab
//
//  Created by ZhaoZhihui on 16/8/2.
//

#include "Scene.hpp"
#include "Base/AcObject.h"

#include "FboScene.h"
#include "LightScene.h"
#include "ParticleScene.h"
#include "TextureScene.h"
#include "VertexScene.h"
#include "CommonScene.h"

namespace Acros {


	const string Scene::SceneList[] = { "FBO","Light","Particle","Texture","Vertex Obj","Common" };
	const int Scene::SceneListLen = sizeof(Scene::SceneList) / sizeof(Scene::SceneList[0]);

	void Scene::renderImgui()
	{
		static AcVector LDIR(1, -1, 1);
		ImGui::SliderFloat("X", &LDIR.x, -1, 1);
		ImGui::SliderFloat("Y", &LDIR.y, -1, 1);
		ImGui::SliderFloat("Z", &LDIR.z, -1, 1);
		mDirLight.setDir(LDIR);

		static float color[3]{ 1,1,1 };
		ImGui::ColorEdit3("Light Color", color);
		mDirLight.setColor(AcColor3(color[0], color[1], color[2]));
	}

	Scene* Scene::CreateScene(int index)
	{
		Scene* newScene = nullptr;
		switch (index + 1)
		{
		case 1:
			newScene = new FboScene();
			break;
		case 2:
			newScene = new LightScene();
			break;
		case 3:
			newScene = new ParticleScene();
			break;
		case 4:
			newScene = new TextureScene();
			break;
		case 5:
			newScene = new VertexScene();
			break;
		case 6: 
			newScene = new CommonScene();
			break;
		default:
			assert(false);
			break;
		}

		return newScene;
	}

	Scene::Scene()
		: mShaderProgram(0)
		, mBaseVAO(0)
		, mBaseVtxBuffer(0)
		, mBaseVboIndicesBuffer(0)
		, mDirLight(Acros::Directional, AcVector(1, -1, 1), AcColor3(0.5f, 0.5f, 0.5f))
	{

	}

	Scene::~Scene()
	{
		if (mShaderProgram != 0)
		{
			glDeleteProgram(mShaderProgram);
		}
	}

	void Scene::enter()
	{
	
	}

	void Scene::update(float delta)
	{
		for (size_t i=0; i < mObjects.size(); ++i)
		{
			mObjects[i]->update(delta);
		}
	}

	void Scene::preRender(Renderer & r)
	{
		if (!getVertexStr().empty() && !getFragmentStr().empty())
			mShaderProgram = r.loadShaderProgram(getVertexStr().c_str(), getFragmentStr().c_str());
	}

	void Scene::render(Renderer& r)
	{
	// 	for (int i=0; i < mObjects.size(); ++i)
	// 	{
	// 		mObjects[i]->draw(mRendererRef, mCam, &mDirLight);
	// 	}
	}

	void Scene::exit()
	{
		for (size_t i=0; i < mObjects.size(); ++i)
		{
			SAFE_DELETE(mObjects[i]);
		}

		mObjects.clear();

		if(mBaseVAO != 0)
			glDeleteVertexArrays(1, &mBaseVAO);
		if(mBaseVtxBuffer != 0)
			glDeleteBuffers(1, &mBaseVtxBuffer);
		if(mBaseVboIndicesBuffer != 0)
			glDeleteBuffers(1, &mBaseVboIndicesBuffer);

	}
}
