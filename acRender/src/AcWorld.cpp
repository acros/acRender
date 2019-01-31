#include "AcWorld.h"
#include "Scene/Scene.hpp"

namespace Acros
{
	World::World()
		: mRunningScene(nullptr)
		, mSceneSelection(1)
		, mCurrenSceneIdx(-1)
	{
		mRenderer.checkRendererVersion();
	}

	void World::setViewSize(int x, int y)
	{
		mRenderer.setViewport(x, y);
	}


	void World::update(float deltaTime)
	{
		if (mSceneSelection != mCurrenSceneIdx)
		{
			quitScene();

			mCurrenSceneIdx = mSceneSelection;
			mRunningScene = Scene::CreateScene(mCurrenSceneIdx);
			if (mRunningScene != nullptr)
			{
				mRunningScene->enter();
				mRunningScene->initRender(mRenderer);
			}
		}

		if(mRunningScene != nullptr)
			mRunningScene->update(deltaTime);
	}

	void World::quitScene()
	{
		if (mRunningScene != nullptr)
		{
			mCurrenSceneIdx = -1;

			mRunningScene->quitRender(mRenderer);
			mRunningScene->exit();

			SAFE_DELETE(mRunningScene);
		}
	}

	void World::render()
	{
		if (mRunningScene != nullptr)
		{
			mRunningScene->preRender(mRenderer);
			mRunningScene->render(mRenderer);
			mRunningScene->postRender(mRenderer);
		}
	}

#if ACROS_USE_IMGUI
	void World::drawImGui()
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;

		ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(550, 280), ImGuiCond_FirstUseEver);

		if (!ImGui::Begin("Option", NULL, window_flags))
		{
			ImGui::End();
			return;
		}

		ImGui::PushItemWidth(ImGui::GetFontSize() * -12);           // Use fixed width for labels (by passing a negative value), the rest goes to widgets. We choose a width proportional to our font size.
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Menu"))
			{
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::RadioButton(Scene::SceneList[0].c_str(), &mSceneSelection, 0); ImGui::SameLine();
		ImGui::RadioButton(Scene::SceneList[1].c_str(), &mSceneSelection, 1); ImGui::SameLine();
		ImGui::RadioButton(Scene::SceneList[2].c_str(), &mSceneSelection, 2); ImGui::SameLine();
		ImGui::RadioButton(Scene::SceneList[3].c_str(), &mSceneSelection, 3);
		ImGui::RadioButton(Scene::SceneList[4].c_str(), &mSceneSelection, 4); ImGui::SameLine();
		ImGui::RadioButton(Scene::SceneList[5].c_str(), &mSceneSelection, 5); ImGui::SameLine();
		ImGui::RadioButton(Scene::SceneList[6].c_str(), &mSceneSelection, 6); //ImGui::SameLine();

		if (mRunningScene != nullptr)
		{
			mRunningScene->renderImgui();
		}

		ImGui::End();
	}

	void World::quit()
	{
		quitScene();
	}
#endif 
}


