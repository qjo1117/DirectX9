#pragma once





class Device
{
public:
	void Init(class WindowInfo& hWnd);
	void Clear();

	LPDIRECT3D9 GetDevice() { return m_pDevice; }			//d3d
	LPDIRECT3DDEVICE9 GetDXGI() { return m_pDxgi; }			//d3ddv

private:
	LPDIRECT3D9 m_pDevice = nullptr;			//d3d
	LPDIRECT3DDEVICE9 m_pDxgi = nullptr;		//d3ddv
};

