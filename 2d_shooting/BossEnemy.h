#pragma once
#include "Enemy.h"
class BossEnemy : public Enemy
{
private:
	float step = 0.0f;
	D3DXVECTOR2 startPos;

	Missile* missile[10];

	float delay = 0.0f;
public:
	BossEnemy();
	~BossEnemy();

	virtual void Init(D3DXVECTOR2 coord) override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Move() override;

};

