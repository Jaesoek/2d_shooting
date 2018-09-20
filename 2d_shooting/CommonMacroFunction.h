#pragma once

//FileName : CommonMacroFunction

//===================================================
//	   ## 필요한 부분은 직접 만들어서 추가 할것 ##
//===================================================

inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}
inline void DrawRect(HDC hdc, RECT rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

inline RECT RectMake(int x, int y, int width, int height)
{
	RECT result = { x, y, x + width, y + height };
	return result;
}

inline RECT AddRect(RECT* rect, int x, int y,bool useFrame = false)
{
	int width = rect->right - rect->left;
	int height = rect->bottom - rect->top;
	if (useFrame)
	{
		(*rect).left = x * width;
		(*rect).top = y * height;
		(*rect).right = (x + 1) *  width;
		(*rect).bottom = (y + 1) * height;
	}
	else
	{
		(*rect).left = x;
		(*rect).top = y;
		(*rect).right = x + width;
		(*rect).bottom = y + height;
	}
	RECT temp = *rect;
	return temp;
}