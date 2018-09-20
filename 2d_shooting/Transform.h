#pragma once
class Transform
{
protected:
	D3DXVECTOR3 position;
	D3DXVECTOR3 angle;
	D3DXVECTOR3 scale;
	union
	{
		struct
		{
			D3DXVECTOR3 axisX;
			D3DXVECTOR3 axisY;
			D3DXVECTOR3 axisZ;
		};
		struct
		{
			D3DXVECTOR3 axis[3];
		};
	};

	D3DXMATRIX matFinal;

	bool isShow = true;
public:
	Transform();
	~Transform();

	void MulMatrix(Transform* trans);

	void SetWorldPosition(float x, float y);
	void SetRotate(float angle);
	void MovePositionLocal(float x, float y);
	void MovePositionWorld(float x, float y);
	void SetScaling(float x, float y);
	void LookAtPosition(const D3DXVECTOR3& target);

	void DefaultControl();
	void UpdateWorld();

	void SetDeviceTransform();
	void UpdateGui();
	D3DXMATRIX GetWorld() { return this->matFinal; }

	D3DXVECTOR3 GetPosition() { return position; }
	float GetAngle() { return angle.z; }
};

