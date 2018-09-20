#pragma once


#define PI 3.141592654f
#define EPSLON 0.0001f
#define FLOATEQAUL(a,b) (abs(a - b) < EPSLON)

class Intersect
{
public:
	Intersect();
	~Intersect();
	static float GetDistance(float x1, float y1, float x2, float y2);
	static float GetAngle(POINT position1, POINT position2);
	static float GetAngle(D3DXVECTOR2 velocity);

	//result : �浹 ����
	//rc	 : �⵹�� �簢��
	//center : ���� �߽���
	//radius : ���� ������ 
	static bool IsConstainCircle(
		RECT rc, POINT center, float radius
	);
	//center1, center2 : ���� �߽���ǥ
	//radius1, radius2 : ���� ������ 
	static bool IsConstainCircle(
		POINT center1, float radius1,
		POINT center2, float radius2);
	//rect   : ��ȯ�� (�浹�� ����� �簢��) 
	//comp1  : �浹�� 1
	//comp2  : �浹��
	//return : �浹 ���� 
	static bool IsConstainRect(RECT* rect , RECT comp1, RECT comp2);
	//comp   : �浹�� �簢�� 
	//point  : �浹�� �� 
	//return : �浹 ���� 
	static bool IsConstainPoint(RECT comp, POINT point);
	static bool IsConstainPoint(D3DXVECTOR2* comp, POINT point);

	//startLine1 : 1���� ���� 
	//endLine1 : 1���� ���κ� 
	//return : �浹 ���� 
	static bool IsCrossLine(D3DXVECTOR2 startLine1,
		D3DXVECTOR2 endLine1, D3DXVECTOR2 startLine2, D3DXVECTOR2 endLine2);

	static bool IsCrossLineOBB(D3DXVECTOR2* OBBBox1, D3DXVECTOR2* OBBBox2);

};

