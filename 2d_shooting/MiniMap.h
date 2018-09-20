#pragma once
#include "Object.h"
class MiniMap : public Object
{
public:
	MiniMap();
	~MiniMap();
	void Init() override;
	virtual void EnableUpdate() override{}
};

