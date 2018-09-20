#include "stdafx.h"
#include "IsoTile.h"


IsoTile::IsoTile()
{
}


IsoTile::~IsoTile()
{
}

// 400개를 update 돌리면 부하가 심해서
// 1개를 가지고 400번을 나눠서 쓰겠다
void IsoTile::Init()
{
	Tile::Init();
	rc->position[0] = D3DXVECTOR4(50, 50, 0, 1.0f);
	rc->position[1] = D3DXVECTOR4(0, 25, 0, 1.0f);
	rc->position[2] = D3DXVECTOR4(50, 0, 0, 1.0f);
	rc->position[3] = D3DXVECTOR4(100, 25, 0, 1.0f);

	this->isActive = true;
	
}

