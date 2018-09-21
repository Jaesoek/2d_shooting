#include "stdafx.h"
#include "Scene.h"
#include "Camera.h"

IScene::IScene()
{
	mainCamera = new Camera();
	mainCamera->Init(WINSIZE_X, WINSIZE_Y);
}

IScene::~IScene()
{
}

void IScene::UpdateGUI()
{
	if (Input->GetKey(VK_CONTROL))
	{
		if (Input->GetKeyDown(VK_F10))
			isSystemShow = !isSystemShow;
		if (Input->GetKeyDown(VK_F11))
			isInterfaceShow = !isInterfaceShow;
		if (Input->GetKeyDown(VK_F12))
			isDemoShow = !isDemoShow;
	}

	if(ImGui::BeginMainMenuBar())
	{
		if(ImGui::BeginMenu("View"))
		{
			if (ImGui::MenuItem("System", "Crtl + F10"))
				isSystemShow = !isSystemShow;
			if(ImGui::MenuItem("Interface","Crtl + F11"))
				isInterfaceShow = !isInterfaceShow;
			if (ImGui::MenuItem("Demo", "Crtl + F12"))
				isDemoShow = !isDemoShow;

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	
	if (isInterfaceShow == true)
	{
		ImGui::SetNextWindowPos(ImVec2(WINSIZE_X - 300, 0));
		ImGui::SetNextWindowSize(ImVec2(300, WINSIZE_Y));
		ImGui::Begin("Interface", &isInterfaceShow,
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse
		);
		{
			SetInterface();
		}
		ImGui::End();
	}
	if (isDemoShow)
	{
		ImGui::ShowDemoWindow();
	}
	if (isSystemShow)
	{
		ImGui::Begin("System");
		{
			ImGui::Text("FPS %0.1f", ImGui::GetIO().Framerate);
		}
		ImGui::End();
	}
}
