#ifndef RPG_WORLDMAPSCRIPT_H
#define RPG_WORLDMAPSCRIPT_H

#include <vector>
#include "../scene/Script.h"
#include "../scene/components/WorldMapComponent.h"
#include "../client/graphics/Rect.h"
#include "../utils/OpenSimplexNoise.h"

#define DEBUG_SEED INT_MAX

class WorldMapGenerator : public IWorldMapGenerator
{
    OpenSimplexNoise m_simplexNoise;

    Texture m_texture;

    Tile sandTile{&m_texture, IntRect(192, 4256 - 32, 32, 32)};
    Tile grassTile{&m_texture, IntRect(96, 4256 - 32, 32, 32)};
    Tile dirtTile{&m_texture, IntRect(160, 4256 - 32, 32, 32)};
    Tile treeTile{
            &m_texture, IntRect(160 - 96, 4256 - 96, 64, 64),
            1, glm::vec2(16, -8)
    };

    Entity m_player;

public:
    WorldMapGenerator(Texture texture, Entity player)
            : m_simplexNoise(DEBUG_SEED), m_texture(texture), m_player(player) {}

    std::vector<Tile> generate(int x, int y) override
    {
        auto& transform = m_player.getComponent<TransformComponent>();

        double value = m_simplexNoise.getNoise(x, y);

        if (value > 0.3f)
        {
            return {dirtTile};
        }
        if (value > -0.2f)
        {
            std::vector grass = {grassTile};

            // Strange condition to make the forest more rare
            if (value > -0.15f && ((int) (value * 10000) % 5) == 2)
            {
                Tile currentTree = treeTile;
                // We need -16 offset to make the layer change more accurate
                // This offset depends on the texture we are using
                if ((transform.position.y - 16) / 64 > y)
                {
                    currentTree.layer = 3;
                }
                grass.push_back(currentTree);
            }
            return grass;
        }
        return {sandTile};
    }
};

class WorldMapScript : public Script
{
private:
    WorldMapComponent *m_worldMap{};
    TransformComponent *m_worldTransform{};
    WorldMapGenerator m_worldMapGenerator;
public:
    WorldMapScript(Texture texture, Entity player)
            : m_worldMapGenerator(texture, player) {}

    void onCreate() override
    {
        m_worldMap = &getComponent<WorldMapComponent>();
        m_worldTransform = &getComponent<TransformComponent>();
        m_worldMap->generator = &m_worldMapGenerator;
    }

    void onUpdate(float deltaTime) override
    {
        Window &window = Window::getInstance();
        float radius = std::max(window.getWidth(), window.getHeight()) / 2;
        float scale = std::max(m_worldTransform->scale.x, m_worldTransform->scale.y);
        m_worldMap->renderRadius = radius / (scale * m_worldMap->tileSize) + 2;
    }
};

#endif //RPG_WORLDMAPSCRIPT_H
