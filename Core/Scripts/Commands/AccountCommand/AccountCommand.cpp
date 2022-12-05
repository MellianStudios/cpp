#include <iostream>
#include "AccountCommand.h"

CommandDefinition AccountCommand::getCommands()
{
    return {"account", true, CommandList{
        {"",    true, &handleAccount},
        {"set", true, CommandList{
            {"password", true, &handleSetPassword},
        }}
    }};
}

bool AccountCommand::handleAccount(const std::vector<std::string> &args)
{
    std::cout << "account" << std::endl;

    return true;
}

bool AccountCommand::handleSetPassword(const std::vector<std::string> &args)
{
    std::cout << "set password " << args[3] << std::endl;

    return true;
}