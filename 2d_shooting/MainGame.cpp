#include "stdafx.h"
#include "MainGame.h"

#include "Camera.h"

#include "Scene.h"
#include "Scene_Stage1.h"
#include "Scene_Stage2.h"
#include "Scene_Stage3.h"

MainGame::MainGame()
{

}
MainGame::~MainGame()
{
}

void MainGame::Init(HWND hWnd)
{
	this->hWnd = hWnd;
	srand(time(NULL));
	D2D::GetDevice(hWnd);


	ImGui::CreateContext();
	HRESULT hr = ImGui::ImplWin32_Init(hWnd);
	
	//장치 생성시 성공 true 실패 false;
	//assert(조건) 조건 == 참 -> 통과 x 
	assert(hr && "Failed Init ImpleWin32");
	hr = ImGui::ImplDX9_Init(D2D::GetDevice());
	assert(hr && "Failed Init ImplDX9");
	ImGui::StyleColorsDark();

/////////////////////////////////////////////////////////

	nowScene = new Scene_Stage3;
	nowScene->Init();

	target = new RenderTarget();
	target->Init();

	minimap = new MiniMap;
	minimap->Init();
	minimap->SetTexture(target->GetTexture());

	D3DXVECTOR4 vec[2] =
	{
		D3DXVECTOR4(100,100,0,1),
		D3DXVECTOR4(100,200,0,1)
	};
	

}

void MainGame::Release()
{
	nowScene->Release();
	SAFE_DELETE(nowScene);

	minimap->Release();
	SAFE_DELETE(minimap);

	target->Release();
	SAFE_DELETE(target);



	ImGui::DestroyContext();
	
	Font::Destroy();

	keybord::Destory();
	D2D::Destroy();
}

void MainGame::Update()
{

	nowScene->Update();

	static int index = 0;
	if (keybord::Get()->GetKeyDown(VK_F2))
	{
		if (index == 0)
		{
			nowScene->Release();
			SAFE_DELETE(nowScene);
			nowScene = new Scene_Stage2;
			nowScene->Init();
			index++;
		}
		else if (index == 1)
		{
			
			nowScene->Release();
			SAFE_DELETE(nowScene);
			nowScene = new Scene_Stage1;
			nowScene->Init();
			index--;
		}
	}
}
void MainGame::UpdateGUI()
{
	ImGui::ImplDX9_NewFrame();
	ImGui::ImplWin32_NewFrame();
	ImGui::NewFrame();
	{
		nowScene->UpdateGUI();
	}
	ImGui::EndFrame();
}
void MainGame::Render()
{
	//화면을 지우는데 색상은 (128,128,128)
	D2D::GetDevice()->Clear(0, NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(128, 128, 128),1.0f,0);
	D2D::GetDevice()->BeginScene();
	{
	/////////////////////////////////////////////////////
		//DEVICE->SetRenderState(D3DRS_LIGHTING, false);
		DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		minimap->Render();
		nowScene->Render();
		
	/////////////////////////////////////////////////////
	}
	ImGui::Render();
	ImGui::ImplDX9_RenderDrawData(ImGui::GetDrawData());
	D2D::GetDevice()->EndScene();
	
	//back buffer 내용을 front buffer 으로 보내준다.
	D2D::GetDevice()->Present(0, 0, 0, 0);
}

void MainGame::RenderTargets()
{
	target->BeginScene();
	{
		nowScene->Render();
	}
	target->EndScene();
}

LRESULT MainGame::MainProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui::ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;
	switch (msg)
	{
	case WM_MOUSEMOVE:
		ptMouse.y = HIWORD(lParam);
		ptMouse.x = LOWORD(lParam);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
			case VK_ESCAPE:
				PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd,msg,wParam,lParam);
}
