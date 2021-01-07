#pragma once
#include <iostream>
class FPSChecker
{
public:
	FPSChecker()=default;
	~FPSChecker()=default;
	void update(float deltaTime)
	{
		m_Frames++;
		m_AccuSec += deltaTime;
		m_Time += deltaTime;
		if (m_AccuSec > m_CheckTime)
		{
			m_AccuSec = 0;
			std::cout << m_Frames / m_Time << std::endl;
		}
	}
private:
	float m_AccuSec=0;
	float m_CheckTime=2;
	int m_Frames=0;
	float m_Time=0;
};
