#pragma once
#include "Rocket.h"
class MiniRocket : public Rocket
{
private:
	float angle = 0.0f;

public:
	MiniRocket();
	~MiniRocket();

	void Init()override;
	void EnableUpdate() override;
};

