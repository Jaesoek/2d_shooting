#include "stdafx.h"
#include "Tile.h"


Tile::Tile()
{
}


Tile::~Tile()
{
}

void Tile::Init()
{
	Object::Init();
	rc->SetCenterSize(30, 30);
	trans->SetWorldPosition(300, 300);
	this->CreateVertexBuffer();
}

void Tile::EnableUpdate()
{
}

void Tile::EnableRender()
{
	trans->SetDeviceTransform();
	DEVICE->SetStreamSource(0, vb, 0, sizeof(VertexPT));
	DEVICE->SetIndices(ib);
	DEVICE->SetFVF(VertexPT::FVF);
	DEVICE->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST, //그릴도형,
		0,					//vertex 시작 인덱스
		0,					//min Vertex 인덱스
		4,					//vertex 갯수
		0,					//시작 index
		2					//그릴 도형 갯수
	);
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	this->collider->Render();
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

}

void Tile::DeviceSetTexture(LPDIRECT3DTEXTURE9 pTex)
{
	DEVICE->SetTexture(0, pTex);
}

void Tile::SetSize(float width, float height)
{
	rc->SetCenterSize(width, height);
	this->CreateVertexBuffer();
}

void Tile::SetPosition(float posX, float posY)
{
	trans->SetWorldPosition(posX, posY);
}

void Tile::SetUV(float u, float v, float maxU, float maxV)
{
	this->uv[0] = { u / maxU , (v + 1) / maxV };
	this->uv[1] = { u / maxU , v  / maxV };
	this->uv[2] = { (u +1) / maxU , v  / maxV };
	this->uv[3] = { (u + 1) / maxU , (v + 1) / maxV };
	this->CreateVertexBuffer();

}

