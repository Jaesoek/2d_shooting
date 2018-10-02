#pragma once
#include "Scene.h"
class Scene_Stage4 : public IScene
{
public:
	Scene_Stage4();
	~Scene_Stage4();

	// IScene을(를) 통해 상속됨
	// 가상함수 
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void SetInterface() override;

private:
	LPD3DXEFFECT pEffect;
	VertexPT vertice[6];
	DWORD indices[6] = { 0,1,2,0,2,3 };

};

