#include "map.h"
#include "entity.h"
#include "inputController.h"
#include "uiController.h"
#include "entityCollection.h"

// TODO: Create a player inventory.
// TODO: What are smart pointers?
// TODO: Handle delta time
// TODO: Write onCreate / onUpdate methods

int main() {
    EntityCollection entityCollection = EntityCollection();

    // TODO: Write char to string map
    std::unordered_map<char, std::string> entityNameMap = {
        {entityCollection.m_grass.getSprite(), entityCollection.m_grass.getName()},
        {entityCollection.m_corn.getSprite(), entityCollection.m_corn.getName()}
    };

    Entity player = Entity("player", 'p', false);
    std::pair<std::size_t, std::size_t> beginningPlayerPosition = { 1, 1 };
    std::pair<std::size_t, std::size_t> spaceBounds = { 20, 50 };

    Map map = Map();
    //map.setSpace(space);
    map.generateSpace(spaceBounds);
    map.setOperatingEntity(player);
    map.modifySpace(beginningPlayerPosition);
    map.setOperatingEntity(player);

    InputController inputController = InputController(&map); 
    UIController uiController = UIController();

    for (;;) {
        uiController.clearConsole();

        map.printSpace();

        uiController.print("Standing on: ");
        uiController.println(entityNameMap[map.getStandingOnEntitySprite()]);

        inputController.movement();
    }

    return 1;
}