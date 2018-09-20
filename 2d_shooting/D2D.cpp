#include "stdafx.h"
#include "D2D.h"

LPDIRECT3DDEVICE9 D2D::device = NULL;
D2D* D2D::instance = NULL;


D2D::D2D(HWND hwnd)
{
	D3DPRESENT_PARAMETERS d3dParam;
	ZeroMemory(&d3dParam, sizeof(d3dParam));

	d3dParam.Windowed = true;
	d3dParam.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dParam.EnableAutoDepthStencil = true;
	d3dParam.AutoDepthStencilFormat = D3DFMT_D16;

	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 caps; //adapter(그래픽 카드)
	d3d->GetDeviceCaps(
		D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	d3d->CreateDevice
	(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dParam, &device
	);
}


D2D::~D2D()
{
	SAFE_RELEASE(d3d);
	SAFE_RELEASE(device);
}

LPDIRECT3DDEVICE9 D2D::GetDevice(HWND hwnd)
{
	if (device == NULL && hwnd != NULL)
	{
		instance = new D2D(hwnd);
	}
	if(device != NULL)
		return device;

	return NULL;
}

void D2D::Destroy()
{
	if (instance != NULL)
		SAFE_DELETE(instance);
}
