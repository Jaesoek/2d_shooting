#include "stdafx.h"
#include "Font.h"

Font* Font::instance = NULL;

Font::Font()
{
	D3DXCreateFont(
		D2D::GetDevice(),	//����̽�
		18,					//������ ����
		0,					//������ �ʺ�
							//�ɼ��� ���� ������ ����
		FW_BOLD,			//��Ʈ �β�
		1,					//�Ӹ� ����
		FALSE,				//���ڸ� ����(����)
		DEFAULT_CHARSET,	//ĳ���� set(
		OUT_DEFAULT_PRECIS,	//�ܰ� ó�����
		DEFAULT_QUALITY,	//����Ƽ
		DEFAULT_PITCH | FF_DONTCARE, //�ɼ�
		"���� ���",			//��Ʈ �̸�
		&pDefaultFont		//������ ����
	);
	//API -> ������½� ���� ���� �� ���� rc
	//Direct-> rc����� rc�ȿ� ���� ���
	//DEFAULT_PITCH -> ���� ���� ���� 
	//FF_DONTCARE -> ���� ���� �� �� ������

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
		str.c_str(), //��� �ϰ� ���� ����
		-1,			 //����� ������ ����,
		&rc,
		DT_LEFT | DT_NOCLIP,
		color
	);
	//DT_NOCLIP -> rectũ�� ������� ��� 
	//DT_LEFT ->���� ���� 
}

void Font::PrintText(D3DXCOLOR color, int x, int y, char * str, ...)
{
	char text[64];
	//va_list ap;
	//va_start(ap, str);
	//vsprintf(text + strlen(text), str, ap);
	//va_end(ap);
	this->PrintText(str, x, y, color);


}
