#include <iostream>
#include "Scripts/Commands/Command/Command.h"

int main()
{
    std::cout << "manager running" << std::endl;

    std::string command;

    while (true) {
        std::getline(std::cin, command);

        Command::run(command);

        if (command == "exit") {
            return 0;
        }
    }
}
