#include "stdafx.h"
#include "Font.h"

Font* Font::instance = NULL;

Font::Font()
{
	D3DXCreateFont(
		D2D::GetDevice(),	//디바이스
		18,					//글자의 높이
		0,					//글자의 너비
							//옵션을 통해 비율을 조절
		FW_BOLD,			//폰트 두께
		1,					//밉맵 설정
		FALSE,				//이텔릭 여부(기울기)
		DEFAULT_CHARSET,	//캐릭터 set(
		OUT_DEFAULT_PRECIS,	//외각 처리방식
		DEFAULT_QUALITY,	//퀄리티
		DEFAULT_PITCH | FF_DONTCARE, //옵션
		"맑은 고딕",			//폰트 이름
		&pDefaultFont		//데이터 저장
	);
	//API -> 글자출력시 글자 길이 에 맞춰 rc
	//Direct-> rc만들고 rc안에 글자 출력
	//DEFAULT_PITCH -> 글자 사이 간격 
	//FF_DONTCARE -> 글자 높이 폭 을 맞춰줌

}


Font::~Font()
{
	SAFE_RELEASE(pDefaultFont);
}

Font * Font::Get()
{
	if (instance == NULL)
		instance = new Font;
	return instance;
}

void Font::Destroy()
{
	if (instance != NULL)
		SAFE_DELETE(instance);
}

void Font::PrintText(string str, int x, int y, D3DCOLOR color)
{
	RECT rc = { x, y, 0,0 };
	pDefaultFont->DrawTextA
	(
		NULL,
		str.c_str(), //출력 하고 싶은 글자
		-1,			 //출력할 글자의 길이,
		&rc,
		DT_LEFT | DT_NOCLIP,
		color
	);
	//DT_NOCLIP -> rect크기 상관없이 출력 
	//DT_LEFT ->왼쪽 정렬 
}
