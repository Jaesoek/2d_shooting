#pragma once

class IScene
{
protected:
	class Camera* mainCamera;

public:
	IScene();
	~IScene();

	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	void UpdateGUI();

protected:
	virtual	void SetInterface() PURE;
	bool isInterfaceShow = false;
	bool isDemoShow = false;
	bool isSystemShow = false;
};

