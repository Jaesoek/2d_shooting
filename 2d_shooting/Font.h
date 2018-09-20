#pragma once
class Font
{
private:
	LPD3DXFONT pDefaultFont;
	static Font* instance;

	Font();
	~Font();
public:
	static Font* Get();
	static void Destroy();
	void PrintText(string str, int x, int y,
		D3DCOLOR color);
};


