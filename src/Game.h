#ifndef RPG_GAME_H
#define RPG_GAME_H

#include "scene/Scene.h"
#include "scene/Entity.h"
#include "client/graphics/SpriteBatch.h"
#include "client/graphics/Font.h"

class Game
{
    Font m_font;
    Texture m_heroTexture;

    Scene m_scene;

    Entity m_cameraEntity;
public:
    Game();
    void update(float deltaTime);
    void destroy();
};

#endif //RPG_GAME_H
