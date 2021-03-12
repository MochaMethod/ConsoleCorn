#ifndef PLAYER_H
#define PLAYER_H

#include "uiController.h"
#include "entity.h"

class Player : public Entity {
    public:
        using Entity::Entity;

        UIController uiController = UIController();

        std::unordered_map<std::string, Entity> inventory;

        void printInventory() {
            uiController.println("Inventory: ");
            for ( auto& [key, value] : inventory )
                uiController.println(key);
        }
};

#endif