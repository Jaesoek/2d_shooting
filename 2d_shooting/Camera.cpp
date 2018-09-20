#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::Init(int width, int height)
{
	D3DXMatrixOrthoOffCenterLH(
		&matProjection,
		0, width,
		height, 0,
		0.0f, 1.0f
	);
	D3DXMatrixLookAtLH(
		&matView,
		&this->position,
		&this->axisZ,
		&this->axisY
	);
}

void Camera::Update()
{
	D3DXMatrixLookAtLH(
		&matView,
		&this->position,
		&(position + axisZ),
		&this->axisY
	);
}

void Camera::SetDeviceMatrix()
{
	DEVICE->SetTransform(D3DTS_VIEW, &matView);
	DEVICE->SetTransform(D3DTS_PROJECTION, &matProjection);
}
