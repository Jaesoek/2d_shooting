#include "stdafx.h"
#include "Scene_AStar.h"
#include "Camera.h"

Scene_AStar::Scene_AStar()
{
}


Scene_AStar::~Scene_AStar()
{
}

void Scene_AStar::Init()
{
	_aStarState = ASTAR_STATE_END;

	selectedColor = 0xFFFFFFFF;
	selectedType = TILE_TYPE_EMPTY;

	StartPointSet = false;
	EndPointSet = false;

	for (int i = 0; i < TILE_Y; ++i)
	{
		for (int j = 0; j < TILE_X; ++j)
		{
			tile[i][j].type = TILE_TYPE_EMPTY;
			tile[i][j].color = 0xFFFFFFFF;
			tile[i][j].parent = NULL;
			tile[i][j].F = BIGNUM;
			tile[i][j].H = 0;
			tile[i][j].i = i;
			tile[i][j].j = j;
			tile[i][j].rc.RectMake(
				WINSIZE_X - (TILE_X + 1) * WIDTH + WIDTH * j,
				WINSIZE_Y - (TILE_Y + 1) * HEIGHT + HEIGHT * i,
				WIDTH, HEIGHT
			);
		}
	}

	D3DXCreateEffectFromFile(
		DEVICE,
		"TileMap.fx",
		0,
		0,
		0,
		0,
		&pEffect,
		0
	);
}

void Scene_AStar::Release()
{
	SAFE_RELEASE(pEffect);
}

void Scene_AStar::Update()
{
	if (_aStarState == ASTAR_STATE_END)
	{
		TileComposition();
	}

	if (Input->GetKeyDown(VK_SPACE) && StartPointSet == true &&
		EndPointSet == true && _aStarState == ASTAR_STATE_END)
	{
		TileInitializing();
	}
	if (_aStarState == ASTAR_STATE_END ||
		_aStarState == ASTAR_STATE_FOUND ||
		_aStarState == ASTAR_STATE_NOWAY)
		return;

	AddOpenList();
	CalculateH();
	CalculateF();
	AddCloseList();
	CheckArrive();
}

void Scene_AStar::Render(Camera* pCam)
{
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	pEffect->SetMatrix("matWorld", &matWorld);
	pEffect->SetMatrix("matView", &pCam->GetView());
	pEffect->SetMatrix("matProjection", &pCam->GetProjection());
	//DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	VertexPT vertice[6];
	for (int i = 0; i < TILE_Y;i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			vertice[0].position = tile[i][j].rc.position[0];
			vertice[1].position = tile[i][j].rc.position[1];
			vertice[2].position = tile[i][j].rc.position[2];
			vertice[3].position = tile[i][j].rc.position[0];
			vertice[4].position = tile[i][j].rc.position[2];
			vertice[5].position = tile[i][j].rc.position[3];

			DEVICE->SetRenderState(D3DRS_LIGHTING, false);
			pEffect->SetFloatArray("Color", tile[i][j].color,4);
			UINT iPassNum = 0;

			pEffect->Begin(&iPassNum, 0);
			pEffect->BeginPass(0);

			DEVICE->SetFVF(VertexPT::FVF);
			DEVICE->DrawPrimitiveUP(
				D3DPT_TRIANGLELIST,
				2,
				vertice,
				sizeof(VertexPT)
			);

			pEffect->EndPass();
			pEffect->End();

		}
	}
	Font::Get()->PrintText(0xFFFF0000, 15, 15, (char*)"%d : EMPTY", 1);
	Font::Get()->PrintText(0xFFFF0000, 15, 35, (char*)"%d : START", 2);
	Font::Get()->PrintText(0xFFFF0000, 15, 55, (char*)"%d : END", 3);
	Font::Get()->PrintText(0xFFFF0000, 15, 75, (char*)"%d : WALL", 4);

	if (_aStarState == ASTAR_STATE_END)
		Font::Get()->PrintText("Press Space To Start", 15, 120, 0xFF000000);
	else if (_aStarState == ASTAR_STATE_FOUND)
		Font::Get()->PrintText("find way", 15, 120, 0xFF000000);
	else if (_aStarState == ASTAR_STATE_NOWAY)
		Font::Get()->PrintText("No Way!!", 15, 120, 0xFF000000);
	else if (_aStarState == ASTAR_STATE_SEARCHING)
		Font::Get()->PrintText("Now Searching...", 15, 120, 0xFF000000);

	
}

