#ifndef UICONTROLLER_H
#define UICONTROLLER_H

#include <iostream>
#include <string>
#include <unistd.h>

// TODO: take in vargs
class UIController {
    public:
        void clearConsole() {
            std::cout << "\033c";
        }

        void println(std::string p_text) {
            std::cout << p_text << std::endl;
        }

        void print(std::string p_text) {
            std::cout << p_text;
        }

        void debug(std::string p_text) {
            std::cout << "DEBUG: " << p_text << std::endl;
        }

        void sleep(long unsigned int seconds) {
            sleep(seconds);
        }
};

#endif