#pragma once
#include "Scene.h"
#include "Scene_AStar.h"
class Scene_AstarTest : public IScene
{
private:
	Scene_AStar * aStar;
public:
	Scene_AstarTest();
	~Scene_AstarTest();

	// IScene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void SetInterface() override;
};

