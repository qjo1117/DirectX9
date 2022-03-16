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

    auto dxgi = m_pDevice->GetDXGI();
//#pragma region Cube Init
//    {
//
//        //
//        // Create vertex and index buffers.
//        //
//
//        dxgi->CreateVertexBuffer(
//            8 * sizeof(Vertex),
//            D3DUSAGE_WRITEONLY,
//            Vertex::FVF,
//            D3DPOOL_MANAGED,
//            &m_pBuffer,
//            0);
//
//        dxgi->CreateIndexBuffer(
//            36 * sizeof(WORD),
//            D3DUSAGE_WRITEONLY,
//            D3DFMT_INDEX16,
//            D3DPOOL_MANAGED,
//            &m_pIndex,
//            0);
//
//        //
//        // Fill the buffers with the cube data.
//        //
//
//        // define unique vertices:
//        Vertex* vertices;
//        m_pBuffer->Lock(0, 0, (void**)&vertices, 0);
//
//        // vertices of a unit cube
//        vertices[0] = Vertex{ -1.0f, -1.0f, -1.0f };
//        vertices[1] = Vertex{ -1.0f, 1.0f, -1.0f };
//        vertices[2] = Vertex{ 1.0f, 1.0f, -1.0f };
//        vertices[3] = Vertex{ 1.0f, -1.0f, -1.0f };
//        vertices[4] = Vertex{ -1.0f, -1.0f, 1.0f };
//        vertices[5] = Vertex{ -1.0f, 1.0f, 1.0f };
//        vertices[6] = Vertex{ 1.0f, 1.0f, 1.0f };
//        vertices[7] = Vertex{ 1.0f, -1.0f, 1.0f };
//
//        m_pBuffer->Unlock();
//
//        // define the triangles of the cube:
//        WORD* indices = 0;
//        m_pIndex->Lock(0, 0, (void**)&indices, 0);
//
//        // front side
//        indices[0] = 0; indices[1] = 1; indices[2] = 2;
//        indices[3] = 0; indices[4] = 2; indices[5] = 3;
//
//        // back side
//        indices[6] = 4; indices[7] = 6; indices[8] = 5;
//        indices[9] = 4; indices[10] = 7; indices[11] = 6;
//
//        // left side
//        indices[12] = 4; indices[13] = 5; indices[14] = 1;
//        indices[15] = 4; indices[16] = 1; indices[17] = 0;
//
//        // right side
//        indices[18] = 3; indices[19] = 2; indices[20] = 6;
//        indices[21] = 3; indices[22] = 6; indices[23] = 7;
//
//        // top
//        indices[24] = 1; indices[25] = 5; indices[26] = 6;
//        indices[27] = 1; indices[28] = 6; indices[29] = 2;
//
//        // bottom
//        indices[30] = 4; indices[31] = 0; indices[32] = 3;
//        indices[33] = 4; indices[34] = 3; indices[35] = 7;
//
//        m_pIndex->Unlock();
//
//        //
//        // Position and aim the camera.
//        //
//
//        D3DXVECTOR3 position(0.0f, 0.0f, -5.0f);
//        D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
//        D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
//        D3DXMATRIX V;
//        D3DXMatrixLookAtLH(&V, &position, &target, &up);
//
//        dxgi->SetTransform(D3DTS_VIEW, &V);
//
//        //
//        // Set the projection matrix.
//        //
//
//        D3DXMATRIX proj;
//        D3DXMatrixPerspectiveFovLH(
//            &proj,
//            D3DX_PI * 0.5f, // 90 - degree
//            (float)m_tInfo.width / (float)m_tInfo.height,
//            1.0f,
//            1000.0f);
//        dxgi->SetTransform(D3DTS_PROJECTION, &proj);
//
//        //
//        // Switch to wireframe mode.
//        //
//    }
//#pragma endregion

#pragma region Teapot Init
    {
        D3DXCreateTeapot(dxgi, &m_pTeapot, 0);
        //
        // Position and aim the camera.
        //

        D3DXVECTOR3 position(0.0f, 0.0f, -3.0f);
        D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
        D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
        D3DXMATRIX V;
        D3DXMatrixLookAtLH(&V, &position, &target, &up);
        dxgi->SetTransform(D3DTS_VIEW, &V);

        //
        // Set projection matrix.
        //

        D3DXMATRIX proj;
        D3DXMatrixPerspectiveFovLH(
            &proj,
            D3DX_PI * 0.5f, // 90 - degree
            (float)m_tInfo.width / (float)m_tInfo.height,
            1.0f,
            1000.0f);
        dxgi->SetTransform(D3DTS_PROJECTION, &proj);
        dxgi->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
    }
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

        // Setup Platform/Rende                                                    rer backends
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

    if (INPUT->GetButtonDown(KEY_TYPE::ESC)) {
        m_tInfo.isLoop = false;
    }
#pragma endregion


    return true;
}

bool CWindow::Render()
{
    auto dxgi = m_pDevice->GetDXGI();       // DXGI 있는지 여부를 체크한다.
    if (dxgi == nullptr) {
        return false;
    }

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

    dxgi->Clear(0, nullptr, D3DCLEAR_TARGET, m_tInfo.clearColor, 1.0f, 0);
    dxgi->BeginScene();

    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

    // TODO : 그려주자

    D3DXMATRIX Ry;
    static float y = 0.0f;
    D3DXMatrixRotationY(&Ry, y);

    y += DELTATIME;
    if (y >= 6.28f)
        y = 0.0f;

    dxgi->SetTransform(D3DTS_WORLD, &Ry);

    
    //dxgi->SetStreamSource(0, m_pBuffer, 0, sizeof(Vertex));
    //dxgi->SetIndices(m_pIndex);
    //dxgi->SetFVF(D3DFVF_XYZ);

    //// Draw cube.
    //dxgi->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);

    m_pTeapot->DrawSubset(0);


    dxgi->EndScene();
    dxgi->Present(nullptr, nullptr, nullptr, nullptr);

    return true;
}

bool CWindow::End()
{

    SAFERELEASE(m_pBuffer);
    SAFERELEASE(m_pIndex);
    SAFERELEASE(m_pTeapot);

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
