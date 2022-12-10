#include <iostream>
#include "Scripts/Commands/Command/Command.h"
#include "Support/Log/Log.h"

int main()
{
    Log::init();
    Command::init(Command::App::Mail);

    MEL_INFO("mail server running");

    std::atomic<bool> exit = false;

    std::thread console = std::thread([&]() {
        std::string command;

        while (!exit) {
            std::getline(std::cin, command);

            if (command == "exit") {
                exit = true;
            } else {
                Command::run(command, true);
            }
        }
    });

    // dummy
    while (!exit) {}

    console.join();

    MEL_INFO("mail bye");
}
