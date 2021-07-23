#ifndef PLAYER_IMPLEMENTATION
#define PLAYER_IMPLEMENTATION

#include "IUnit.h"

class Player : public IUnit
{
    glm::vec2 m_position;
    float m_Speed;
    int m_keyAxis;
public:
    Player(glm::vec2 position, float speed);

    glm::vec2 getPosition() const;
    void setPosition(glm::vec2 position);

    float getSpeed() const;
    void setSpeed(const float speed);

    int getKeyAxis();

    virtual void draw(Shader shader, unsigned int vaoId, Texture texture) override;

    virtual void receiver(int key, int action) override;
};

#endif
