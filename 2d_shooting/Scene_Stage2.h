#pragma once
#include "Scene.h"
#include "Tile.h"
class Scene_Stage2 :public IScene
{
private:
	Tile * tile;
	Tile * obj;
	int tileX, tileY;
	float width, height;
	float prevWidth, prevHeight;
	bool result = false;

	LPDIRECT3DTEXTURE9 pSelectTex;
	char filePath[256];

	D3DXVECTOR2 uv{ 0, 0 };
	D3DXVECTOR2 maxUV{ 32.0f, 32.0f };

	// pair의 first 는 지형 UV, second는 obj UV
	vector<vector<
		pair<D3DXVECTOR2, D3DXVECTOR2>>> UVs;

	bool isDraw = false;
	bool isObj = false;

	HANDLE file;

public:
	Scene_Stage2();
	~Scene_Stage2();

	void Init() override;
	void Release()override;
	void Update()override;
	void Render()override;

	void SetInterface() override;
};

