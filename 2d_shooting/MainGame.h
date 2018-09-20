#pragma once
#include "RenderTarget.h"
#include "MiniMap.h"


class MainGame
{
private:					//변수
	class IScene* nowScene;

	RenderTarget* target;
	MiniMap* minimap;
	
public:						//함수
	MainGame();
	~MainGame();

	void Init(HWND hWnd);	//초기화
	void Release();			//삭제(이미지 추가후 사용)
	void Update();			//키보드, 마우스 입력 처리 및 계산
	void UpdateGUI();
	void Render();			//랜더 만 
	void RenderTargets();
///////////////////////////////////////////////////////////////////

private:
	HWND hWnd;
	POINT ptMouse;
public:
	//메인 프로시져 (메인게임에서 메세지 처리용)
	LRESULT MainProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

