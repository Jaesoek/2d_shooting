#include "stdafx.h"
#include "Transform.h"


Transform::Transform()
{
	position = D3DXVECTOR3(0, 0, 0);
	angle = D3DXVECTOR3(0, 0, 0);
	scale = D3DXVECTOR3(1, 1, 1);
	axisX = D3DXVECTOR3(1, 0, 0);
	axisY = D3DXVECTOR3(0, 1, 0);
	axisZ = D3DXVECTOR3(0, 0, 1);
}


Transform::~Transform()
{
}

void Transform::MulMatrix(Transform * trans)
{
	this->matFinal =  this->matFinal *  trans->GetWorld();
}

void Transform::SetWorldPosition(float x, float y)
{
	this->position.x = x;
	this->position.y = y;

	this->UpdateWorld();
}

void Transform::SetRotate(float angle)
{
	D3DXVECTOR3 worldAxis[3];
	for (int i = 0; i < 3; i++)
		worldAxis[i] = axis[i];
	this->angle.z += angle;

	D3DXMATRIX rot;
	D3DXMatrixRotationZ(&rot, D3DXToRadian(angle));
	for (int i = 0; i < 3; i++)
		D3DXVec3TransformNormal(this->axis + i,
			worldAxis + i, &rot);
	this->UpdateWorld();
}

void Transform::MovePositionLocal(float x, float y)
{
	//자신의 이동 축 
	
	D3DXVECTOR3 move(0, 0, 0);
	move += this->axisX * x;
	move -= this->axisY * y;

	this->SetWorldPosition(position.x + move.x, position.y + move.y);
}

void Transform::MovePositionWorld(float x, float y)
{
	D3DXVECTOR3 move(0, 0, 0);
	move += D3DXVECTOR3(1, 0, 0) * x;
	move += D3DXVECTOR3(0, -1, 0) * y;
	this->SetWorldPosition(position.x + move.x, position.y + move.y);

}

void Transform::SetScaling(float x, float y)
{
	scale.x *= x;
	scale.y *= y;
	this->UpdateWorld();
}

void Transform::LookAtPosition(const D3DXVECTOR3 & target)
{
	D3DXVECTOR3 worldPos = position;
	D3DXVECTOR3 dir = target - worldPos;
	D3DXVec3Normalize(&dir, &dir);

	D3DXVECTOR3 newRight;
	axisY = dir;
	D3DXVec3Cross(&newRight, &dir, &axisZ);
	axisX = newRight;
	this->UpdateWorld();
}

void Transform::DefaultControl()
{
	if (keybord::Get()->GetKey('W'))
		this->MovePositionLocal(0, 5);
	if (keybord::Get()->GetKey('S'))
		this->MovePositionLocal(0, -5);
	//if (keybord::Get()->GetKey('A'))
	//	this->MovePositionLocal(0, 5);
	//if (keybord::Get()->GetKey('D'))
	//	this->MovePositionLocal(0, -5);

	if (keybord::Get()->GetKey('A'))
		this->SetRotate(-1.0f);
	if (keybord::Get()->GetKey('D'))
		this->SetRotate(1.0f);
}

void Transform::UpdateWorld()
{
	//최종 world 행령 계산 
	
	D3DXVECTOR3 right = this->axisX * this->scale.x;
	D3DXVECTOR3 up = this->axisY * this->scale.y;
	D3DXVECTOR3 forward = this->axisZ * this->scale.z;

	D3DXMatrixIdentity(&matFinal);

	memcpy(&this->matFinal._11, &right, sizeof(D3DXVECTOR3));
	memcpy(&this->matFinal._21, &up, sizeof(D3DXVECTOR3));
	memcpy(&this->matFinal._31, &forward, sizeof(D3DXVECTOR3));
	memcpy(&this->matFinal._41, &position, sizeof(D3DXVECTOR3));
}

void Transform::SetDeviceTransform()
{
	DEVICE->SetTransform(D3DTS_WORLD, &this->matFinal);
}

void Transform::UpdateGui()
{

	if (ImGui::Checkbox("ShowTransform", &isShow))
	if (ImGui::BeginChild("Transform", ImVec2(0,0), &isShow))
	{
		ImGui::LabelText(" ", "Transform");
		ImGui::InputFloat3("Position", position);
		ImGui::InputFloat3("Rotation", angle);
		ImGui::InputFloat3("Scale", scale);
		ImGui::Separator();
		ImGui::EndChild();
	}
}
