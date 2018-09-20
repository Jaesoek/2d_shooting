#include "stdafx.h"
#include "Rocket.h"
#include "Enemy.h"

Rocket::Rocket()
{
	this->Init();
}


Rocket::~Rocket()
{
	this->Release();
}

void Rocket::Init()
{
	Object::Init();
	D3DXCreateTextureFromFile(
		DEVICE, "Images/SplitHorizon.tga", &pTex
	);
	for (int i = 0; i < 10;i++)
	{
		bullet[i] = new Missile;
		bullet[i]->Init(15,15);
		bullet[i]->SetActive(true);
	}
	this->SetActive(true);

	D3DXMATRIX matRot;
	D3DXMatrixRotationZ(&matRot, D3DXToRadian(-90));
	for (int i = 0; i < 4;i++)
		D3DXVec4Transform(&rc->position[i], &rc->position[i], &matRot);
	this->CreateVertexBuffer();
}

void Rocket::Release()
{
	Object::Release();
	for (int i = 0; i < 10;i++)
		SAFE_DELETE(bullet[i]);
}

void Rocket::Update()
{
	Object::Update();
	if (keybord::Get()->GetKeyDown(VK_SPACE))
	{
		for (int i = 0; i < 10;i++)
		{
			if (bullet[i]->GetBool()) continue;
			bullet[i]->Fire(
				trans->GetPosition()
				, trans->GetAngle());
			break;
		}
	}

	for (int i = 0; i < 10;i++)
		bullet[i]->Update();

	for (int i = 0; i < 10; i++)
	{
		int enemyHp = enemy->GetHP();
		bullet[i]->SetDamage(enemy->Getcollider(), &enemyHp);
		enemy->SetHP(enemyHp);
	}
	//if (this->isActive)
	// 
	//	if (keybord::Get()->GetKeyDown(VK_RETURN))
	//	{
	//		this->SetActive(false);
	//	}
	//}
}

void Rocket::Render()
{
	Object::Render();
	for (int i = 0; i < 10;i++)
		bullet[i]->Render();
}
