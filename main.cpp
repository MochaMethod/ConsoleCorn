#include "map.h"
#include "entity.h"
#include "inputController.h"

// TODO: Create different entities && entity collection
// TODO: Create a player inventory.
// TODO: Border and entity collision.
// TODO: What are smart pointers?

int main() {
    Entity player = Entity("player", 'p');
    /*
    std::vector<std::vector<char>> space = {
        {'.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.'},
    };
    */

    Map map = Map();
    //map.setSpace(space);
    map.generateSpace(20, 50);
    map.setOperatingEntity(player);
    map.modifySpace(1, 1);

    InputController inputController = InputController(); 

    for (;;) {
        // Clears the console:
        std::cout << "\033c";

        map.printSpace();
        inputController.movement(&map, player);
    }

    return 0;
}