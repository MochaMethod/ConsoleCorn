#include "map.h"
#include "entity.h"
#include "inputController.h"

int main() {
    Entity player = Entity();
    player.setSprite('p');

    std::vector<std::vector<char>> space = {
        {'.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.'},
    };

    Map map = Map();
    map.setSpace(space);
    map.setOperatingEntity(player);
    map.modifySpace(1, 1);

    InputController inputController = InputController(); 

    for (;;) {
        map.printSpace();
        inputController.movement(&map, player);
    }

    return 0;
}