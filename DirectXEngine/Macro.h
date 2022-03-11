#pragma once

#define CORE CWindow::GetI()
#define WINDOWINFO CWindow::GetI()->GetWindowInfo()
#define INPUT Input::GetI()
#define TIMER Timer::GetI()


#define SAFEDELETE(ptr) if(ptr) { delete ptr; } ptr = nullptr;
