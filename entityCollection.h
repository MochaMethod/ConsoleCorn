#ifndef ENTITYCOLLECTION_H
#define ENTITYCOLLECTION_H

#include "entity.h"

class EntityCollection {
    public:
        Entity m_grass = Entity("grass", ',', false);
        Entity m_corn = Entity("corn", '!', true);
};

#endif