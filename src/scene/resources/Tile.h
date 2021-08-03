#ifndef TILE_H
#define TILE_H

#include <vector>
#include <memory>
#include "../../client/graphics/Sprite.h"
#include "../../utils/Types.h"

class Tilee
{
private:
    u8 m_id;
    FloatRect m_aabb;
    bool m_collide;
public:
    Tilee() = default;
    Tilee(u8 id, FloatRect aabb, bool collide) : 
        m_id(id), 
        m_aabb(aabb),
        m_collide(collide) { }
};

// TODO: Заготовка для информации о тайле. 
struct Tile
{
    Sprite& m_sprite;
    u8 m_id;
    bool m_collide;

    Tile(Sprite& sprite, u8 id, bool collide) :
        m_sprite(sprite),
        m_id(id),
        m_collide(collide) {};
    /**
     * <p>Проверяет может ли что то столкнуться с тайлом</p>
     * 
     * @return true если да, false иначе
    */
    inline bool isCollide() const { return m_collide; }
    /**
     * <p>Возвращает ссылку на спрайт</p>
     * 
     * @return Sprite&
    */
    inline Sprite& getSprite() const { return m_sprite; }
    /**
     * <p>Возвращает id тайла</p>
     * 
     * @return u8 id
    */
    inline u8 getId() const { return m_id; }
};

// TODO: временное решение в виде глобальной переменной. Определение в GameMain.cpp
extern std::vector<std::unique_ptr<Tile>> TilesData;

#endif
