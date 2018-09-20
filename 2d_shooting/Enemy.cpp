#include "stdafx.h"
#include "Enemy.h"
#include "Rocket.h"

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::Init()
{
	Object::Init();
	D3DXCreateTextureFromFile(
		DEVICE, "Images/enemy.png", &pTex
	);
	this->SetActive(true);

	for (int i = 0; i < 10; i++)
	{
		bullet[i] = new Missile();
		bullet[i]->Init(15,15);
		bullet[i]->SetActive(true);
	}
	hp = 100;
	preTime = GetTickCount();

	D3DXMATRIX matRot;
	D3DXMatrixRotationZ(&matRot, D3DXToRadian(180));
	for (int i = 0; i < 4;i++)
		D3DXVec4Transform(&rc->position[i], &rc->position[i], &matRot);
	this->CreateVertexBuffer();
}

void Enemy::Release()
{
	Object::Release();
}

void Enemy::Update()
{
	Object::Update();
}

void Enemy::Render()
{
	Object::Render();
	for (int i = 0; i < 10; i++)
		bullet[i]->Render();
	//wsprintf(str, "HP : %d / 100", hp);
	//Font::Get()->PrintText(str, coord.x, coord.y - 20, 0xFFFFFFFF);
	//if (isDeath) return;

	//D3DXVECTOR3 position = trans->GetPosition();

	//IMAGE->Render("back", position.x, position.y - 20, 100, 20);
	//IMAGE->Render("front", position.x, position.y - 20, hp, 20);
}

void Enemy::Move()
{
	if (isDeath) return;
	
	D3DXVECTOR3 to = player->GetTrans()->GetPosition();
	D3DXVECTOR3 from = trans->GetPosition();
	float length = D3DXVec3Length(&(to - from));


	if (length > 400) return; //탐지범위를 벗어날경우 

	trans->LookAtPosition(to);
	POINT p1 = { (LONG)to.x,(LONG)to.y };
	POINT p2 = { (LONG)from.x,(LONG)from.y };

	angle = Intersect::GetAngle(p1, p2);
	//trans->MovePositionLocal(0,-3);
	if (length > 200) return; //공격 범위

	Attack();
}

void Enemy::Attack()
{
	curTime = GetTickCount();

	if (curTime - preTime > 500)
	{
		for (int i = 0; i < 10;i++)
		{
			if (bullet[i]->GetBool()) continue;
			bullet[i]->Fire(
				trans->GetPosition(),
				angle
			);
			break;
		}
		preTime = GetTickCount();
	}
}

void Enemy::EnableUpdate()
{
	Move();
	for (int i = 0; i < 10; i++)
		bullet[i]->MoveBullet();
	collider->SetAABBBox(*rc, trans->GetWorld());
}

void Enemy::SetPlayerLink(Rocket * pl)
{
	player = pl;
}
