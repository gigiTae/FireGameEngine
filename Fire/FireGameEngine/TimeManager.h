#pragma once


namespace Fire
{
class TimeManager
{
public:
	static TimeManager* GetInstance() { static TimeManager mgr; return &mgr; }

public:
	TimeManager();
	~TimeManager();

	void Initialize();
	float Update();
	void Finalize();

public:
	float GetDeltaTime() const { return static_cast<float>(m_deltaTime); }
	int GetFPS() { return m_fps; }

private:
	LARGE_INTEGER m_curentCount;
	LARGE_INTEGER m_prevCount;
	LARGE_INTEGER m_frequency;

	double m_deltaTime;
	double m_elapsedTime;
	int m_updateCount;
	int m_fps;
};

}
