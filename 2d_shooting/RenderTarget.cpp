#include "stdafx.h"
#include "RenderTarget.h"


RenderTarget::RenderTarget()
{
}


RenderTarget::~RenderTarget()
{
	this->Release();
}

void RenderTarget::Init()
{
	//ortho size(
	//빈텍스쳐 생성 
	DEVICE->CreateTexture
	(
		WINSIZE_X, //내가 저장할 범위 크기로 
		WINSIZE_Y, //
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&pRenderTexture,
		NULL
	);
	DEVICE->CreateDepthStencilSurface
	(
		WINSIZE_X,
		WINSIZE_Y,
		D3DFMT_D24S8,
		D3DMULTISAMPLE_NONE,
		0, //퀄리티 
		TRUE,
		&pRenderSurface,
		NULL
	);
}

void RenderTarget::Release()
{
	SAFE_RELEASE(pRenderTexture);
	SAFE_RELEASE(pRenderSurface);
}

void RenderTarget::BeginScene()
{
	//화면에 랜더링 되는 대신에 Texture랜더링한다.
	DEVICE->GetRenderTarget(0, &pDeviceTargetSurface);
	DEVICE->GetDepthStencilSurface(&pDeviceDepthAndStencil);

	LPDIRECT3DSURFACE9 texSurface = NULL;
	if (SUCCEEDED(this->pRenderTexture->GetSurfaceLevel(0,&texSurface)))
	{
		DEVICE->SetRenderTarget(0, texSurface);
		SAFE_RELEASE(texSurface);
	}
	DEVICE->SetDepthStencilSurface(pRenderSurface);
	DEVICE->Clear(0, NULL, D3DCLEAR_TARGET |
		D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, 
		0xFF0000FF, 1.0f, 0.0f);
}

void RenderTarget::EndScene()
{
	DEVICE->SetRenderTarget(0, pDeviceTargetSurface);
	DEVICE->SetDepthStencilSurface(pDeviceDepthAndStencil);

	SAFE_RELEASE(pDeviceDepthAndStencil);
	SAFE_RELEASE(pDeviceTargetSurface);
}

void RenderTarget::SaveTexture()
{
	D3DXSaveTextureToFile(
		"Images/RenderTarget.png",
		D3DXIFF_PNG,
		pRenderTexture,
		NULL
	);
}

void RenderTarget::SetTexture()
{
}
