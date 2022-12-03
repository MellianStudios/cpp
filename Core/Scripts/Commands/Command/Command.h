#ifndef MELLIANCORE_COMMAND_H
#define MELLIANCORE_COMMAND_H

#include <string>
#include "../CommandContract/CommandContract.h"

class Command
{
private:
    static CommandContract::CommandHandler getHandler(
        const CommandContract::CommandList &commands,
        const std::vector<std::string> &arguments,
        std::uint8_t index = 0
    );

    static bool commandNotFound(const std::vector<std::string> &args);

public:
    static bool run(const std::string &command);
};

#endif //MELLIANCORE_COMMAND_H
