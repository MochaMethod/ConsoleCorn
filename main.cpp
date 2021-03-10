#include "map.h"
#include "entity.h"
#include "inputController.h"

// TODO: Border and entity collision.
// TODO: Create a player inventory.
// TODO: What are smart pointers?

int main() {
    Entity player = Entity("player", 'p');
    std::pair<std::size_t, std::size_t> beginningPlayerPosition = { 1, 1 };

    Map map = Map();
    //map.setSpace(space);
    map.generateSpace(20, 50);
    map.setOperatingEntity(player);
    map.modifySpace(beginningPlayerPosition);

    InputController inputController = InputController(); 

    for (;;) {
        // Clears the console:
        std::cout << "\033c";

        map.printSpace();
        inputController.movement(&map, player);
    }

    return 1;
}