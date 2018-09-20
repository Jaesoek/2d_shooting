#pragma once
//Device -> �����ؼ� ���
//�̱��� �������� D2D Ŭ������ �ϳ��� ���� �� ����

class D2D
{
private:
	LPDIRECT3D9 d3d = NULL; 
	//Direct ����ϰڴ� + device �����ϱ� ���� ����
	static LPDIRECT3DDEVICE9 device;
	static D2D* instance;
	D2D(HWND hwnd);
	~D2D();
public:
	static LPDIRECT3DDEVICE9 GetDevice(
	HWND hwnd = NULL);
	static void Destroy();

};

#define DEVICE D2D::GetDevice()
