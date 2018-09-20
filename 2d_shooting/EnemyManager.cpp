#include "stdafx.h"
#include "EnemyManager.h"
#include "Rocket.h"

EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
}

void EnemyManager::Init()
{
	for (int i = 0; i < 2;i++)
	{
		for (int j = 0; j < 2; j++)
		{
			Enemy* newEm = new Enemy;
			newEm->Init(D3DXVECTOR2(100 + i * 100,
				50 + 50 * j));
			enemys.push_back(newEm);
		}
	}
	boss = new BossEnemy();
	boss->Init(D3DXVECTOR2(200, -310));

	stage1 = 0;
}

void EnemyManager::Release()
{
	for (int i = 0; i < enemys.size();i++)
		SAFE_DELETE(enemys[i]);
	SAFE_DELETE(boss);
}

void EnemyManager::Update()
{
	if (!isStageChange)
	{
		for (int i = 0; i < enemys.size();i++)
			enemys[i]->Update();
	}
	else
	{
		boss->Update();
	}
}

void EnemyManager::Render()
{
	if (!isStageChange)
	{
		for (int i = 0; i < enemys.size();i++)
			enemys[i]->Render();
	}
	else
	{
		boss->Render();
	}
	//0x(16Áø¼ö) -> ARGB
	//D3DXCOLOR -> RGBA(1.0f)
}

void EnemyManager::SetPlayerLink(Rocket * pl)
{
	boss->SetPlayerLink(pl);
	for (int i = 0; i < enemys.size();i++)
		enemys[i]->SetPlayerLink(pl);
}
