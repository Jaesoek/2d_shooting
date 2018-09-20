#pragma once
#include "Bullet.h"
class Rocket : public Object
{
private:
	Missile* bullet[10];
	//class EnemyManager* enemys;
	class Enemy* enemy;
public:
	Rocket();
	~Rocket();

	void Init() override;
	void Release() override; //�Ѿ��� ���� �Ҷ�  
	void Update() override;
	void Render() override;
	//void SetEnemyLink(EnemyManager* em) { enemys = em; };
	void SetEnemyLink(Enemy* em) { enemy = em; };

};

