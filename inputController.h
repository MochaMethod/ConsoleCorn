#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include "entity.h"
#include "player.h"
#include "map.h"
#include "rawmode.h"
#include "inputOptions.h"
#include "uiController.h"
#include "entityCollection.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>

class InputController {
    public:
        InputController() {}
        InputController(Map* p_space) {
            m_space = p_space;
        }

        // Members:
        InputOptions options = InputOptions();
        UIController uiController = UIController();
        EntityCollection entityCollection = EntityCollection();

        // Utilities:
        void movement() {
            enableRawMode();

            char c;
            read(STDIN_FILENO, &c, 1);
            switch(c) {
                case 'w' :
                    handleRawModeMovement(-1, 0);
                    break;
                case 's' :
                    handleRawModeMovement(1, 0);
                    break;
                case 'a' :
                    handleRawModeMovement(0, -1);
                    break;
                case 'd' :
                    handleRawModeMovement(0, 1);
                    break;
                case 'e' :
                    disableRawMode();
                    userInput();
                    break;
                case 'q':
                    disableRawMode();
                    exit(1);
                    break;
                default:
                    std::cout << "Invalid movement." << std::endl;
                    break;
            }
        
    }

    void handleRawModeMovement(std::size_t p_colModifier, std::size_t p_rowModifier) {
        std::pair<std::size_t, std::size_t> newPosition = m_space->getUpdatedPosition(std::pair<std::size_t, std::size_t> { p_colModifier, p_rowModifier });
        if (!m_space->willCollideWithBorder(newPosition)) m_space->modifySpace(newPosition);

        disableRawMode();
    }

    // TODO: Confirm user selection.
    // TODO: Find out why map spazzes out.
    std::string handleEntries(std::vector<std::string> p_acceptableInput) {
        uiController.println("Choices: ");
        for (std::string i : p_acceptableInput) {
            uiController.print(i);
            uiController.print(" ");
        }
        uiController.println("");
        std::string rawInput;
        std::string acceptedInput;

        for (;;) {
            std::cin >> rawInput;

            std::vector<std::string> inputVector;
            
            for (std::string i : p_acceptableInput) {
                if (std::find(p_acceptableInput.begin(), p_acceptableInput.end(), i) != p_acceptableInput.end()) {
                    if (i.rfind(rawInput, 0) == 0) inputVector.push_back(i);
                }
            }

            if (inputVector.size() == 0) {
                uiController.println("Invalid input.");
            } else if (inputVector.size() == 1) {
                acceptedInput = inputVector[0];
                break;
            } else {
                uiController.println("Which of the following did you mean?: ");
                for (std::string i : inputVector) {
                    uiController.println(i);
                }
            }
        }

        uiController.print("You chose: ");
        uiController.println(acceptedInput);

        sleep(1);

        return acceptedInput;
    }

    void userInput() {
        std::vector<std::string> acceptableInput = {
            options.m_interact
        };
        std::string input = handleEntries(acceptableInput);

        if (input == options.m_interact) {
            std::vector<std::string> acceptableInput = { options.m_grab };
            handleEntries(acceptableInput);
        } else if (input == options.m_grab) {
            if (m_space->getStandingOnEntitySprite() == entityCollection.m_corn.getSprite()) {
                entityCollection.m_player.inventory[entityCollection.m_corn.getName()] = entityCollection.m_corn;
            }
        }
    }

    private:
        char m_userEntry;
        Map* m_space;
};

#endif