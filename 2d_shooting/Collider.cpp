#include "stdafx.h"
#include "Collider.h"


Collider::Collider()
{

}

Collider::Collider(RECT rc)
{
	AABBBox[0] = D3DXVECTOR2(rc.left, rc.top);
	AABBBox[1] = D3DXVECTOR2(rc.right, rc.top);
	AABBBox[2] = D3DXVECTOR2(rc.right,rc.bottom);
	AABBBox[3] = D3DXVECTOR2(rc.left, rc.bottom);
	AABBBox[4] = D3DXVECTOR2(rc.left, rc.top);

	OBBBox[0] = D3DXVECTOR2(rc.left, rc.top);
	OBBBox[1] = D3DXVECTOR2(rc.right, rc.top);
	OBBBox[2] = D3DXVECTOR2(rc.right, rc.bottom);
	OBBBox[3] = D3DXVECTOR2(rc.left, rc.bottom);
	OBBBox[4] = D3DXVECTOR2(rc.left, rc.top);
}


Collider::~Collider()
{
}

void Collider::SetAABBBox(RECT rc, const D3DXMATRIX& matWorld)
{
	AABBBox[0] = D3DXVECTOR2(rc.left, rc.top);
	AABBBox[1] = D3DXVECTOR2(rc.right, rc.top);
	AABBBox[2] = D3DXVECTOR2(rc.right, rc.bottom);
	AABBBox[3] = D3DXVECTOR2(rc.left, rc.bottom);
	AABBBox[4] = D3DXVECTOR2(rc.left, rc.top);

	D3DXVECTOR4 temp[5];
	for (int i = 0; i < 5; i++)
	{
		D3DXVec2Transform(&temp[i], &AABBBox[i], &matWorld);
		OBBBox[i].x = temp[i].x;
		OBBBox[i].y = temp[i].y;
	}

	D3DXVECTOR2 vMin(WINSIZE_X, WINSIZE_Y);
	D3DXVECTOR2 vMax(0, 0);
	for (int i = 0; i < 5; i++)
	{
		if (vMin.x > OBBBox[i].x)
			vMin.x = OBBBox[i].x;

		if (vMin.y > OBBBox[i].y)
			vMin.y = OBBBox[i].y;

		if (vMax.x < OBBBox[i].x)
			vMax.x = OBBBox[i].x;

		if (vMax.y < OBBBox[i].y)
			vMax.y = OBBBox[i].y;
	}
	//¿Þ»ó
	AABBBox[0].x = vMin.x;
	AABBBox[0].y = vMin.y;
	//¿À»ó
	AABBBox[1].x = vMax.x;
	AABBBox[1].y = vMin.y;
	//¿ÀÇÏ
	AABBBox[2].x = vMax.x;
	AABBBox[2].y = vMax.y;
	//¿ÞÇÏ 
	AABBBox[3].x = vMin.x;
	AABBBox[3].y = vMax.y;
	//¿Þ»ó 
	AABBBox[4] = AABBBox[0];

	this->rc = { (long)vMin.x, (long)vMin.y, (long)vMax.x, (long)vMax.y };
}

void Collider::Render()
{
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	DEVICE->SetTransform(D3DTS_WORLD, &matWorld);

	VertexPC line[2];
	
	line[0] = VertexPC(D3DXVECTOR2(400,500),0xFFFF0000);
	line[1] = VertexPC(D3DXVECTOR2(800, 500), 0xFFFF0000);


	DEVICE->SetFVF(VertexPC::FVF);
	DEVICE->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, line, sizeof(VertexPC));

	if (_bDebug)
	{
		D3DXMATRIX matWorld;
		D3DXMatrixIdentity(&matWorld);
		DEVICE->SetTransform(D3DTS_WORLD, &matWorld);
		VertexPC box1[5];
		VertexPC box2[5];
		for (int i = 0; i < 5; i++)
		{
			box1[i] = VertexPC(AABBBox[i], 0xFF008000);
			box2[i] = VertexPC(OBBBox[i], 0xFF00FF00);
		}
		DEVICE->SetFVF(VertexPC::FVF);
		DEVICE->DrawPrimitiveUP(D3DPT_LINESTRIP,4, box1, sizeof(VertexPC));
		DEVICE->DrawPrimitiveUP(D3DPT_LINESTRIP,4, box2, sizeof(VertexPC));
	}
}
