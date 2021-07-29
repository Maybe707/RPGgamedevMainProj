#include <GLFW/glfw3.h>

class ChronoGuard
{
    float m_prevFrameTime;
    float m_frameTime;
    float m_deltaTime;
public:
    ChronoGuard(float prevFrameTime, float frameTime, float deltaTime) :
            m_prevFrameTime(prevFrameTime),
            m_frameTime(frameTime),
            m_deltaTime(deltaTime)
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
