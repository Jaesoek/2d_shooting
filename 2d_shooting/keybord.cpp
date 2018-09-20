#include "stdafx.h"
#include "keybord.h"

keybord* keybord::instance = NULL;
bool keybord::GetKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (keyDown[key] == false)
		{
			keyDown.set(key, true);
			return true;
		}
	}
	else
	{
		keyDown.set(key, false);
	}
	return false;
}
bool keybord::GetKey(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	return false;
}
bool keybord::GetKeyUp(int key)
{
	return false;
}
bool keybord::ToggleKey(int key)
{
	return false;
}


keybord::keybord()
{
	for (int i = 0; i < KEYMAX;i++)
	{
		keyDown.set(i, false);
		keyUp.set(i, false);
	}
}
keybord::~keybord()
{
}

keybord * keybord::Get()
{
	if (instance == NULL)
		instance = new keybord;
	return instance;
}

void keybord::Destory()
{
	if (instance != NULL)
	{
		delete instance;
		instance = NULL;
	}
}
