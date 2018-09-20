#include "stdafx.h"
#include "Bullet.h"


//init에서 
Bullet::Bullet()
{

}

Bullet::~Bullet()
{
	this->Release();
}

void Bullet::Init()
{
	Object::Init();
	D3DXCreateTextureFromFile
	(
		DEVICE, "Images/eplasma2.tga", &pTex
	);
	fire = false;
	speed = 10;
	
}

void Bullet::Release()
{
	Object::Release();
}

void Bullet::Update()
{
	MoveBullet();
	collider->SetAABBBox(*rc, trans->GetWorld());
}

void Bullet::SetDamage(Collider * target, int * hp)
{

	if (Intersect::IsCrossLineOBB(
		collider->GetOBBBox(),
		target->GetOBBBox()
	) && this->fire == true)
	{
		*hp -= 10;
		this->fire = false;
	}
}

void Bullet::MoveBullet()
{
	if (!fire) return;

 	trans->MovePositionLocal(0, speed);
}

void Bullet::Fire(D3DXVECTOR3 pos, float angle)
{
	trans->SetWorldPosition(pos.x, pos.y);
	this->StartPos = pos;
	trans->SetRotate(angle);
	this->fire = true;
}

void Bullet::Render()
{
	if (!fire) return;
	Object::Render();
}

void Missile::Init(int width, int height)
{
	Bullet::Init();
	rc->SetCenterSize(width, height);
	//rc크기를 변경시키면 다시 버퍼 생성 
	this->CreateVertexBuffer();
}

