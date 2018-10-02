#include "stdafx.h"
#include "Scene_Stage4.h"
#include "Camera.h"

Scene_Stage4::Scene_Stage4()
{
}


Scene_Stage4::~Scene_Stage4()
{
}

void Scene_Stage4::Init()
{
	vertice[0] = VertexPT(0, WINSIZE_Y, 0, 1);
	vertice[1] = VertexPT(0, 0, 0, 0);
	vertice[2] = VertexPT(WINSIZE_X, 0, 1, 0);

	vertice[3] = VertexPT(0, WINSIZE_Y, 0, 1);
	vertice[4] = VertexPT(WINSIZE_X, 0, 1, 0);
	vertice[5] = VertexPT(WINSIZE_X, WINSIZE_Y, 1, 1);


	Texture::Get()->Init("Test", "Images/Mine.jpg");


	DWORD dwShaderFlag = 0;
	dwShaderFlag |= D3DXSHADER_DEBUG;
	LPD3DXBUFFER pError;
	D3DXCreateEffectFromFile(DEVICE,
		"TileMap.fx", 0, 0, dwShaderFlag, 0, &pEffect, &pError);
	if (pError)
	{
		MessageBox(NULL, (CHAR*)pError->GetBufferPointer(),
			"Sahder", MB_OK);
	}
}

void Scene_Stage4::Release()
{
	SAFE_RELEASE(pEffect);
}

void Scene_Stage4::Update()
{
}

void Scene_Stage4::Render()
{
	pEffect->SetVector("tiling", &D3DXVECTOR4(10,10,0,0));
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	pEffect->SetMatrix("matWorld", &matWorld);
	pEffect->SetMatrix("matView", &mainCamera->GetView());
	pEffect->SetMatrix("matProjection", &mainCamera->GetProjection());
	pEffect->SetTechnique("TILING");
	pEffect->SetTexture("pTex", Texture::Get()->GetTexture("Test"));
	UINT iPassNum;
	pEffect->Begin(&iPassNum, 0);
	{
		pEffect->BeginPass(0);
		{
			DEVICE->SetFVF(VertexPT::FVF);
			DEVICE->DrawPrimitiveUP(
				D3DPT_TRIANGLELIST,
				2,
				vertice,
				sizeof(VertexPT)
			);
		}
		pEffect->EndPass();
	}
	pEffect->End();
}

void Scene_Stage4::SetInterface()
{
}
