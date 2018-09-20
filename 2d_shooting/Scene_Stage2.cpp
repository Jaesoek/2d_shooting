#include "stdafx.h"
#include "Scene_Stage2.h"


Scene_Stage2::Scene_Stage2()
{
}


Scene_Stage2::~Scene_Stage2()
{
}

void Scene_Stage2::Init()
{
	tile = new Tile;
	tile->Init();
	tile->SetActive(true);
	tileX = tileY = 10;
	prevWidth = prevHeight = width = height = 50.0f;

	Texture::Get()->Init("TileMap", "Images/terrain_atlas.png");

	UVs.resize(tileX);
	for (int i = 0; i < 10; i++)
	{
		UVs[i].resize(tileY);
	}
	for (int i = 0; i < tileX; i++)
	{
		for (int j = 0; j < tileY; j++)
		{
			UVs[i][j].first = D3DXVECTOR2(0, 0);
			UVs[i][j].second = D3DXVECTOR2(-1, -1);
		}
	}
}

void Scene_Stage2::Release()
{
	tile->Release();
	SAFE_DELETE(tile);
}

void Scene_Stage2::Update()
{
	tile->Update();
	if (Input->GetKey(VK_LBUTTON) && (isDraw || isObj))
	{
		for (int i = 0; i < tileX * tileY; i++)
		{
			int x = i / tileY;
			int y = i % tileY;
			tile->SetPosition(x * width, y * height);
			tile->UpdateCollider();
			if (Intersect::IsConstainPoint(tile->Getcollider()->GetOBBBox(),
				_ptMouse))
			{
				if (isDraw)
					UVs[x][y].first = uv;
				if (isObj)
					UVs[x][y].second = uv;
				break;
			}
		}
	}

}

void Scene_Stage2::Render()
{
	for (int i = 0; i < tileX; i++)
	{
		for (int j = 0; j < tileY; j++)
		{
			// ���� Render
			tile->SetUV(
				UVs[i][j].first.x,
				UVs[i][j].first.y,
				32.0f, 32.0f);
			Texture::Get()->SetDeivceTexture("TileMap");
			tile->SetPosition(
				i * width, j * height);
			tile->Render();

			// Obj Render
			if (UVs[i][j].second.x >= 0 && UVs[i][j].second.y >= 0)
			{
				tile->SetUV(
					UVs[i][j].second.x,
					UVs[i][j].second.y,
					32.0f, 32.0f);
				tile->SetPosition(
					i * width, j * height);
				tile->Render();
			}
		}
	}
}

void Scene_Stage2::SetInterface()
{
	ImGui::BeginChild("Tile");
	{
		ImGui::LabelText(" ", "Tiling");
		ImGui::InputInt("X", &tileX);
		if (UVs.size() < tileX)
		{
			UVs.push_back(UVs[0]);
		}
		else if (UVs.size() > tileX)
		{
			UVs.pop_back();
		}
		ImGui::InputInt("Y", &tileY);
		if (UVs[0].size() > tileY)
		{
			for (int i = 0; i < tileX; i++)
			{
				UVs[i].pop_back();
			}
		}
		else if (UVs[0].size() < tileY)
		{
			for (int i = 0; i < tileX; i++)
			{
				UVs[i].push_back(
					make_pair<D3DXVECTOR2, D3DXVECTOR2>
					(D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0)));
			}
		}

		ImGui::SliderFloat("Width", &width, 1.0f, 100.0f);
		ImGui::SliderFloat("Height", &height, 1.0f, 100.0f);

		if (prevWidth != width)
		{
			tile->SetSize(width, height);
			prevWidth = width;
		}
		if (prevHeight != height)
		{
			tile->SetSize(width, height);
			prevHeight = height;
		}

		ImGui::InputFloat("U", &uv.x, 1.0f);
		ImGui::InputFloat("V", &uv.y, 1.0f);
		ImGui::InputFloat("MaxU", &maxUV.x, 0.1f);
		ImGui::InputFloat("MaxV", &maxUV.y, 0.1f);

		ImGui::Image(
			pSelectTex,
			ImVec2(250, 250),	// ������
			ImVec2(uv.x / maxUV.x, uv.y / maxUV.y),	// UV ��������
			ImVec2((uv.x + 1) / maxUV.x, (uv.y + 1) / maxUV.y));	// UV ������

		if (ImGui::Button("Draw"))
		{
			isDraw = true;
			isObj = false;
		}
		ImGui::SameLine();
		if (ImGui::Button("Obj"))
		{
			isDraw = false;
			isObj = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("Reset"))
		{
			isDraw = false;
			isObj = false;
		}
		ImGui::SameLine();
		if (ImGui::Button("Save"))
		{
			// ���̺� fopen, fstream, createFile
			file = CreateFile(
				"SaveMap.mp",
				GENERIC_WRITE,
				0,		// ���� ���� ��� �Է�
				NULL,	// ���� �Ǵ� ��ġ ���� �ɼ�
				CREATE_ALWAYS,	// ������ ������ ���� ����
				FILE_ATTRIBUTE_NORMAL,
				NULL
			);

			DWORD write;
			WriteFile(file, &width, sizeof(float), &write, NULL);
			WriteFile(file, &height, sizeof(float), &write, NULL);

			WriteFile(file, &tileX, sizeof(int), &write, NULL);
			WriteFile(file, &tileY, sizeof(int), &write, NULL);

			for (int i = 0; i < tileX; ++i)
			{
				for (int j = 0; j < tileY; ++j)
				{
					WriteFile(file, &UVs[i][j].first, sizeof(D3DXVECTOR2), &write, NULL);
					WriteFile(file, &UVs[i][j].second, sizeof(D3DXVECTOR2), &write, NULL);
				}
			}
			char str[64] = "TileMap";
			WriteFile(file, str, 64, &write, NULL);
			CloseHandle(file);
		}
		ImGui::SameLine();
		if (ImGui::Button("Load"))
		{
			// Load createFile
			file = CreateFile(
				"SaveMap.mp",
				GENERIC_READ,
				0,		// ���� ���� ��� �Է�
				NULL,	// ���� �Ǵ� ��ġ ���� �ɼ�
				OPEN_EXISTING,	// ������ �������� �о��
				FILE_ATTRIBUTE_NORMAL,
				NULL
			);

			DWORD read;
			ReadFile(file, &width, sizeof(float), &read, NULL);
			ReadFile(file, &height, sizeof(float), &read, NULL);

			ReadFile(file, &tileX, sizeof(int), &read, NULL);
			ReadFile(file, &tileY, sizeof(int), &read, NULL);

			for (int i = 0; i < tileX; ++i)
			{
				for (int j = 0; j < tileY; ++j)
				{
					ReadFile(file, &UVs[i][j].first, sizeof(D3DXVECTOR2), &read, NULL);
					ReadFile(file, &UVs[i][j].second, sizeof(D3DXVECTOR2), &read, NULL);
				}
			}
			ReadFile(file, &pSelectTex, sizeof(LPDIRECT3DTEXTURE9), &read, NULL);
			CloseHandle(file);
		}
	}
	ImGui::EndChild();
}