void Scene_AStar::TileComposition()
{
	if (Input->GetKeyDown('1'))
	{
		selectedType = TILE_TYPE_EMPTY;
		selectedColor = 0xFFFFFFFF;
	}
	else if (Input->GetKeyDown('2'))
	{
		selectedType = TILE_TYPE_START;
		selectedColor = 0xFF00FF00;
	}
	else if (Input->GetKeyDown('3'))
	{
		selectedType = TILE_TYPE_END;
		selectedColor = 0xFFFF0000;
	}
	else if (Input->GetKeyDown('4'))
	{
		selectedType = TILE_TYPE_WALL;
		selectedColor = 0xFF000000;
	}

	if (Input->GetKey(VK_LBUTTON))
	{
		for (int i = 0; i < TILE_Y; i++)
		{
			for (int j = 0; j < TILE_X; j++)
			{
				if (PtInRect(&tile[i][j].rc, _ptMouse))
				{
					if (tile[i][j].type == TILE_TYPE_START) StartPointSet = false;
					if (tile[i][j].type == TILE_TYPE_END) EndPointSet = false;

					tile[i][j].type = selectedType;
					tile[i][j].color = selectedColor;

					if (selectedType == TILE_TYPE_START)
					{
						if (StartPointSet)
						{
							tile[startX][startY].color = 0xFFFFFFFF;
							tile[startX][startY].type = TILE_TYPE_EMPTY;
						}
						StartPointSet = true;
						startX = j;
						startY = i;
					}
					if (selectedType == TILE_TYPE_END)
					{
						if (EndPointSet)
						{
							tile[endX][endY].color = 0xFFFFFFFF;
							tile[endX][endY].type = TILE_TYPE_EMPTY;
						}
						EndPointSet = true;
						endX = j;
						endY = i;
					}
				}
			}
		}
	}
	
}

void Scene_AStar::TileInitializing()
{
	barrive = false;
	for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			if (tile[i][j].type == TILE_TYPE_EMPTY)
			{
				tile[i][j].walkAble = true;
				tile[i][j].listOn = false;
			}
			else if (tile[i][j].type == TILE_TYPE_START)
			{
				tile[i][j].walkAble = true;
				tile[i][j].listOn = true;
				_closeList.push_back(&tile[i][j]);
			}
			else if (tile[i][j].type == TILE_TYPE_END)
			{
				tile[i][j].walkAble = true;
				tile[i][j].listOn = false;
				endX = j;
				endY = i;
			}
			else if (tile[i][j].type == TILE_TYPE_WALL)
			{
				tile[i][j].walkAble = false;
				tile[i][j].listOn = false;
			}
		}
	}
	_aStarState = ASTAR_STATE_SEARCHING;
	lastIndex = 0;
}

