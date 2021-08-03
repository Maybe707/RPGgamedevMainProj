#ifndef RPG_GAME_H
#define RPG_GAME_H

#include "scene/Scene.h"
#include "scene/Entity.h"
#include "client/graphics/SpriteBatch.h"
#include "client/graphics/Font.h"
#include "scene/resources/TilePallet.h"

class Game
{
    Font m_font;
    Texture m_heroTexture;
    Texture m_baseTexture;
    TilePallet m_pallet;

    Scene m_scene;

    Entity m_cameraEntity;
public:
    Game();
    void update(float deltaTime);
    void destroy();
};

#endif //RPG_GAME_H
