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
	/* ----- ���� �����츦 �����ߴ��� ----- */
	HWND hWnd = ::GetActiveWindow();
	// ���Ʈ�������� GetFouce�� ����

	/* ----- ���� �����찡 ������ �ȵ� ���¶�� KEY_STATE�� �ʱ�ȭ���ش�. ----- */
	if (hWnd != m_hWnd) {
		for (uint32 key = 0; key < KEY_STATE_COUNT; key++) {
			m_vecStates[key] = KEY_STATE::NONE;
		}
		return;
	}

	/* ----- �ѹ��� �� Ű�� ���ȴ��� Ȯ���Ѵ�. ----- */
	if (::GetKeyboardState(m_arrAscilKeys) == false) {
		m_bAnyKey = false;
		return;
	}
	m_bAnyKey = true;

	/* ----- �� Ű���� ���ε� ���¸� Ȯ���Ѵ�. ----- */
	for (uint32 key = 0; key < KEY_TYPE_COUNT; ++key) {
		if (m_arrAscilKeys[key] & 0x80) {
			KEY_STATE& state = m_vecStates[key];

			if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN) {
				state = KEY_STATE::PRESS;		// ���
			}
			else {
				state = KEY_STATE::DOWN;		// ó��
			}
		}
		else {
			KEY_STATE& state = m_vecStates[key];

			if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN) {
				state = KEY_STATE::UP;			// ó�� UP
			}
			else {
				state = KEY_STATE::NONE;		// �ƿ� ����
			}
		}
	}

	::GetCursorPos(&m_tMousePos);
	::ScreenToClient(CORE->GetWindowInfo().hWnd, &m_tMousePos);
}


/*
	 ----- �ѹ��� �� Ű�� ���ȴ��� Ȯ���Ѵ�. -----
	if (::GetKeyboardState(_ascilKeys) == false) {
		return;
	}
	�׳� ::GetAsyncState�� 256�� �ϴ� �ͺ��� ���� �������� �ٲ�����
	�ʱ� FPS 1400 -> FPS 4000
	���� �ٲ�� ��������� �� �� ����
*/