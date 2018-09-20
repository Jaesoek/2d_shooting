#pragma once
class RenderTarget
{
private:
	LPDIRECT3DTEXTURE9 pRenderTexture;
	LPDIRECT3DSURFACE9 pRenderSurface;
	
	LPDIRECT3DSURFACE9 pDeviceTargetSurface;
	LPDIRECT3DSURFACE9 pDeviceDepthAndStencil;


public:
	RenderTarget();
	~RenderTarget();

	void Init(); //�ʱ�ȭ
	void Release(); //���� 
	void BeginScene(); //���� Ÿ�� ����
	void EndScene(); //���� 
	void SaveTexture(); //��ũ�� ��
	void SetTexture();
	LPDIRECT3DTEXTURE9 GetTexture()
	{
		return pRenderTexture;
	}
};

