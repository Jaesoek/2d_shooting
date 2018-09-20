#pragma once
#include "Bullet.h"
#include "Object.h"
class Enemy : public Object
{
protected:
	int hp;

	class Rocket* player;

	bool isDeath = false;
	Missile* bullet[10];
	DWORD preTime;
	DWORD curTime;
	float angle = 0.0f;
public:
	Enemy();
	~Enemy();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual void Move();
	virtual void Attack();

	virtual void EnableUpdate() override;

	void SetPlayerLink(Rocket* pl);
	int GetHP() { return hp; }
	void SetHP(int _hp) { hp = _hp; if (hp < 0) SetActive(false); }

	bool GetDeath() { return isDeath; }
};