void Scene_AStar::AddOpenList()
{
	
	Ci = _closeList[lastIndex]->i;
	Cj = _closeList[lastIndex]->j;
	Cg = _closeList[lastIndex]->G;
	if (Ci != 0)
	{
		if (tile[Ci - 1][Cj].walkAble)
		{
			if (!tile[Ci - 1][Cj].listOn)
			{
				tile[Ci - 1][Cj].listOn = true;
				tile[Ci - 1][Cj].color = 0xFFAAFFAA;
				tile[Ci - 1][Cj].G = Cg + 10;
				tile[Ci - 1][Cj].parent = _closeList[lastIndex];
				_openList.push_back(&tile[Ci - 1][Cj]);

			}
			else
			{
				if (Cg + 10 < tile[Ci - 1][Cj].G)
				{
					tile[Ci - 1][Cj].G = Cg + 10;
					tile[Ci - 1][Cj].parent = _closeList[lastIndex];
				}
			}
		}//if (tile[Ci - 1][Cj].walkAble)

		if (Cj != 0)
		{
			if (tile[Ci - 1][Cj - 1].walkAble &&
				tile[Ci - 1][Cj].walkAble &&
				tile[Ci][Cj - 1].walkAble)
			{
				if (!tile[Ci - 1][Cj - 1].listOn)
				{
					tile[Ci - 1][Cj - 1].listOn = true;
					tile[Ci - 1][Cj - 1].color = 0xFFAAFFAA;
					tile[Ci - 1][Cj - 1].G = Cg + 14;
					tile[Ci - 1][Cj - 1].parent = _closeList[lastIndex];
					_openList.push_back(&tile[Ci - 1][Cj - 1]);
				}
				else
				{
					if (14 + Cg < tile[Ci - 1][Cj - 1].G)
					{
						tile[Ci - 1][Cj - 1].G = Cg + 14;
						tile[Ci - 1][Cj - 1].parent = _closeList[lastIndex];

					}
				}
			}
		}
		if (Cj != TILE_X - 1) //우상단 
		{
			if (tile[Ci - 1][Cj + 1].walkAble &&
				tile[Ci - 1][Cj].walkAble &&
				tile[Ci][Cj + 1].walkAble)
			{
				if (!tile[Ci - 1][Cj + 1].listOn)
				{
					tile[Ci - 1][Cj + 1].listOn = true;
					tile[Ci - 1][Cj + 1].color = 0xFFAAFFAA;
					tile[Ci - 1][Cj + 1].G = Cg + 14;
					tile[Ci - 1][Cj + 1].parent = _closeList[lastIndex];
					_openList.push_back(&tile[Ci - 1][Cj + 1]);
				}
				else
				{
					if (14 + Cg < tile[Ci - 1][Cj + 1].G)
					{
						tile[Ci - 1][Cj + 1].G = Cg + 14;
						tile[Ci - 1][Cj + 1].parent = _closeList[lastIndex];
					}
				}
			}
		}
	}
	if (Cj != 0)
	{
		if (tile[Ci][Cj - 1].walkAble)
		{
			if (!tile[Ci][Cj - 1].listOn)
			{
				tile[Ci][Cj - 1].listOn = true;
				tile[Ci][Cj - 1].color = 0xFFAAFFAA;
				tile[Ci][Cj - 1].G = Cg + 10;
				tile[Ci][Cj - 1].parent = _closeList[lastIndex];
				_openList.push_back(&tile[Ci][Cj - 1]);
			}
			else
			{
				if (10 + Cg < tile[Ci][Cj - 1].G)
				{
					tile[Ci][Cj - 1].G = Cg + 10;
					tile[Ci][Cj - 1].parent = _closeList[lastIndex];

				}
			}
		}
	}

	if (Cj != TILE_X - 1)
	{
		if (tile[Ci][Cj + 1].walkAble)
		{
			if (!tile[Ci][Cj + 1].listOn)
			{
				tile[Ci][Cj + 1].listOn = true;
				tile[Ci][Cj + 1].color = 0xFFAAFFAA;
				tile[Ci][Cj + 1].G = Cg + 10;
				tile[Ci][Cj + 1].parent = _closeList[lastIndex];
				_openList.push_back(&tile[Ci][Cj + 1]);
			}
			else
			{
				if (10 + Cg < tile[Ci][Cj - 1].G)
				{
					tile[Ci][Cj + 1].G = Cg + 10;
					tile[Ci][Cj + 1].parent = _closeList[lastIndex];

				}
			}
		}
	}

	if (Ci != TILE_Y - 1)
	{
		if (tile[Ci + 1][Cj].walkAble)
		{
			if (!tile[Ci + 1][Cj].listOn)
			{
				tile[Ci + 1][Cj].listOn = true;
				tile[Ci + 1][Cj].color = 0xFFAAFFAA;
				tile[Ci + 1][Cj].G = Cg + 10;
				tile[Ci + 1][Cj].parent = _closeList[lastIndex];
				_openList.push_back(&tile[Ci + 1][Cj]);

			}
			else
			{
				if (Cg + 10 < tile[Ci + 1][Cj].G)
				{
					tile[Ci + 1][Cj].G = Cg + 10;
					tile[Ci + 1][Cj].parent = _closeList[lastIndex];
				}
			}
		}//if (tile[Ci - 1][Cj].walkAble)
		if (Cj != 0)
		{
			if (tile[Ci + 1][Cj - 1].walkAble &&
				tile[Ci + 1][Cj].walkAble &&
				tile[Ci][Cj - 1].walkAble)
			{
				if (!tile[Ci + 1][Cj - 1].listOn)
				{
					tile[Ci + 1][Cj - 1].listOn = true;
					tile[Ci + 1][Cj - 1].color = 0xFFAAFFAA;
					tile[Ci + 1][Cj - 1].G = Cg + 14;
					tile[Ci + 1][Cj - 1].parent = _closeList[lastIndex];
					_openList.push_back(&tile[Ci + 1][Cj - 1]);
				}
				else
				{
					if (14 + Cg < tile[Ci + 1][Cj - 1].G)
					{
						tile[Ci + 1][Cj - 1].G = Cg + 14;
						tile[Ci + 1][Cj - 1].parent = _closeList[lastIndex];
					}
				}
			}
		}
		if (Cj != TILE_X - 1) //우상단 
		{
			if (tile[Ci + 1][Cj + 1].walkAble &&
				tile[Ci + 1][Cj].walkAble &&
				tile[Ci][Cj + 1].walkAble)
			{
				if (!tile[Ci + 1][Cj + 1].listOn)
				{
					tile[Ci + 1][Cj + 1].listOn = true;
					tile[Ci + 1][Cj + 1].color = 0xFFAAFFAA;
					tile[Ci + 1][Cj + 1].G = Cg + 14;
					tile[Ci + 1][Cj + 1].parent = _closeList[lastIndex];
					_openList.push_back(&tile[Ci - 1][Cj + 1]);
				}
				else
				{
					if (14 + Cg < tile[Ci + 1][Cj + 1].G)
					{
						tile[Ci + 1][Cj + 1].G = Cg + 14;
						tile[Ci + 1][Cj + 1].parent = _closeList[lastIndex];
					}
				}
			}
		}
	}

	
}

