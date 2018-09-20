#pragma once
#include "Tile.h"
class IsoTile : public Tile
{
public:
	IsoTile();
	~IsoTile();

	virtual void Init() override;
};

