#include "pch.h"
#include "CApp.h"
#include "Device.h"

bool CApp::Begin()
{
	CWindow::Begin();

	return true;
}

bool CApp::Update()
{
	CWindow::Update();

	return true;
}

bool CApp::Render()
{
	LPDIRECT3DDEVICE9 dxgi = m_pDevice->GetDXGI();	// ����
	dxgi->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);
	dxgi->BeginScene();

	// TODO : �׷��ָ� �ȴٰ� �մϴ�.

	dxgi->EndScene();
	dxgi->Present(nullptr, nullptr, nullptr, nullptr);

	return true;
}

bool CApp::End()
{
	return true;
}
