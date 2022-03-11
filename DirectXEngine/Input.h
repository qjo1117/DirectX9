#pragma once

enum class KEY_TYPE
{
	UP = VK_UP,
	DOWN = VK_DOWN,
	LEFT = VK_LEFT,
	RIGHT = VK_RIGHT,

	SPACE = VK_SPACE,
	DEL = VK_DELETE,
	SHIFT = VK_SHIFT,

	ESC = VK_ESCAPE,

	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',

	Q = 'Q',
	E = 'E',
	Z = 'Z',
	C = 'C',

	R = 'R',
	T = 'T',
	I = 'I',
	J = 'J',
	O = 'O',

	LBUTTON = VK_LBUTTON,
	RBUTTON = VK_RBUTTON,

	N_1 = '1',
	N_2 = '2',
	N_3 = '3',
	N_4 = '4',
	N_5 = '5',
	N_6 = '6',
	N_7 = '7',
	N_8 = '8',
	N_9 = '9',
	N_0 = '0',
};

enum class KEY_STATE
{
	NONE,
	PRESS,
	DOWN,
	UP,
	END
};

enum
{
	KEY_TYPE_COUNT = static_cast<int32>(UINT8_MAX + 1),
	KEY_STATE_COUNT = static_cast<int32>(KEY_STATE::END)
};


/*-----------
	Input
------------*/
class Input
{
public:
	static Input* GetI() {
		static Input instance;
		return &instance;
	}

public:
	/* ----- External Function ----- */
	void Init(HWND hWnd);
	void Update();

	/* ----- Helper Function ----- */
	bool GetButton(KEY_TYPE key) { return GetState(key) == KEY_STATE::PRESS; }
	bool GetButtonDown(KEY_TYPE key) { return GetState(key) == KEY_STATE::DOWN; }
	bool GetButtonUp(KEY_TYPE key) { return GetState(key) == KEY_STATE::UP; }

	bool IsAnyKey() { return m_bAnyKey; }

	const POINT& GetMousePos() { return m_tMousePos; }

private:
	/* ----- Mapping Function ----- */
	inline KEY_STATE GetState(KEY_TYPE key) { return m_vecStates[static_cast<int>(key)]; }

private:
	/* ----- Input Variable ----- */
	HWND				m_hWnd;

	bool				m_bAnyKey = false;

	vector<KEY_STATE>	m_vecStates;
	BYTE				m_arrAscilKeys[KEY_TYPE_COUNT] = {};
	POINT				m_tMousePos = {};
};

