#include <GLFW/glfw3.h>
class Chrono_Guard
{
	float m_Prev_Frame_Time;
	float m_Frame_Time;
	float m_Delta_Time;
	public:
Chrono_Guard(float prev_t, float frame, float delta_t) :
	m_Prev_Frame_Time(prev_t), m_Frame_Time(frame), m_Delta_Time(delta_t)
	{}

	void set_New_Frame_Time()
	{
		m_Frame_Time = glfwGetTime();
		m_Delta_Time = m_Frame_Time - m_Prev_Frame_Time;
		m_Delta_Time *= 200;
		m_Prev_Frame_Time = m_Frame_Time;
	}

	float get_Delta() { return m_Delta_Time; }
};
