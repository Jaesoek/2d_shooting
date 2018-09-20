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

	void Init(); //초기화
	void Release(); //삭제 
	void BeginScene(); //랜더 타겟 시작
	void EndScene(); //종료 
	void SaveTexture(); //스크린 샷
	void SetTexture();
	LPDIRECT3DTEXTURE9 GetTexture()
	{
		return pRenderTexture;
	}
};

