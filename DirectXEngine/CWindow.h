#pragma once

#include <Windows.h>
#include <string>
#include <memory>

using namespace std;

#define MAX_LOADSTRING 100

struct WindowInfo
{
public:
	int width = 0;
	int height = 0;
	bool isLoop = true;

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

protected:
	/* ----- Base Framework Function ----- */
	virtual bool	Begin();
	virtual bool	Update();
	virtual bool	Render();
	virtual bool	End();

	void	Logic();

public:
	/* ----- Helper Function ----- */
	const WindowInfo& GetWindowInfo() { return m_tInfo; }
	
	void ReSizeWindow(float width, float height);
	void ReSizeWindow(int width, int height);
	void TitleRename(const wstring& str);

private:
	/* ----- Window Variable ------ */
	struct WindowInfo m_tInfo = { 800, 500, true };

	shared_ptr<class Device> m_pDevice;
};
