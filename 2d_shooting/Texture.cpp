#include "stdafx.h"
#include "Texture.h"

Texture* Texture::instance = NULL;

Texture::Texture()
{

}

Texture::~Texture()
{
	auto iter = textures.begin();
	for (iter; iter != textures.end();)
	{
		if (iter->second != NULL)
		{
			SAFE_RELEASE(iter->second);
			iter = textures.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	textures.clear();
}

Texture * Texture::Get()
{
	if (instance == NULL)
		instance = new Texture;
	return instance;
}

void Texture::Destroy()
{
	if (instance != NULL)
		SAFE_DELETE(instance);
}

void Texture::Init(string key, string fileName)
{
	if (textures.count(key) > 0)
	{
		assert(false);
	}
	LPDIRECT3DTEXTURE9 pTex;
	D3DXCreateTextureFromFile(
		DEVICE,
		fileName.c_str(),
		&pTex
	);
	textures[key] = pTex;
}

LPDIRECT3DTEXTURE9 Texture::GetTexture(string key)
{
	auto iter = textures.find(key);
	return iter->second;
}

void Texture::SetDeivceTexture(string key)
{
	if (textures.count(key) < 1)
	{
		assert(false);
	}
	DEVICE->SetTexture(0, textures[key]);
}
