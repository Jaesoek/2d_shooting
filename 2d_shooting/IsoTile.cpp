#include "stdafx.h"
#include "IsoTile.h"


IsoTile::IsoTile()
{
}


IsoTile::~IsoTile()
{
}

// 400���� update ������ ���ϰ� ���ؼ�
// 1���� ������ 400���� ������ ���ڴ�
void IsoTile::Init()
{
	Tile::Init();
	rc->position[0] = D3DXVECTOR4(50, 50, 0, 1.0f);
	rc->position[1] = D3DXVECTOR4(0, 25, 0, 1.0f);
	rc->position[2] = D3DXVECTOR4(50, 0, 0, 1.0f);
	rc->position[3] = D3DXVECTOR4(100, 25, 0, 1.0f);

	this->isActive = true;
	
}

