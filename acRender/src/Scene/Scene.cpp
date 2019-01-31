//
//  Scene.cpp
//  OpenGL_ES_Lab
//
//  Created by ZhaoZhihui on 16/8/2.
//  Copyright © 2016年 ZhaoZhihui. All rights reserved.
//

#include "Scene.hpp"
#include "Base/AcObject.h"

#include "SimpleTriangle.h"
#include "FboScene.h"
#include "LightScene.h"
#include "ParticleScene.h"
#include "TextureScene.h"
#include "TriangleScene.h"
#include "VertexScene.h"

namespace Acros {

	const string Scene::SceneList[] = { "Simple Triangle","FBO","Light","Particle","Texture","Triangle","Vertex Obj" };


	Scene* Scene::CreateScene(int index)
	{
		Scene* newScene = nullptr;
		switch (index)
		{
		case 0:
			newScene = new SimpleTriangle();
			break;
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
			newScene = new TriangleScene();
			break;
		case 6:
			newScene = new VertexScene();
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
		for (int i=0; i < mObjects.size(); ++i)
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
		for (int i=0; i < mObjects.size(); ++i)
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
