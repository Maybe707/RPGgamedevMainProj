#include <GLFW/glfw3.h>

class RTime
{
    float m_prevFrameTime;
    float m_frameTime;
    float m_deltaTime;
public:
    RTime(float prevFrameTime, float frameTime, float delta_time) :
        m_prevFrameTime(prevFrameTime),
        m_frameTime(frameTime),
        m_deltaTime(delta_time)
    { }

    void setNewFrameTime()
    {
        m_frameTime = glfwGetTime();
        m_deltaTime = m_frameTime - m_prevFrameTime;
        m_prevFrameTime = m_frameTime;
    }

    float getDeltaTime()
    {   
        setNewFrameTime(); 
        return m_deltaTime; 
    }
};
