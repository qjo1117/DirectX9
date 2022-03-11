#include "pch.h"
#include "Device.h"
#include "CWindow.h"

void Device::Init(WindowInfo& info)
{
	m_pDevice = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));			// 초기화
	d3dpp.Windowed = info.windowed;				// 창모드
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// 몰?루
	d3dpp.hDeviceWindow = info.hWnd;			// 핸들
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;	// 스왑체인 포맷값	 알파도 지원해봅시다.
	d3dpp.BackBufferWidth = info.width;			// 알
	d3dpp.BackBufferHeight = info.height;		// 음

	m_pDevice->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		info.hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pDxgi);
	

}

void Device::Clear()
{
	SAFEDELETE(m_pDevice);
	SAFEDELETE(m_pDxgi);
}
