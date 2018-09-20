#pragma once
#include "Texture.h"
class Sprite
{
private:
	static Sprite * instance;
	map<string, Texture*> textures;

	//map�� �����͸� �����ϴ� �༮
	//�̸� ���� �ϰ� ������ ���?
	Sprite();
	~Sprite();
public:
	static Sprite* Get();
	static void Destroy();

	void Init(string key, string fileName);
	void Init(string key, string fileName, D3DXCOLOR colorKey);
	void Init(string key, string fileName, int frameX, int frameY);

	void Release();

	void Render(string key);	//0,0 ��ġ���� ���
	void Render(string key, int width, int heihgt);
	void Render(string key, float posX, float posY);
	void Render(string key, float posX, float posY, float angle, RECT rc);
	void Render(string key, float posX, float posY, int width, int heihgt);
	void Render(string key, float posX, float posY, int width, int heihgt, int frameX, int frameY);
	void Render(string key, float posX, float posY, float angle, float pivotX = 0.0f, float pivotY = 0.0f);
	/*
		pivot : �߽���
		   (0,0)
			------
			|	 |
			------
				 (1,1)
	*/
public:
	Texture * FindTexture(string key);
	RECT GetRect(string key);
};

#define IMAGE Sprite::Get()