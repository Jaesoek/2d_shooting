#pragma once
#include "Scene.h"
#include "Rocket.h"
#include "Enemy.h"
#include "MiniRocket.h"
class Scene_Stage1 : public IScene
{
private:
	Rocket * ver2;
	Enemy* enemy;
	MiniRocket* mini;
public:
	Scene_Stage1();
	~Scene_Stage1();

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	void SetInterface() override;
};

