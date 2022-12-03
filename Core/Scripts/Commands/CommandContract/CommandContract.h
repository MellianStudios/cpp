#ifndef MELLIANCORE_COMMANDCONTRACT_H
#define MELLIANCORE_COMMANDCONTRACT_H

#include <vector>
#include <functional>
#include <variant>
#include <string>

struct CommandDefinition
{
    std::string name;
    bool permission;
    std::variant<std::function<bool(const std::vector<std::string> &args)>, std::vector<CommandDefinition>> handler;
};

class CommandContract
{
public:
    virtual CommandDefinition getCommands() = 0;

    typedef std::vector<CommandDefinition> CommandList;
    typedef std::function<bool(const std::vector<std::string> &args)> CommandHandler;
};

#endif //MELLIANCORE_COMMANDCONTRACT_H
