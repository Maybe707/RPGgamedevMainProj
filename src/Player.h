#ifndef PLAYER_IMPLEMENTATION
#define PLAYER_IMPLEMENTATION

#include "IUnit.h"
#include "graphics/Sprite.h"

class Player : public IUnit
{
    Sprite& m_sprite;
    float m_speed;
    int m_keyAxis{};
public:
    Player(Sprite& sprite, float speed);

    glm::vec2 getPosition() const;
    void setPosition(glm::vec2 position);

    float getSpeed() const;
    void setSpeed(const float speed);

    int getKeyAxis() const;

    virtual void draw(SpriteBatch& batch) override;

    virtual void receiver(int key, int action) override;
};

#endif
