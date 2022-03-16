#pragma once

#include <Windows.h>
#include <string>
#include <memory>
#include <vector>
#include <d3d9.h>

#include "Type.h"

using namespace std;

#define MAX_LOADSTRING 100


struct WindowInfo
{
public:
	int width = 0;
	int height = 0;
	bool isLoop = true;
	bool windowed = true;
	uint32 clearColor = D3DCOLOR_XRGB(100, 100, 100);

	HWND hWnd = nullptr;
	HINSTANCE hInst = 0;

	std::wstring title;
};




class CWindow
{
public:
	/* ----- SingleTon ----- */
	static CWindow* GetI() {
		static CWindow instance;
		return &instance;
	}

private:
	CWindow();
	~CWindow();

private:
	/* ----- Window Helper Function ----- */
	ATOM MyRegisterClass(HINSTANCE hInstance);
	BOOL InitInstance(HINSTANCE gInstance, int nCmdShow);

public:
	/* ----- Window Helper Function ----- */
	int Run(HINSTANCE hInstance, int nCmdShow);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	/* ----- Base Framework Function ----- */
	virtual bool	Begin();
	virtual bool	Update();
	virtual bool	Render();
	virtual bool	End();

	void		Logic();

public:
	/* ----- Helper Function ----- */
	const WindowInfo& GetWindowInfo() { return m_tInfo; }
	
	void ReSizeWindow(float width, float height);
	void ReSizeWindow(int32 width, int32 height);
	void TitleRename(const wstring& str);

private:
	/* ----- Window Variable ------ */
	struct WindowInfo m_tInfo = { 1200, 800, true, true };

	shared_ptr<class Device> m_pDevice;

	// ¿”Ω√∞¥√º
	vector<class Vertex> m_vecVertices;
	LPDIRECT3DVERTEXBUFFER9 m_pBuffer;
	LPDIRECT3DINDEXBUFFER9 m_pIndex;
	LPD3DXMESH m_pTeapot;

	Vec2 m_fPos = {0.0f,0.0f };
};
