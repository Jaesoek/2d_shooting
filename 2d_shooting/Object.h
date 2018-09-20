#pragma once
#include "Rect.h"
#include "Collider.h"
#include "Transform.h"
class Object
{
protected:
	Rect* rc;
	D3DXVECTOR2 uv[4];
	LPDIRECT3DVERTEXBUFFER9 vb;
	LPDIRECT3DINDEXBUFFER9 ib;

	LPDIRECT3DTEXTURE9 pTex;
	Transform* trans;
	Collider* collider;

	bool isActive = false;
	DWORD dwStart;
	DWORD dwEnd;
public:
	Object();
	virtual ~Object();

	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void SetActive(bool isActive);
	GETTER_SETTER(LPDIRECT3DTEXTURE9,Texture, pTex);
	Transform* GetTrans() { return trans; }
	Collider* Getcollider() { return collider; }
	void TransformGui() { trans->UpdateGui(); }

	void UpdateCollider();
protected:
	void CreateVertexBuffer();
	void CreateIndexBuffer();

	virtual	void EnableInit(); //비활성-> 활성화
	virtual void DisableInit(); //활성화-> 비활설 
	virtual void EnableUpdate();
	virtual void DisableUpdate();
	virtual void EnableRender();


};

