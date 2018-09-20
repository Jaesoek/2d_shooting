#pragma once
#include "Transform.h"
class Camera : public Transform
{
private:
	int width;
	int height;

	D3DXMATRIX matView;
	D3DXMATRIX matProjection; 
	//projection 투영 -> 
	//3D좌표로 물체를 2D  
public:
	Camera();
	~Camera();

	void Init(int width, int height);
	void Update();
	void SetDeviceMatrix();

	D3DXMATRIX GetView() { return matView; }
	D3DXMATRIX GetProjection() { return matProjection; }
};

