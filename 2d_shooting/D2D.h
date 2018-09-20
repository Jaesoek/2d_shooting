#pragma once
//Device -> 생성해서 사용
//싱글톤 패턴으로 D2D 클래스를 하나만 생성 후 관리

class D2D
{
private:
	LPDIRECT3D9 d3d = NULL; 
	//Direct 사용하겠다 + device 생성하기 위한 변수
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
