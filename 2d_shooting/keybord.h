#pragma once
//�̱��� ����
//��ü�� 1���� ���� �����ϰڴ�.
//=> new 1���� ����ϰڴ�. 
//��ü -> ������ + �ൿ 
#include <bitset>

#define KEYMAX 256
class keybord
{
private:
	bitset<KEYMAX> keyUp;
	bitset<KEYMAX> keyDown;

public:
	//Ű�� �ѹ��� ���ȴ���? 
	bool GetKeyDown(int key);
	//Ű�� ��� ������ �ִ���?
	bool GetKey(int key);
	//Ű�� ���ȴ� �����?
	bool GetKeyUp(int key);
	bool ToggleKey(int key);

	//�̱���
private:
	keybord();
	~keybord();
	static keybord* instance;
public:
	static keybord* Get();
	static void Destory();

};

#define Input keybord::Get()

