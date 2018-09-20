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

	//result : 충돌 여부
	//rc	 : 출돌용 사각형
	//center : 원의 중심점
	//radius : 원의 반지름 
	static bool IsConstainCircle(
		RECT rc, POINT center, float radius
	);
	//center1, center2 : 원의 중심좌표
	//radius1, radius2 : 원의 반지름 
	static bool IsConstainCircle(
		POINT center1, float radius1,
		POINT center2, float radius2);
	//rect   : 반환용 (충돌후 생기는 사각형) 
	//comp1  : 충돌용 1
	//comp2  : 충돌용
	//return : 충돌 여부 
	static bool IsConstainRect(RECT* rect , RECT comp1, RECT comp2);
	//comp   : 충돌용 사각형 
	//point  : 충돌용 점 
	//return : 충돌 여부 
	static bool IsConstainPoint(RECT comp, POINT point);
	static bool IsConstainPoint(D3DXVECTOR2* comp, POINT point);

	//startLine1 : 1번선 시작 
	//endLine1 : 1번선 끝부분 
	//return : 충돌 여부 
	static bool IsCrossLine(D3DXVECTOR2 startLine1,
		D3DXVECTOR2 endLine1, D3DXVECTOR2 startLine2, D3DXVECTOR2 endLine2);

	static bool IsCrossLineOBB(D3DXVECTOR2* OBBBox1, D3DXVECTOR2* OBBBox2);

};

