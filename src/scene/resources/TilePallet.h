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

    void setCellSize(const glm::vec2& cellSize);
    const glm::vec2& getCellSize() const;

    void setCellScale(const glm::vec2& cellScale);
    const glm::vec2& getCellScale() const;

    void setCellOrigin(const glm::vec2& texOffset);
    const glm::vec2& getCellOrigin() const;

    void init();

    void addTile(const IntRect& rect);
    const Tile& getTile(u32 id) const;
};

#endif