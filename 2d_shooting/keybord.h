#pragma once
//싱글톤 패턴
//객체를 1개만 만들어서 관리하겠다.
//=> new 1번만 사용하겠다. 
//객체 -> 데이터 + 행동 
#include <bitset>

#define KEYMAX 256
class keybord
{
private:
	bitset<KEYMAX> keyUp;
	bitset<KEYMAX> keyDown;

public:
	//키를 한번만 눌렸느냐? 
	bool GetKeyDown(int key);
	//키를 계속 누르고 있느냐?
	bool GetKey(int key);
	//키를 눌렸다 띄었냐?
	bool GetKeyUp(int key);
	bool ToggleKey(int key);

	//싱글톤
private:
	keybord();
	~keybord();
	static keybord* instance;
public:
	static keybord* Get();
	static void Destory();

};

#define Input keybord::Get()

