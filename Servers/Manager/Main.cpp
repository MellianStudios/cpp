#include <iostream>
#include "Database/Migration/MigrationManager.h"

int main()
{
    std::cout << "manager running" << std::endl;

    std::string command;

    while (true) {
        std::getline(std::cin, command);

        if (command == "migrate") {
            MigrationManager::update();
        }

        if (command == "migrate fresh") {
            MigrationManager::fresh();
        }

        if (command == "exit") {
            return 0;
        }
    }

    return 0;
}
