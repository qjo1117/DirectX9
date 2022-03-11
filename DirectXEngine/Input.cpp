#include "pch.h"
#include "Input.h"
#include "CWindow.h"

void Input::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	m_vecStates.resize(KEY_TYPE_COUNT, KEY_STATE::NONE);
}

void Input::Update()
{
	/* ----- 현재 윈도우를 선택했는지 ----- */
	HWND hWnd = ::GetActiveWindow();
	// 어소트락에서는 GetFouce로 잡음

	/* ----- 현재 윈도우가 선택이 안된 상태라면 KEY_STATE를 초기화해준다. ----- */
	if (hWnd != m_hWnd) {
		for (uint32 key = 0; key < KEY_STATE_COUNT; key++) {
			m_vecStates[key] = KEY_STATE::NONE;
		}
		return;
	}

	/* ----- 한번에 각 키가 눌렸는지 확인한다. ----- */
	if (::GetKeyboardState(m_arrAscilKeys) == false) {
		m_bAnyKey = false;
		return;
	}
	m_bAnyKey = true;

	/* ----- 각 키보드 맵핑된 상태를 확인한다. ----- */
	for (uint32 key = 0; key < KEY_TYPE_COUNT; ++key) {
		if (m_arrAscilKeys[key] & 0x80) {
			KEY_STATE& state = m_vecStates[key];

			if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN) {
				state = KEY_STATE::PRESS;		// 계속
			}
			else {
				state = KEY_STATE::DOWN;		// 처음
			}
		}
		else {
			KEY_STATE& state = m_vecStates[key];

			if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN) {
				state = KEY_STATE::UP;			// 처음 UP
			}
			else {
				state = KEY_STATE::NONE;		// 아예 없음
			}
		}
	}

	::GetCursorPos(&m_tMousePos);
	::ScreenToClient(CORE->GetWindowInfo().hWnd, &m_tMousePos);
}


/*
	 ----- 한번에 각 키가 눌렸는지 확인한다. -----
	if (::GetKeyboardState(_ascilKeys) == false) {
		return;
	}
	그냥 ::GetAsyncState를 256개 하는 것보다 위에 버전으로 바꿨을때
	초기 FPS 1400 -> FPS 4000
	으로 바뀌는 성능향상을 볼 수 있음
*/