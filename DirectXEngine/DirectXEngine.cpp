#include "DirectXEngine.h"
#include "CWindow.h"
#include "pch.h"

#define MAX_LOADSTRING 100

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    return CORE->Run(hInstance, nCmdShow);
}


