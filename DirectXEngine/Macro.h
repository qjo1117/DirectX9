#pragma once

#define CORE CWindow::GetI()
#define WINDOWINFO CWindow::GetI()->GetWindowInfo()
#define INPUT Input::GetI()
#define TIMER Timer::GetI()

#define DELTATIME Timer::GetI()->GetDeltaTime()


#define SAFEDELETE(ptr) if(ptr) { delete ptr; } ptr = nullptr;
#define SAFERELEASE(ptr) if(ptr) { ptr->Release(); } ptr = nullptr;

#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)