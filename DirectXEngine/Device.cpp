#include "pch.h"
#include "Device.h"

void Device::Init(HWND hWnd)
{
	m_pDevice = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = true;			// â���
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// ��?��
	d3dpp.hDeviceWindow = hWnd;		// �ڵ�

	m_pDevice->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pDxgi);


}

void Device::Clear()
{
	SAFEDELETE(m_pDevice);
	SAFEDELETE(m_pDxgi);
}
