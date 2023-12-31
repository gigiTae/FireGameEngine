#include "FireGameEnginepch.h"
#include "TimeManager.h"

Fire::TimeManager::TimeManager()
	:m_deltaTime(0.)
	, m_frequency()
	, m_prevCount()
	, m_curentCount()
	, m_elapsedTime(0.)
	, m_fps(0)
	, m_updateCount(0)
{

}

Fire::TimeManager::~TimeManager()
{

}

void Fire::TimeManager::Initialize()
{
	QueryPerformanceFrequency(&m_frequency); // 프로세서의 카운터 값의 빈도
	QueryPerformanceCounter(&m_prevCount); // 이전 프레임의 카운터 값 
	QueryPerformanceCounter(&m_curentCount);
}

float Fire::TimeManager::Update()
{
	QueryPerformanceCounter(&m_curentCount);

	m_deltaTime = (m_curentCount.QuadPart - m_prevCount.QuadPart) / (double)m_frequency.QuadPart;

	m_prevCount = m_curentCount;

	++m_updateCount;
	m_elapsedTime += m_deltaTime;
	if (m_elapsedTime >= 1.)
	{
		m_elapsedTime -= 1.;
		m_fps = m_updateCount;
		m_updateCount = 0;
	}

	return static_cast<float>(m_deltaTime);
}

void Fire::TimeManager::Finalize()
{

}
