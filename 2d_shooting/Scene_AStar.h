#pragma once
#define TILE_X 20
#define TILE_Y 20
#define WIDTH 40
#define HEIGHT 40
#define BIGNUM 5000 //큰값 

enum TILE_TYPE
{
	TILE_TYPE_EMPTY, //빈 타일 (이동가능)
	TILE_TYPE_START, //시작지점
	TILE_TYPE_END,   //끝지점 
	TILE_TYPE_WALL   //벽
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
	bool walkAble; //지날갈수 있는 가?
	bool listOn; //openList에 추가 되었느냐?
	int i, j; //배열의 인덱스
	int F, G, H; //F : 최종 G : 1타일 이동시 , H 도착지점 최단거리
	aStarTile* parent;
	TILE_TYPE type; //타일 속성 
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

	int startX, startY;// 시작지점
	int endX, endY;
	int lastIndex; //클로즈 리스에 추가된 마지막 인덱스 번호
	
	bool StartPointSet; //시작지점 배치 여부
	bool EndPointSet; //도착지점 여부

	int Ci;
	int Cj;
	int Cg;

	ASTAR_STATE _aStarState;

public:
	Scene_AStar();
	~Scene_AStar();

	void Init();
	void Release();
	void Update();
	void Render();

	void TileComposition(); //타일배치
	void TileInitializing(); //배치후 
	//
	void AddOpenList();
	void CalculateH();
	void CalculateF();
	void AddCloseList();
	void CheckArrive();
	//
	void ShowWay(aStarTile* tile);

};

