#include "stdafx.h"
#include "Object.h"


Object::Object()
{
	
}


Object::~Object()
{
}

void Object::Init()
{
	DEVICE->CreateVertexBuffer
	(
		sizeof(VertexPT) * 4,		//저장사이즈
		D3DUSAGE_DYNAMIC,
		VertexPT::FVF,				//FVF
		D3DPOOL_DEFAULT,
		&vb, NULL
	);
	DEVICE->CreateIndexBuffer
	(
		sizeof(UINT) * 6,
		D3DUSAGE_DYNAMIC,
		D3DFMT_INDEX32,
		D3DPOOL_DEFAULT,
		&ib, NULL
	);
	rc = new Rect(0, 0, 100, 100);
	uv[0] = D3DXVECTOR2(0, 1);
	uv[1] = D3DXVECTOR2(0, 0);
	uv[2] = D3DXVECTOR2(1, 0);
	uv[3] = D3DXVECTOR2(1, 1);

	D3DXCreateTextureFromFile(
		DEVICE, "Images/block.jpg", &pTex
	);

	trans = new Transform;
	trans->SetWorldPosition(WINSIZE_X / 2, WINSIZE_Y / 2);

	collider = new Collider(*rc);


	this->CreateVertexBuffer();
	this->CreateIndexBuffer();
}

void Object::Release()
{
	SAFE_DELETE(trans);
	SAFE_DELETE(rc);
	SAFE_RELEASE(ib);
	SAFE_RELEASE(vb);
}

void Object::Update()
{
	if (this->isActive)
		EnableUpdate();
	else
		DisableUpdate();
}

void Object::Render()
{
	if (this->isActive)
		EnableRender();
}

void Object::SetActive(bool isActive)
{
	if (this->isActive == false && isActive == true)
	{
		this->EnableInit();
		this->isActive = true;
	}
	if (this->isActive == true && isActive == false)
	{
		this->DisableInit();
		this->isActive = false;
	}
}

void Object::UpdateCollider()
{
	this->collider->SetAABBBox(*rc, this->trans->GetWorld());

}

void Object::CreateVertexBuffer()
{
	VertexPT* vertex;
	vb->Lock(0, sizeof(VertexPT) * 4, (void**)&vertex, 0);
	{
		for (int i = 0; i < 4; i++)
		{
			vertex[i].position = rc->position[i];
			vertex[i].uv = uv[i];
		}
	}
	vb->Unlock();
}

void Object::CreateIndexBuffer()
{
	void* pIndex;
	ib->Lock(0, sizeof(UINT) * 6, &pIndex, 0);
	{
		memcpy(pIndex, rc->index, sizeof(UINT) * 6);
	}
	ib->Unlock();

}

void Object::EnableInit() //비 -> 활
{
	trans->SetWorldPosition(
		rand() % 600 + 200,
		rand() % 600 + 200
	);
}

void Object::DisableInit()
{
	dwStart = GetTickCount();
}

void Object::EnableUpdate()
{
	trans->DefaultControl();
	//MATREIX 
	collider->SetAABBBox(*rc, trans->GetWorld());
}

void Object::DisableUpdate()
{
	dwEnd = GetTickCount();
	ImGui::Begin("Transform");
	int count = dwEnd - dwStart;
	ImGui::InputInt("Respawn", &count);
	ImGui::End();
	if (dwEnd - dwStart > 1000)
	{
		this->SetActive(true);
	}
}

void Object::EnableRender()
{
	trans->SetDeviceTransform();
	DEVICE->SetTexture(0, pTex);
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
