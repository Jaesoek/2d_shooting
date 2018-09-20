#pragma once
#include "BossEnemy.h"
class EnemyManager
{
private:
	vector<Enemy*> enemys;
	int stage1;
	bool isStageChange = false;
	Enemy* boss;
public:
	EnemyManager();
	~EnemyManager();

	void Init();
	void Release();
	void Update();
	void Render();

	void SetPlayerLink(class Rocket* pl);
	vector<Enemy*> GetEnemys() { return enemys; }
	Enemy* GetBoss() { return boss; }
	int GetCount() { return stage1; }
	void SetCount(int count) { 
		stage1 = count; if (count == enemys.size()) isStageChange = true;
	}
};

