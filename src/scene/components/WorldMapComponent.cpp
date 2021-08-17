#include "WorldMapComponent.h"

void WorldMapComponent::addTile(int id, Tile tile)
{
    tileSet.insert({id, tile});
}
