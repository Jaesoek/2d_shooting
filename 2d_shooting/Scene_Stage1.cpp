#include "stdafx.h"
#include "Scene_Stage1.h"


Scene_Stage1::Scene_Stage1()
{
}


Scene_Stage1::~Scene_Stage1()
{
}

void Scene_Stage1::Init()
{
	ver2 = new Rocket;
	ver2->Init();

	enemy = new Enemy;
	enemy->Init();


	mini = new MiniRocket;
	mini->Init();

	mini->SetEnemyLink(enemy);
	enemy->SetPlayerLink(ver2);
	ver2->SetEnemyLink(enemy);

}

void Scene_Stage1::Release()
{
	ver2->Release();
	SAFE_DELETE(ver2);

	enemy->Release();
	SAFE_DELETE(enemy);

	mini->Release();
	SAFE_DELETE(mini);
}

void Scene_Stage1::Update()
{
	ver2->Update();
	enemy->Update();
	mini->Update();
	mini->GetTrans()->SetWorldPosition(50, 0);
	mini->GetTrans()->MulMatrix(ver2->GetTrans());
}

void Scene_Stage1::Render()
{
	ver2->Render();
	enemy->Render();
	mini->Render();
}

void Scene_Stage1::SetInterface()
{
	ver2->TransformGui();
}
