#include <GLFW/glfw3.h>

class ChronoGuard
{
    float m_prevFrameTime;
    float m_frameTime;
    float m_deltaTime;

    int m_frameCount;
    float m_fpsStartTime;
    int m_fps;
public:
    ChronoGuard(float prevFrameTime, float frameTime, float delta_time) :
            m_prevFrameTime(prevFrameTime),
            m_frameTime(frameTime),
            m_deltaTime(delta_time),
            m_fpsStartTime(0),
            m_frameCount(0),
            m_fps(0)
    { }

    void setNewFrameTime()
    {
        m_frameTime = glfwGetTime();
        m_deltaTime = m_frameTime - m_prevFrameTime;
        m_prevFrameTime = m_frameTime;

        m_frameCount++;

        // Если прошла секунда
        if (m_frameTime - m_fpsStartTime >= 1.0)
        {
            m_fps = m_frameCount;

            m_frameCount = 0;
            m_fpsStartTime = m_frameTime;
        }
    }

    float getDeltaTime()
    {   
        setNewFrameTime(); 
        return m_deltaTime; 
    }

    int getFps()
    {
        return m_fps;
    }
};
