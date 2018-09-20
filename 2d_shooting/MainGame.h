#pragma once
#include "RenderTarget.h"
#include "MiniMap.h"


class MainGame
{
private:					//����
	class IScene* nowScene;

	RenderTarget* target;
	MiniMap* minimap;
	
public:						//�Լ�
	MainGame();
	~MainGame();

	void Init(HWND hWnd);	//�ʱ�ȭ
	void Release();			//����(�̹��� �߰��� ���)
	void Update();			//Ű����, ���콺 �Է� ó�� �� ���
	void UpdateGUI();
	void Render();			//���� �� 
	void RenderTargets();
///////////////////////////////////////////////////////////////////

private:
	HWND hWnd;
	POINT ptMouse;
public:
	//���� ���ν��� (���ΰ��ӿ��� �޼��� ó����)
	LRESULT MainProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

