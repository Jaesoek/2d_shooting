#pragma once
#include "IsoTile.h"
#include "Scene.h"
#include "Collider.h"
#include "Camera.h"

#define TILEX 20
#define TILEY 20
#define STARTX 400
#define STARTY 40


class Scene_Stage3 : public IScene
{
private:
	IsoTile * tile;
	D3DXVECTOR2 uv[TILEX][TILEY];
	Collider* cameraCollider;

public:
	Scene_Stage3();
	~Scene_Stage3();

	void Init();
	void Release();
	void Update();
	void Render();

	// IScene��(��) ���� ��ӵ�
	virtual void SetInterface() override;
};

