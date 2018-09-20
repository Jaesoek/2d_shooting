#pragma once

//fileName Rect

struct Rect : public tagRECT
{
public:
	D3DXVECTOR4 position[4];
	UINT index[6];
public:
	Rect();
	Rect(int x, int y, int width, int height);
	~Rect() {};

	void SetCenterSize(int width, int height);
	void UpdateVector();
	void UpdateRect();
};
