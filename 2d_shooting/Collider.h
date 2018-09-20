#pragma once
class Collider
{
private:
	Rect rc;
	D3DXVECTOR2 AABBBox[5];
	D3DXVECTOR2 OBBBox[5];

public:
	Collider();
	Collider(RECT rc);
	~Collider();

	void SetAABBBox(RECT rc, const D3DXMATRIX& matWorld);
	void Render();

	D3DXVECTOR2* GetOBBBox() { return OBBBox; }
	RECT GetRect() { return rc; }
};

