#pragma once
#include "Object.h"

//변수 생성시 
class Bullet : public Object
{
protected:
	D3DXVECTOR3 StartPos;
	float radius;	//반지름
	float speed;	//속도
	bool fire;		//발사 여부
	float angle;	//처음 발사될때 각도 
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