void Scene_AStar::CalculateH()
{
	for (int i = 0; i < _openList.size(); i++)
	{
		int vertical = (endX - _openList[i]->j) * 10;
		int horizontal = (endY - _openList[i]->i) * 10;

		if (vertical < 0) vertical *= -1;
		if (horizontal < 0) horizontal *= -1;
		_openList[i]->H = vertical + horizontal;
	}
}

void Scene_AStar::CalculateF()
{
	for (int i = 0; i < _openList.size(); i++)
	{
		_openList[i]->F = _openList[i]->G + _openList[i]->H;
	}
}

void Scene_AStar::AddCloseList()
{
	if (_openList.size() == 0)
	{
		_aStarState = ASTAR_STATE_NOWAY;
		return;
	}

	int index = 0;
	int lowest = BIGNUM;
	for (int i = 0; i < _openList.size();i++)
	{
		if (_openList[i]->F < lowest)
		{
			lowest = _openList[i]->F;
			index = i;
		}
	}

	_openList[index]->color = 0xFF8080FF;
	_closeList.push_back(_openList[index]);
	_openList.erase(_openList.begin() + index);

	lastIndex++;
}

void Scene_AStar::CheckArrive()
{
	if (_closeList[lastIndex]->i == endY &&
		_closeList[lastIndex]->j == endX)
	{
		_aStarState = ASTAR_STATE_FOUND;
		_closeList[lastIndex]->color = 0xFFFF5050;
		ShowWay(_closeList[lastIndex]);
		barrive = true;
	}
}

void Scene_AStar::ShowWay(aStarTile * tile)
{
	if (!(tile->i == endY && tile->j == endX))
		tile->color = 0xFFFF8080;
	tile = tile->parent;
	if (tile->parent == NULL)
		return;
	else
		ShowWay(tile);
}
