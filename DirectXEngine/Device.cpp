#include "pch.h"
#include "Device.h"
#include "CWindow.h"

void Device::Init(WindowInfo& info)
{
	m_pDevice = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));			// �ʱ�ȭ
	d3dpp.Windowed = info.windowed;				// â���
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// ��?��
	d3dpp.hDeviceWindow = info.hWnd;			// �ڵ�
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;	// ����ü�� ���˰�	 ���ĵ� �����غ��ô�.
	d3dpp.BackBufferWidth = info.width;			// ��
	d3dpp.BackBufferHeight = info.height;		// ��

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
