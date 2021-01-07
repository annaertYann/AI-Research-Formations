#pragma once
class Delay
{
public:
	Delay(float time) { m_DelayTime = time; };
	~Delay() = default;
	
	bool Update(float deltaTime)
	{
		if (m_Start)
		{
			m_AccuSec += deltaTime;
			if (m_AccuSec >= m_DelayTime)
			{
				Reset();
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}

	}

	//helpers
	void Start() { m_Start = true; }
	void Stop() { m_Start = false; }
	void Reset() { m_AccuSec = 0; }
	void AddTime(float time) { m_AccuSec += time; }
	void SetDelayTime(float time) { m_DelayTime = time; }
	float GetDelayTime() { return m_DelayTime; }
	bool GetIsActive() { return m_Start; }
private:
	float m_AccuSec=0;
	float m_DelayTime;
	bool m_Start = true;
};
