#ifndef TILEPALLET_H
#define TILEPALLET_H

#include <vector>
#include <glm/vec2.hpp>
#include "Tile.h"

class TilePallet
{
private:
    Texture& m_texture;
    std::vector<Tilee> m_tiles;
    glm::vec2 m_cellScale;
    glm::vec2 m_cellSize;
    glm::vec2 m_texOffset;
public:
    void setCellSize(const glm::vec2& cellSize);
    const glm::vec2& getCellSize() const;

    void setCellScale(const glm::vec2& cellScale);
    const glm::vec2& getCellScale() const;

    void addTile(const Tilee& tile);
};

#endif