#include <iostream>
#include "LookupCommand.h"

CommandDefinition LookupCommand::getCommands() {
    return {"lookup", true, CommandList{
        {"item", true, &handleItem},
        {"faction", true, &handleFaction},
    }};
}

bool LookupCommand::handleItem(const std::vector<std::string> &args) {
    std::cout << "lookup item" << std::endl;

    return true;
}

bool LookupCommand::handleFaction(const std::vector<std::string> &args) {
    std::cout << "lookup faction" << std::endl;

    return true;
}
