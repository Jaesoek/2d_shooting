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
		D3DPT_TRIANGLELIST, //�׸�����,
		0,					//vertex ���� �ε���
		0,					//min Vertex �ε���
		4,					//vertex ����
		0,					//���� index
		2					//�׸� ���� ����
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

