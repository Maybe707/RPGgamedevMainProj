#ifndef PLAYER_IMPLEMENTATION
#define PLAYER_IMPLEMENTATION

#include "Unit_Interface.h"

class PlayerImpl : public IUnit
{
    float m_xAxis;
    float m_yAxis;
    float m_Speed;
    float m_xRange = 32.0f;
    float m_yRange = 32.0f;
    int m_keyAxis;
    int m_action;
public:
    PlayerImpl(float xAxis, float yAxis, float speed);

    void setXAxis(float xAxis);
    void setYAxis(float yAxis);
    
    void setKeyAxis(int key);
    void set_Speed(const float& speed);

    float getXAxis();
    float getYAxis();

    float getXRange();
    float getYRange();

    int& getKeyAxis();
    int& getAction();
    float& getSpeed();

    virtual void draw(const int screenWidth, const int screenHeight,
                      Shader shader, unsigned int vaoId, Texture texture) override;
        
    virtual void receiver(int key, int action) override;
};

#endif
