#include "TilePallet.h"

void TilePallet::setCellSize(const glm::vec2& cellSize)
{
    m_cellSize = cellSize;
}

const glm::vec2& TilePallet::getCellSize() const
{
    return m_cellSize;
}

void TilePallet::setCellScale(const glm::vec2& cellScale)
{
    m_cellScale = cellScale;
}

const glm::vec2& TilePallet::getCellScale() const
{
    return m_cellScale;
}

void TilePallet::addTile(const Tilee& tile)
{
    m_tiles.emplace_back(tile);
}
