#include "stdafx.h"
#include "BossEnemy.h"
#include "Rocket.h"

BossEnemy::BossEnemy()
{
}


BossEnemy::~BossEnemy()
{
}

void BossEnemy::Init(D3DXVECTOR2 coord)
{
	Enemy::Init(coord);
	this->hp = 1000;
	this->startPos = coord;
	for (int i = 0; i < 10; i++)
	{
		missile[i] = new Missile;
	}
}

void BossEnemy::Update()
{
	Move();

	for (int i = 0; i < 10;i++)
		bullet[i]->MoveBullet();
}

void BossEnemy::Render()
{
	for (int i = 0; i < 10; i++)
		bullet[i]->Render();

	image->Render(coord.x, coord.y, 600, 300);
}

void BossEnemy::Move()
{
	if (step <= 1.0f)
	{
		D3DXVECTOR2 endPos(coord.x,60);

		D3DXVec2Lerp(&coord, &startPos, &endPos, step);
		step += 0.005f;
	}
	else
	{
		velocity = player->GetCoord() - coord;
		D3DXVec2Normalize(&velocity, &velocity);
		Attack();

		if (hp < 500)
		{
			delay += 0.05f;
			if (delay > 0.5f)
			{
				delay -= 0.5f;
				for (int i = 0; i < 10;i++)
				{
					//missile[i] = new Missile()
				}
			}
		}
	}
}
