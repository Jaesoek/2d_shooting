#pragma once
class Texture
{
private:
	//IDirect3DTexture9* tex;
	map<string,LPDIRECT3DTEXTURE9> textures;
	
	Texture();
	~Texture();

	static Texture* instance;
public:
	static Texture* Get();
	static void Destroy();

	void Init(string key, string fileName);
	LPDIRECT3DTEXTURE9 GetTexture(string key);
	void SetDeivceTexture(string key);
};

