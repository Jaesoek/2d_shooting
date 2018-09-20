#include "stdafx.h"
#include "MiniRocket.h"


MiniRocket::MiniRocket()
{
}


MiniRocket::~MiniRocket()
{
}

void MiniRocket::Init()
{
	Rocket::Init();
	trans->SetScaling(0.3f, 0.3f);
	isActive = true;
}

void MiniRocket::EnableUpdate()
{
	angle = 1.0f;
	this->trans->SetRotate(angle);
}
