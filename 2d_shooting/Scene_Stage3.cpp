#include "stdafx.h"
#include "Scene_Stage3.h"
#include "Camera.h"


Scene_Stage3::Scene_Stage3()
{
}


Scene_Stage3::~Scene_Stage3()
{
}

void Scene_Stage3::Init()
{
	tile = new IsoTile;
	tile->Init();
	ZeroMemory(uv, sizeof(D3DXVECTOR2) * TILEX * TILEY);

	Texture::Get()->Init("Tile", "Images/mario_tile1.png");

	tile->SetUV(uv[0][0].x, uv[0][0].y, 32.0f, 32.0f);
	cameraCollider = new Collider(RECT{ 0, 0, 0, 0 });
}

void Scene_Stage3::Release()
{
	tile->Release();
	SAFE_DELETE(tile);
}

void Scene_Stage3::Update()
{
	mainCamera->Update();
	mainCamera->DefaultControl();
}

void Scene_Stage3::Render()
{
	mainCamera->SetDeviceMatrix();
	for (int i = 0; i < TILEX; ++i)
	{
		for (int j = 0; j < TILEY; ++j)
		{
			tile->SetPosition(
				STARTX + 50 * i - 50 * j,
				STARTY + 25 * i + 25 * j);
			tile->UpdateCollider();
			RECT rc = { 0,0,WINSIZE_X,WINSIZE_Y };
			cameraCollider->SetAABBBox(
				rc, mainCamera->GetWorld());
			RECT tileRc = tile->Getcollider()->GetRect();
			if (Intersect::IsConstainRect(
				NULL,
				tileRc, 
				cameraCollider->GetRect()))
			{
				
				Texture::Get()->SetDeivceTexture("Tile");
				tile->Render();
			}
		}
	}
}

void Scene_Stage3::SetInterface()
{

}
