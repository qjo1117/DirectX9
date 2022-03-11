#include "pch.h"
#include "CWindow.h"
#include "Input.h"
#include "Timer.h"

#include "Device.h"


CWindow::CWindow()
{
}

CWindow::~CWindow()
{
    
}

ATOM CWindow::MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = 0;
    wcex.lpszClassName = m_tInfo.title.c_str();
    wcex.hIconSm = nullptr;

    return RegisterClassExW(&wcex);
}

BOOL CWindow::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    m_tInfo.hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    m_tInfo.hWnd = CreateWindowW(m_tInfo.title.c_str(), m_tInfo.title.c_str(), WS_OVERLAPPEDWINDOW,
        100, 100, m_tInfo.width, m_tInfo.height, nullptr, nullptr, hInstance, nullptr);

    if (!m_tInfo.hWnd) {
        return false;
    }

    ShowWindow(m_tInfo.hWnd, nCmdShow);
    UpdateWindow(m_tInfo.hWnd);

    return true;
}

LRESULT CWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

bool CWindow::Begin()
{
    /* ----- SingleTon Init ----- */
    INPUT->Init(m_tInfo.hWnd);
    TIMER->Init(m_tInfo.hWnd);

    /* ----- Default Begin Variable ----- */
    m_pDevice = make_shared<Device>();
    m_pDevice->Init(m_tInfo.hWnd);

    return true;
}

bool CWindow::Update()
{
    TIMER->Update();        // 빈도수 체크       : 정훈영교수님이 하드웨어로 틱 검사하는 걸로 하시면 그걸로 바꾸자
    INPUT->Update();        // 입력 부분


#pragma region Test Input
    if (INPUT->GetButtonDown(KEY_TYPE::A)) {
        MessageBox(nullptr, L"Hello", L"Test", MB_OK);
    }

    if (INPUT->GetButtonDown(KEY_TYPE::ESC)) {
        m_tInfo.isLoop = false;
    }
#pragma endregion

    return true;
}

bool CWindow::Render()
{
    LPDIRECT3DDEVICE9 dxgi = m_pDevice->GetDXGI();	// 맵핑
    dxgi->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);
    dxgi->BeginScene();

    // TODO : 그려주면 된다고 합니다.

    dxgi->EndScene();
    dxgi->Present(nullptr, nullptr, nullptr, nullptr);

    return true;
}

bool CWindow::End()
{
   

    return true;
}

void CWindow::Logic()
{


    Update();
    Render();


}

void CWindow::ReSizeWindow(float width, float height)
{
    ReSizeWindow(static_cast<int>(width), static_cast<int>(height));
}

void CWindow::ReSizeWindow(int width, int height)
{
    // TODO 구현해야한다


}

void CWindow::TitleRename(const wstring& str)
{
    // TODO 구현해야한다

}

int CWindow::Run(HINSTANCE hInstance, int nCmdShow)
{
    m_tInfo.title = L"겜플3A_박정욱";

    MyRegisterClass(hInstance);
    if (!InitInstance(hInstance, nCmdShow)) {
        return false;
    }

    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));

    /* ----- Base FrameWork ----- */
    Begin();
    while (m_tInfo.isLoop) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        Logic();

    }
    End();

    return (int)msg.wParam;
}
