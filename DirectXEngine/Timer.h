#pragma once


enum class TIMER_STATE
{
	NONE,
	STOP,
	SLOW,
	FAST,
	END
};

/*----------
	Timer
-----------*/
class Timer
{
public:
	static Timer* GetI() {
		static Timer instance;
		return &instance;
	}

public:
	/* ----- External Function ----- */
	void Init(HWND hWnd);
	void Update();

	/* ----- Helper Function ----- */
	uint32	GetFps() { return m_iFps; }
	float	GetDeltaTime() { return m_fDeltaTime; }

	void	SetTimeScale(float timeScale) { m_fTimeScale = timeScale; }

	/* ----- Time State Function ----- */
	void	Stop() { m_eState = TIMER_STATE::STOP; }
	void	Run() { m_eState = TIMER_STATE::NONE; }
	void	Slow() { m_eState = TIMER_STATE::SLOW; }
	void	Fast() { m_eState = TIMER_STATE::FAST; }

public:
	void	ShowFps();

private:
	/* ----- Frequency Variable ----- */
	uint64		m_iFrequency = 0;
	uint64		m_iPrevCount = 0;
	float		m_fDeltaTime = 0.0f;

private:
	/* ----- Visiable Frame Variable ----- */
	uint32		m_iFrameCount = 0;
	float		m_fFrameTime = 0.0f;
	uint32		m_iFps = 0;

private:
	/* ----- �ð��� ���Ҷ� ���� ���� ----- */
	float		m_fTimeScale = 2.0f;
	TIMER_STATE	m_eState = TIMER_STATE::NONE;

private:
	/* ----- Mapping ----- */
	HWND		m_hWnd = nullptr;
};

