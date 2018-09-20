#include "stdafx.h"
#include "Rect.h"

Rect::Rect()
{
	this->left = 0;
	this->right = 0;
	this->top = 0;
	this->bottom = 0;
	for (int i = 0; i < 4; i++)
	{
		position[i] = D3DXVECTOR4(0, 0, 0,1.0f);
	}
	index[0] = 0;
	index[1] = 1;
	index[2] = 2;

	index[3] = 0;
	index[4] = 2;
	index[5] = 3;
}

Rect::Rect(int x, int y, int width, int height)
{
	this->left = x - width / 2;
	this->right = x + width / 2;
	this->top = y - height / 2;
	this->bottom = y + height / 2;

	position[0] = D3DXVECTOR4(left, bottom, 0,1.0f);
	position[1] = D3DXVECTOR4(left, top, 0,  1.0f);
	position[2] = D3DXVECTOR4(right, top, 0, 1.0f);
	position[3] = D3DXVECTOR4(right, bottom, 0, 1.0f);

	index[0] = 0;
	index[1] = 1;
	index[2] = 2;

	index[3] = 0;
	index[4] = 2;
	index[5] = 3;
}

void Rect::SetCenterSize(int width, int height)
{
	POINT center;
	center.x = (this->right + this->left) / 2;
	center.y = (this->bottom + this->top) / 2;

	this->left = center.x - width / 2;
	this->right = center.x + width / 2;
	this->top = center.y - height / 2;
	this->bottom = center.y + height / 2;

	this->UpdateVector();
}

void Rect::UpdateVector()
{
	position[0] = D3DXVECTOR4(left, bottom, 0, 1.0f);
	position[1] = D3DXVECTOR4(left, top, 0, 1.0f);
	position[2] = D3DXVECTOR4(right, top, 0, 1.0f);
	position[3] = D3DXVECTOR4(right, bottom, 0, 1.0f);
}

void Rect::UpdateRect()
{
	this->left   = position[0].x;
	this->top    = position[1].y;
	this->right  = position[2].x;
	this->bottom = position[3].y;
}
