#include "stdafx.h"
#include "Scene_AStar.h"


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

			tile[i][j].rc = RectMake(
				WINSIZE_X - (TILE_X + 1) * WIDTH * WIDTH * j,
				WINSIZE_Y - (TILE_Y+1) * HEIGHT *HEIGHT * i,
				WIDTH, HEIGHT);
		}
	}
}

void Scene_AStar::Release()
{
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

void Scene_AStar::Render()
{
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	DEVICE->SetTransform(D3DTS_WORLD, &matWorld);
	DEVICE->SetFVF(VertexPC::FVF);

	Font::Get()->PrintText(0xFFFF0000 , 15, 15, (char*)"%d : EMPTY", 1);
	Font::Get()->PrintText(0xFFFF0000, 15, 35, (char*)"%d : EMPTY", 2);
	Font::Get()->PrintText(0xFFFF0000, 15, 55, (char*)"%d : EMPTY", 3);
	Font::Get()->PrintText(0xFFFF0000, 15, 75, (char*)"%d : EMPTY", 4);

	if (_aStarState == ASTAR_STATE_END)
		Font::Get()->PrintText("Press Space To Start", 15, 120, 0xFF000000);
	else if(_aStarState == ASTAR_STATE_FOUND)
		Font::Get()->PrintText("Find Way", 15, 120, 0xFF000000);
	else if (_aStarState == ASTAR_STATE_NOWAY)
		Font::Get()->PrintText("No Way!", 15, 120, 0xFF000000);
	else if (_aStarState == ASTAR_STATE_SEARCHING)
		Font::Get()->PrintText("Now Searching...", 15, 120, 0xFF000000);


	VertexPC vertice[4];
	for (int i = 0; i < TILE_Y; ++i)
	{
		for (int j = 0; j < TILE_X; ++j)
		{
			for (int k = 0; k < 4; k++)
			{
				vertice[k].position = tile[i][j].rc.position[i];
				vertice[k].color = tile[i][j].color;
			}
			DEVICE->DrawIndexedPrimitiveUP(
				D3DPT_TRIANGLELIST,
				0,
				0,
				2,
				tile[i][j].rc.index,
				D3DFMT_INDEX32,
				vertice,
				sizeof(vertice)
			);
			
		}
	}
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
		selectedType = TILE_TYPE_EMPTY;
		selectedColor = 0xFF00FF00;
	}
	else if (Input->GetKeyDown('3'))
	{
		selectedType = TILE_TYPE_END;
		selectedColor = 0xFFFF0000;
	}
	else if (Input->GetKeyDown('4'))
	{
		selectedType = TILE_TYPE_END;
		selectedColor = 0xFF000000;
	}

	if (Input->GetKey(VK_LBUTTON))
	{
		for (int i = 0; i < TILE_Y; ++i)
		{
			for (int j = 0; j < TILE_X; ++j)
			{
				if (PtInRect(&tile[i][j].rc, _ptMouse))
				{
					if (tile[i][j].type == TILE_TYPE_START) StartPointSet = false;
					if (tile[i][j].type == TILE_TYPE_END) EndPointSet = false;

					tile[i][j].type = selectedType;
					tile[i][j].color = selectedColor;

				}
			}
		}
	}

}

void Scene_AStar::TileInitializing()
{
	for (int i = 0; i < TILE_Y; ++i)
	{
		for (int j = 0; j < TILE_X; ++j)
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

				startX = j;
				startY = i;
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

	if (Cj != TILE_X -1)
	{
		if (tile[Ci][Cj + 1].walkAble)
		{
			if (!tile[Ci][Cj + 1].listOn)
			{
				tile[Ci][Cj + 1].listOn = true;
				tile[Ci][Cj + 1].color = 0xFFAAFFAA;
				tile[Ci][Cj + 1].G = Cg + 10;
				tile[Ci][Cj + 1].parent = _closeList[lastIndex];
				_openList.push_back(&tile[Ci][Cj - 1]);
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
	}

	int index = 0;
	int lowest = BIGNUM;
	for (int i = 0; i < _openList.size(); ++i)
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
	}
}

void Scene_AStar::ShowWay(aStarTile * tile)
{
}
