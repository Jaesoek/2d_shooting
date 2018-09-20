#pragma once
#include "Object.h"

//���� ������ 
class Bullet : public Object
{
protected:
	D3DXVECTOR3 StartPos;
	float radius;	//������
	float speed;	//�ӵ�
	bool fire;		//�߻� ����
	float angle;	//ó�� �߻�ɶ� ���� 
public:
	Bullet();
	virtual ~Bullet();

	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();
public:
	virtual void SetDamage(Collider* target, int* hp);
	virtual void MoveBullet();
	virtual void Fire(D3DXVECTOR3 pos, float angle);
	bool GetBool() { return fire; }
};

class Missile : public Bullet
{
public:
	void Init(int width, int height);
};