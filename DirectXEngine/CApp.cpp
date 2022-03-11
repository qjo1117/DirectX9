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
	LPDIRECT3DDEVICE9 dxgi = m_pDevice->GetDXGI();	// 맵핑
	dxgi->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);
	dxgi->BeginScene();

	// TODO : 그려주면 된다고 합니다.

	dxgi->EndScene();
	dxgi->Present(nullptr, nullptr, nullptr, nullptr);

	return true;
}

bool CApp::End()
{
	return true;
}
