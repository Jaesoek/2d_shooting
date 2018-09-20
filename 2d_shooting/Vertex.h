#pragma once

static struct VertexP
{
	D3DXVECTOR3 position;

	static DWORD FVF;
};

static struct VertexPT 
{
	D3DXVECTOR4 position;
	D3DXVECTOR2 uv;
	static const DWORD FVF;
};

static struct VertexPC
{
	D3DXVECTOR4 position;
	D3DXCOLOR color;
	static const DWORD FVF;

	VertexPC()
	{
		position = D3DXVECTOR4(0, 0, 0, 1);
		color = D3DXCOLOR(1, 1, 1, 1);
	}
	VertexPC(D3DXVECTOR2 vec, D3DXCOLOR color)
	{
		position = D3DXVECTOR4(vec.x,vec.y, 0, 1);
		this->color = color;
	}
};
