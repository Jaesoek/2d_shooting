#include "stdafx.h"
#include "Scene_AstarTest.h"
#include "Camera.h"

Scene_AstarTest::Scene_AstarTest()
{
}


Scene_AstarTest::~Scene_AstarTest()
{
}

void Scene_AstarTest::Init()
{
	aStar = new Scene_AStar;
	aStar->Init();
}

void Scene_AstarTest::Release()
{
	aStar->Release();
	SAFE_DELETE(aStar);
}

void Scene_AstarTest::Update()
{
	aStar->Update();
}

void Scene_AstarTest::Render()
{
	mainCamera->SetDeviceMatrix();
	aStar->Render(mainCamera);
}

void Scene_AstarTest::SetInterface()
{
}
