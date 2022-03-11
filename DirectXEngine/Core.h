#pragma once

#include <Windows.h>

class Core
{

public:

	ATOM                MyRegisterClass(HINSTANCE hInstance);
	BOOL                InitInstance(HINSTANCE, int);
	LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);


};

