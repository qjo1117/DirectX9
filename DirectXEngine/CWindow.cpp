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

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


LRESULT CWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam)) {
        return true;
    }

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
    m_pDevice->Init(m_tInfo);

#pragma region 버텍스 버퍼 초기화
    LPDIRECT3DDEVICE9 dxgi = m_pDevice->GetDXGI();	// 맵핑

    m_vecVertices.push_back(Vertex{ 320.0f, 50.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(0,  0, 255), });
    m_vecVertices.push_back(Vertex{ 520.0f, 400.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(0, 0, 255), });
    m_vecVertices.push_back(Vertex{ 120.0f, 400.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(0, 0, 255), });

    dxgi->CreateVertexBuffer(3 * sizeof(Vertex),
        0,
        CUSTOMFVF,
        D3DPOOL_MANAGED,
        &m_pBuffer,
        NULL);

    void* pointer = nullptr;    // the void pointer

    m_pBuffer->Lock(0, 0, reinterpret_cast<void**>(&pointer), 0);    // lock the vertex buffer
    memcpy(pointer, &m_vecVertices[0], m_vecVertices.size() * sizeof(Vertex));    // copy the vertices to the locked buffer
    m_pBuffer->Unlock();    // unlock the vertex buffer
#pragma endregion


#pragma region IMGUI INIT
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // Setup Platform/Renderer backends
        ImGui_ImplWin32_Init(m_tInfo.hWnd);
        ImGui_ImplDX9_Init(m_pDevice->GetDXGI());
    }
#pragma endregion

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
#pragma region IMGUI RENDER CLEAR
    // Start the Dear ImGui frame
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    static bool 가능 = true;
    ImGui::ShowDemoWindow(&가능);

    // Rendering
    ImGui::EndFrame();
#pragma endregion

 


    LPDIRECT3DDEVICE9 dxgi = m_pDevice->GetDXGI();	// 맵핑
    dxgi->Clear(0, nullptr, D3DCLEAR_TARGET, m_tInfo.clearColor, 1.0f, 0);
    dxgi->BeginScene();

    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

    // TODO : 그려주자
    // select which vertex format we are using
    dxgi->SetFVF(CUSTOMFVF);

    // select the vertex buffer to display
    dxgi->SetStreamSource(0, m_pBuffer, 0, sizeof(Vertex));

    // copy the vertex buffer to the back buffer
    dxgi->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);


    dxgi->EndScene();
    
    dxgi->Present(nullptr, nullptr, nullptr, nullptr);

    return true;
}

bool CWindow::End()
{
    m_pBuffer->Release();

#pragma region IMGUI RENDER END
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
#pragma endregion
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

void CWindow::ReSizeWindow(int32 width, int32 height)
{
    m_tInfo.width = width;
    m_tInfo.height = height;

    RECT rect = { 0, 0, width, height };
    ::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
    ::SetWindowPos(m_tInfo.hWnd, 0, 0, 0, rect.right - rect.left, rect.bottom - rect.top, 0);


}

void CWindow::TitleRename(const wstring& str)
{

    ::SetWindowTextW(m_tInfo.hWnd, str.c_str());
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
