#include "stdafx.h"
#include "Intersect.h"


Intersect::Intersect()
{

}


Intersect::~Intersect()
{
}

float Intersect::GetDistance(float x1, float y1, float x2, float y2)
{
	float deltaX = abs(x1 - x2);
	float deltaY = abs(y1 - y2);

	float distancePow2 = deltaX * deltaX + deltaY * deltaY;

	float distance = sqrtf(distancePow2);
	return distance;
}

float Intersect::GetAngle(POINT position1, POINT position2)
{
	float x = position2.x - position1.x;
	float distance = GetDistance(
		position1.x, position1.y, position2.x, position2.y);
	float angle = acosf(x / distance);

	if (position2.y > position1.y)
	{
		angle = 2 * PI - angle;
		if (angle >= 2 * PI) angle -= 2 * PI;
	}

	return angle;
}

float Intersect::GetAngle(D3DXVECTOR2 velocity)
{
	float angle = acosf(velocity.x);
	if (velocity.y > 0)
	{
		angle = 2 * PI - angle;
		if (angle >= 2 * PI) angle -= 2 * PI;
	}
	return angle;
}

bool Intersect::IsConstainCircle(RECT rc, POINT center, float radius)
{
	//면하고 충돌시 
	if (rc.left < center.x && center.x < rc.right
		|| rc.top < center.y && center.y < rc.bottom)
	{
		RECT temp;
		temp.left = rc.left - radius;
		temp.right = rc.right + radius;
		temp.top = rc.top - radius;
		temp.bottom = rc.bottom + radius;

		return IsConstainPoint(temp, center);
	}
	//꼭지점 충돌 
	else
	{
		POINT temp = { rc.left,rc.top };
		if (IsConstainCircle(center, radius, temp, 0)) return true;
		temp = { rc.left,rc.bottom };
		if (IsConstainCircle(center, radius, temp, 0)) return true;
		temp = { rc.right,rc.top };
		if (IsConstainCircle(center, radius, temp, 0)) return true;
		temp = { rc.right,rc.bottom };
		if (IsConstainCircle(center, radius, temp, 0)) return true;
	}
	return false;
}

bool Intersect::IsConstainCircle(POINT center1, float radius1, POINT center2, float radius2)
{
	float distance = GetDistance(center1.x, center1.y,
		center2.x, center2.y);
	bool result = false;
	if ((radius1 + radius2) > distance)
	{
		result = true;
	}
	return result;
}

bool Intersect::IsConstainRect(RECT * rect, RECT comp1, RECT comp2)
{

	bool isVertical = false;
	bool isHorizontal = false;

	if (comp1.left <= comp2.right && comp1.right >= comp2.left)
	{
		isHorizontal = true;

		if (rect != NULL)
		{
			rect->left = (comp1.left >= comp2.left) ? comp1.left : comp2.left;
			rect->right = (comp1.right <= comp2.right) ? comp1.right : comp2.right;
		}
	}

	if (comp1.top <= comp2.bottom && comp1.bottom >= comp2.top)
	{
		isVertical = true;
		if (rect != NULL)
		{
			rect->top = max(comp1.top, comp2.top);
			rect->bottom = min(comp1.bottom, comp2.bottom);
		}
	}

	if (isVertical && isHorizontal)
	{
		return true;
	}

	if (rect != NULL)
		*rect = { 0,0,0,0 };

	return false;
}

bool Intersect::IsConstainPoint(RECT comp, POINT point)
{
	bool result = true;

	//int num += 10; -> num = num + 10
	//A &= B -> A = A && B
	result &= comp.left < point.x;
	result &= comp.right > point.x;
	result &= comp.top < point.y;
	result &= comp.bottom > point.y;

	return result;
}

bool Intersect::IsConstainPoint(D3DXVECTOR2 * comp, POINT point)
{
	bool result = true;

	//int num += 10; -> num = num + 10
	//A &= B -> A = A && B
	result &= comp[0].x < point.x;
	result &= comp[1].x > point.x;
	result &= comp[1].y < point.y;
	result &= comp[2].y > point.y;

	return result;
}

bool Intersect::IsCrossLine(D3DXVECTOR2 startLine1, D3DXVECTOR2 endLine1, D3DXVECTOR2 startLine2, D3DXVECTOR2 endLine2)
{
	D3DXVECTOR2 vec1 = endLine1  - startLine1;
	D3DXVECTOR2 vec2 = startLine2  - startLine1;
	D3DXVECTOR2 vec3 = endLine2  - startLine1;

	D3DXVec2Normalize(&vec1,&vec1);	//길이를 1로만들어 주는 녀석
	D3DXVec2Normalize(&vec2, &vec2);//normalize(정규화)
	D3DXVec2Normalize(&vec3, &vec3);

	D3DXVECTOR3 result1;
	D3DXVECTOR3 result2;
	D3DXVec3Cross(
		&result1,
		new D3DXVECTOR3(vec1.x, vec1.y, 0.0f),
		new D3DXVECTOR3(vec2.x, vec2.y, 0.0f)
	);
	D3DXVec3Cross(
		&result2,
		new D3DXVECTOR3(vec1.x, vec1.y, 0.0f),
		new D3DXVECTOR3(vec3.x, vec3.y, 0.0f)
	);

	bool final = true;
	
	D3DXVec3Normalize(&result1, &result1);
	D3DXVec3Normalize(&result2, &result2);
	final &= !FLOATEQAUL(result1.z, result2.z);

	vec1 = endLine2 - startLine2;
	vec2 = startLine1 - startLine2;
	vec3 = endLine1 - startLine2;

	D3DXVec2Normalize(&vec1, &vec1);	//길이를 1로만들어 주는 녀석
	D3DXVec2Normalize(&vec2, &vec2);//normalize(정규화)
	D3DXVec2Normalize(&vec3, &vec3);

	D3DXVec3Cross(
		&result1,
		new D3DXVECTOR3(vec1.x, vec1.y, 0.0f),
		new D3DXVECTOR3(vec2.x, vec2.y, 0.0f)
	);
	D3DXVec3Cross(
		&result2,
		new D3DXVECTOR3(vec1.x, vec1.y, 0.0f),
		new D3DXVECTOR3(vec3.x, vec3.y, 0.0f)
	);
	D3DXVec3Normalize(&result1, &result1);
	D3DXVec3Normalize(&result2, &result2);
	final &= !FLOATEQAUL(result1.z, result2.z);

	return final;
}

bool Intersect::IsCrossLineOBB(D3DXVECTOR2 * OBBBox1, D3DXVECTOR2 * OBBBox2)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			bool result = IsCrossLine(
				OBBBox1[i], OBBBox1[i + 1], OBBBox2[j], OBBBox2[j + 1]);
			if (result == true) return true;
		}
	}
	return false;
}

