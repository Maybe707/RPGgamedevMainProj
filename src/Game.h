#ifndef RPG_GAME_H
#define RPG_GAME_H

#include "scene/Scene.h"
#include "scene/Entity.h"
#include "graphics/SpriteBatch.h"
#include "graphics/Camera2D.h"
#include "graphics/Font.h"

class Game
{
    Camera2D m_camera;

    Font m_font;
    Texture m_heroTexture;

    Scene m_scene;

    Entity m_playerEntity;

    Entity m_textEntity;
    Entity m_debugInfoEntity;

public:
    Game();
    void update(float deltaTime);
    void destroy();

    // TODO: Временный метод
    Camera2D* getCamera();
};

#endif //RPG_GAME_H
