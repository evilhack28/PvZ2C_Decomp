//
//  PlantUtils.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-10-04.
//
#include "PvZ/PlantUtils.h"
#include "PvZ/GridItem.h"
#include "PvZ/BoardConstants.h"
#include "PvZ/EntityFinder.h"
#include <algorithm>

/////////////// PlantUtils ///////////////

struct ClusterEntry
{
    BoardEntity* first;
    size_t second;
    bool operator<(const ClusterEntry& o) const { return first < o.first || (!(o.first < first) && second < o.second); }
};

static GridItem* ToGridItem(BoardEntity* e)
{
    return static_cast<GridItem*>(e);
}

GridItemPtr PlantUtils::GetBestDamageableGridItemFromEntities(std::vector<BoardEntity*> entities)
{
    GridItemPtr best;
    int bestColumn = BoardConstants::NUMBER_OF_COLUMNS();
    for (size_t i = 0; i < entities.size(); i++)
    {
        GridItem* item = ToGridItem(entities[i]);
        if (item->IsDamageableByPlants())
        {
            int column = item->GetGridX();
            if (bestColumn > column)
            {
                best = item->GetPtr();
                bestColumn = column;
            }
        }
    }
    return best;
}

ZombiePtr PlantUtils::GetBestZombieFromEntities(const std::vector<BoardEntity*> i_entities, PlantTargetParams& i_targetParams)
{
    ZombiePtr best;
    std::vector<BoardEntity*>::const_iterator it = i_entities.begin();
    std::vector<BoardEntity*>::const_iterator end = i_entities.end();
    for (; it != end; ++it)
    {
        ZombiePtr zombie = (*it)->GetPtr();
        if (zombie.IsValid())
        {
            if (!best.IsValid())
            {
                best = zombie;
                if (i_targetParams.distanceWeight == 0)
                {
                    if (best)
                        return best;
                }
            }
        }
    }
    return best;
}

std::vector<BoardEntityPtr> PlantUtils::GetEntityClusterTargets(std::vector<BoardEntity*> i_entities, BoardEntityTypeFlag i_targetType, const float i_radius)
{
    std::vector<BoardEntityPtr> targets;
    if (!i_entities.empty())
    {
        std::vector<ClusterEntry > clusters;
        {
            std::vector<BoardEntity*>::iterator it = i_entities.begin();
            std::vector<BoardEntity*>::iterator end = i_entities.end();
            for (; it != end; ++it)
            {
                BoardEntity*& current = *it;
                ClusterEntry entry;
                entry.first = current;
                std::vector<BoardEntity*> nearby;
                EntityFinder::GetEntitiesWithinCircle(nearby, i_targetType, current->GetPosition(), i_radius);
                entry.second = nearby.size();
                clusters.push_back(entry);
            }
        }
        std::sort(clusters.begin(), clusters.end());
        {
            std::vector<ClusterEntry >::iterator cit = clusters.begin();
            std::vector<ClusterEntry >::iterator cend = clusters.end();
            for (; cit != cend; ++cit)
            {
                targets.push_back(cit->first->GetPtr());
            }
        }
    }
    return targets;
}
