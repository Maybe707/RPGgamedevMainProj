#ifndef TILEPALLET_H
#define TILEPALLET_H

#include <vector>
#include <glm/vec2.hpp>
#include "Tile.h"

class TilePallet
{
private:
    Texture* m_texture{nullptr};
    std::vector<Tile> m_tiles;
    glm::vec2 m_cellScale{0};
    glm::vec2 m_cellSize{0};
    glm::vec2 m_origin{0};
public:
    TilePallet() = default;

    void setTexture(Texture* texture);
    Texture* getTexture() const;

    /**
     * <p>Устанавливает размер тайла в сетке</p>
     * 
     * @param cellSize Размер тайла в сетке
    */
    void setCellSize(const glm::vec2& cellSize);
    /**
     * <p>Возвращает размер тайла в сетке</p>
     * 
     * @return размер тайла в сетке
    */
    const glm::vec2& getCellSize() const;

    /**
     * <p>Устанавливает скейл тайла в сетке</p>
     * 
     * @param cellScale скейл тайла в сетке
    */
    void setCellScale(const glm::vec2& cellScale);
    /**
     * <p>Возвращает скейл тайла в сетке</p>
     * 
     * @return скейл тайла в сетке
    */
    const glm::vec2& getCellScale() const;

    /**
     * <p>Устанавливает центр тайла в сетке</p>
     * 
     * @param cellOrigin центр тайла в сетке
    */
    void setCellOrigin(const glm::vec2& cellOrigin);
    /**
     * <p>Возвращает центр тайла в сетке</p>
     * 
     * @return центер тайла в сетке
    */
    const glm::vec2& getCellOrigin() const;

    /**
     * <p>Устанавливает расположение и размер тайлов</p>
     * 
     * @param tilePos расположение тайла в сетке
    */
    void addTile(const glm::ivec2& tilePos);
    /**
     * <p>Возвращает тайл по id</p>
     * 
     * @param id Id тайла
     * 
     * @return тайл
    */
    const Tile& getTile(u32 id) const;
};

#endif