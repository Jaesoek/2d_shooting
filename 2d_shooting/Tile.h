#pragma once
#include "Object.h"
class Tile : public Object
{
public:
	Tile();
	~Tile();

	virtual void Init() override;
	virtual void EnableUpdate() override;
	virtual void EnableRender() override;

	void DeviceSetTexture(LPDIRECT3DTEXTURE9 pTex);
	void SetSize(float width, float height);
	void SetPosition(float posX, float posY);
	void SetUV(float u, float v, float maxU, float maxV);
};

