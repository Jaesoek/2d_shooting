#pragma once
#define TILE_X 20
#define TILE_Y 20
#define WIDTH 40
#define HEIGHT 40
#define BIGNUM 5000 //ū�� 

enum TILE_TYPE
{
	TILE_TYPE_EMPTY, //�� Ÿ�� (�̵�����)
	TILE_TYPE_START, //��������
	TILE_TYPE_END,   //������ 
	TILE_TYPE_WALL   //��
};

enum ASTAR_STATE
{
	ASTAR_STATE_SEARCHING,
	ASTAR_STATE_FOUND,
	ASTAR_STATE_NOWAY,
	ASTAR_STATE_END
};

struct aStarTile
{
	Rect rc;
	D3DXCOLOR color;
	bool walkAble; //�������� �ִ� ��?
	bool listOn; //openList�� �߰� �Ǿ�����?
	int i, j; //�迭�� �ε���
	int F, G, H; //F : ���� G : 1Ÿ�� �̵��� , H �������� �ִܰŸ�
	aStarTile* parent;
	TILE_TYPE type; //Ÿ�� �Ӽ� 
};
class Scene_AStar 
{
private:
	struct Vertex
	{
		D3DXVECTOR4 position;
		D3DXCOLOR color;
	};

	aStarTile tile[TILE_X][TILE_Y];
	vector<aStarTile*> _openList;
	vector<aStarTile*> _closeList;

	TILE_TYPE selectedType;
	D3DXCOLOR selectedColor;

	int startX, startY;// ��������
	int endX, endY;
	int lastIndex; //Ŭ���� ������ �߰��� ������ �ε��� ��ȣ
	
	bool StartPointSet; //�������� ��ġ ����
	bool EndPointSet; //�������� ����

	int Ci;
	int Cj;
	int Cg;

	ASTAR_STATE _aStarState;

	LPD3DXEFFECT pEffect;

	bool barrive = false;

public:
	Scene_AStar();
	~Scene_AStar();

	void Init();
	void Release();
	void Update();
	void Render(class Camera* pCam);

	bool GetArrive(aStarTile* lastTile)
	{
		if (barrive)
		{
			lastTile = _closeList[lastIndex];
		}
		else
			lastTile = NULL;
		return lastTile;
	}

	void SetStart(int x, int y);
	void SetEnd(int x, int y);

	void TileComposition(); //Ÿ�Ϲ�ġ
	void TileInitializing(); //��ġ�� 
	//
	void AddOpenList();
	void CalculateH();
	void CalculateF();
	void AddCloseList();
	void CheckArrive();
	//
	void ShowWay(aStarTile* tile);

};

