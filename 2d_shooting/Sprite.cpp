#include "stdafx.h"
#include "Sprite.h"

Sprite* Sprite::instance = NULL;

Sprite::Sprite()
{
}
Sprite::~Sprite(){}

Sprite * Sprite::Get()
{
	if (instance == NULL)
		instance = new Sprite;

	return instance;
}
void Sprite::Destroy()
{
	if (instance != NULL)
		SAFE_DELETE(instance);
}

void Sprite::Init(string key, string fileName)
{
	if (textures.count(key) > 0)
	{
		assert(false && "Already have same key Value");
		return;
	}

	Texture* temp = new Texture();
	temp->Init(fileName.c_str());
	textures[key] = temp;
}

void Sprite::Init(string key, string fileName, D3DXCOLOR colorKey)
{
	if (textures.count(key) > 0)
	{
		assert(false && "Already have same key Value");
		return;
	}

	Texture* temp = new Texture();
	temp->Init(fileName.c_str(), colorKey);
	textures[key] = temp;
}

void Sprite::Init(string key, string fileName, int frameX, int frameY)
{
	if (textures.count(key) > 0)
	{
		assert(false && "Already have same key Value");
		return;
	}

	Texture* temp = new Texture();
	temp->Init(fileName.c_str(), frameX,frameY);
	textures[key] = temp;
}

void Sprite::Release()
{
	
	auto iter = textures.begin();
	for (; iter != textures.end(); )
	{
		if (iter->second != NULL)
		{
			SAFE_DELETE(iter->second);
		}
		else
		{
			iter++;
		}
	}
	textures.clear();
}

void Sprite::Render(string key)
{
	FindTexture(key)->Render();
}

void Sprite::Render(string key, int width, int heihgt)
{
	FindTexture(key)->Render(width,heihgt);
}

void Sprite::Render(string key, float posX, float posY)
{
	FindTexture(key)->Render(posX, posY);
}

void Sprite::Render(string key, float posX, float posY, float angle, RECT rc)
{
	FindTexture(key)->Render(posX, posY,angle,rc);
}

void Sprite::Render(string key, float posX, float posY, int width, int heihgt)
{
	FindTexture(key)->Render(posX, posY, width, heihgt);

}

void Sprite::Render(string key, float posX, float posY, int width, int heihgt, int frameX, int frameY)
{
	FindTexture(key)->Render(posX, posY, width, heihgt,frameX,frameY);
}

void Sprite::Render(string key, float posX, float posY, float angle, float pivotX, float pivotY)
{
	FindTexture(key)->Render(posX, posY, angle, pivotX, pivotY);
}

Texture * Sprite::FindTexture(string key)
{
	if (textures.count(key) < 1)
		assert(false && "키 값이 존재 하지 않습니다.");

	return textures[key];
}

RECT Sprite::GetRect(string key)
{
	return FindTexture(key)->GetRect();
}
