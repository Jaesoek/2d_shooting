#include "stdafx.h"
#include "MiniMap.h"


MiniMap::MiniMap()
{
	this->isActive = true;
}


MiniMap::~MiniMap()
{
}

void MiniMap::Init()
{
	Object::Init();
	rc->SetCenterSize(300, 300);
	this->CreateVertexBuffer();
	trans->SetWorldPosition(150, 150);
}
