//
//  Scene.cpp
//  OpenGL_ES_Lab
//
//  Created by ZhaoZhihui on 16/8/2.
//  Copyright © 2016年 ZhaoZhihui. All rights reserved.
//

#include "Scene.hpp"

#include "SimpleTriangle.h"
#include "FboScene.h"
#include "LightScene.h"
#include "ParticleScene.h"
#include "TextureScene.h"
#include "TriangleScene.h"
#include "VertexScene.h"

const string Scene::SceneList[] = { "Simple Triangle","FBO","Light","Particle","Texture","Triangle","Vertex Obj" };
Scene*	Scene::sShowingScene = NULL;
int	Scene::sSceneSelection = 0;
int Scene::sCurrenSceneIdx = -1;

#if ACROS_USE_IMGUI
void Scene::DrawImGui()
{
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(550, 280), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Option", NULL, window_flags))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}

//	ImGui::Text("Current scene: %s","***");
	ImGui::PushItemWidth(ImGui::GetFontSize() * -12);           // Use fixed width for labels (by passing a negative value), the rest goes to widgets. We choose a width proportional to our font size.
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Menu"))
		{
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	ImGui::RadioButton(SceneList[0].c_str(), &sSceneSelection, 0); ImGui::SameLine();
	ImGui::RadioButton(SceneList[1].c_str(), &sSceneSelection, 1); ImGui::SameLine();
	ImGui::RadioButton(SceneList[2].c_str(), &sSceneSelection, 2); ImGui::SameLine();
	ImGui::RadioButton(SceneList[3].c_str(), &sSceneSelection, 3);
	ImGui::RadioButton(SceneList[4].c_str(), &sSceneSelection, 4); ImGui::SameLine();
	ImGui::RadioButton(SceneList[5].c_str(), &sSceneSelection, 5); ImGui::SameLine();
	ImGui::RadioButton(SceneList[6].c_str(), &sSceneSelection, 6); //ImGui::SameLine();

	if (sShowingScene != nullptr)
	{
		sShowingScene->renderImgui();
	}

	ImGui::End();
}
#endif

void Scene::UpdateScene(Renderer& render)
{
	if (sSceneSelection == sCurrenSceneIdx)
		return;

	ClearScene();

	sCurrenSceneIdx = sSceneSelection;
	//"Vertex", "FBO", "Light", "Particle", "Texture", "Triangle"
	switch (sSceneSelection)
	{
	case 0:
		sShowingScene = new SimpleTriangle(render);
		break;
	case 1:
		sShowingScene = new FboScene(render);
		break;
	case 2:
		sShowingScene = new LightScene(render);
		break;
	case 3:
		sShowingScene = new ParticleScene(render);
		break;
	case 4:
		sShowingScene = new TextureScene(render);
		break;
	case 5:
		sShowingScene = new TriangleScene(render);
		break;
	case 6:
		sShowingScene = new VertexScene(render);
		break;
	default:
		assert(false);
		break;
	}
	
	if (sShowingScene != nullptr)
		sShowingScene->enter();
}

void Scene::ClearScene()
{
	if (sShowingScene != nullptr)
	{
		sCurrenSceneIdx = -1;
		sShowingScene->exit();
		delete sShowingScene;
		sShowingScene = nullptr;
	}
}

Scene::Scene(Renderer& render)
	: mRendererRef(render)
	, mShaderProgram(0)
	, mBaseVAO(0)
	, mBaseVtxBuffer(0)
	, mBaseColorBuffer(0)
	, mBaseVboIndicesBuffer(0)
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
	if(!getVertexStr().empty() && !getFragmentStr().empty())
		mShaderProgram = mRendererRef.loadShaderProgram(getVertexStr().c_str(), getFragmentStr().c_str());
}

void Scene::update(float delta)
{
    
}

void Scene::render()
{
    
}

void Scene::exit()
{
    if(mBaseVAO != 0)
		glDeleteVertexArrays(1, &mBaseVAO);
	if(mBaseVtxBuffer != 0)
		glDeleteBuffers(1, &mBaseVtxBuffer);
	if(mBaseColorBuffer != 0)
		glDeleteBuffers(1, &mBaseColorBuffer);
	if(mBaseVboIndicesBuffer != 0)
		glDeleteBuffers(1, &mBaseVboIndicesBuffer);

}
