#ifndef ENTITYCOLLECTION_H
#define ENTITYCOLLECTION_H

#include "entity.h"
#include "player.h"

class EntityCollection {
    public:
        Player m_player = Player("player", 'p', false);
        Entity m_grass = Entity("grass", ',', false);
        Entity m_corn = Entity("corn", '!', true);

        std::unordered_map<char, Entity> entityNameMap = {
            {m_grass.getSprite(), m_grass},
            {m_corn.getSprite(), m_corn}
        };
};

#endif