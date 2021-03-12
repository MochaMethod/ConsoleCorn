#include "map.h"
#include "entity.h"
#include "player.h"
#include "inputController.h"
#include "uiController.h"
#include "entityCollection.h"

// TODO: Look into VSCode support for C++20
// TODO: Create a player inventory.
// TODO: What are smart pointers?
// TODO: Handle delta time
// TODO: Write onCreate / onUpdate methods

int main() {
    EntityCollection entityCollection = EntityCollection();

    std::pair<std::size_t, std::size_t> beginningPlayerPosition = { 1, 1 };
    std::pair<std::size_t, std::size_t> spaceBounds = { 20, 50 };

    Map map = Map();
    //map.setSpace(space);
    map.generateSpace(spaceBounds);
    map.setOperatingEntity(entityCollection.m_player);
    map.modifySpace(beginningPlayerPosition);
    map.setOperatingEntity(entityCollection.m_player);

    InputController inputController = InputController(&map); 
    UIController uiController = UIController();

    for (;;) {
        uiController.clearConsole();

        map.printSpace();

        uiController.print("Standing on: ");
        uiController.println(entityCollection.entityNameMap[map.getStandingOnEntitySprite()].getName());
        entityCollection.m_player.printInventory();
        inputController.movement();
    }

    return 1;
}