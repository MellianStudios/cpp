#include <iostream>
#include "Command.h"
#include "Support/String/String.h"
#include "../AccountCommand/AccountCommand.h"
#include "../LookupCommand/LookupCommand.h"
#include "../MigrateCommand/MigrateCommand.h"

bool Command::run(const std::string &command) {
    AccountCommand account_command;
    LookupCommand lookup_command;
    MigrateCommand migrate_command;

    CommandContract::CommandList commands = {
        account_command.getCommands(),
        lookup_command.getCommands(),
        migrate_command.getCommands(),
    };

    std::vector<std::string> arguments = String::explode(command, " ");

    CommandContract::CommandHandler command_handler = getHandler(commands, arguments);

    return command_handler(arguments);
}

CommandContract::CommandHandler Command::getHandler(
    const CommandContract::CommandList &commands,
    const std::vector<std::string> &arguments,
    std::uint8_t index
) {
    if (index > arguments.size()) {
        return &commandNotFound;
    }

    for (const CommandDefinition &command: commands) {
        if (command.name == arguments[index] || (command.name.empty() && arguments.size() == index)) {
            if (std::holds_alternative<CommandContract::CommandList>(command.handler)) {
                return getHandler(std::get<CommandContract::CommandList>(command.handler), arguments, ++index);
            } else {
                return std::get<CommandContract::CommandHandler>(command.handler);
            }
        }
    }

    return &commandNotFound;
}

bool Command::commandNotFound(const std::vector<std::string> &args) {
    std::cout << "command not found" << std::endl;

    return false;
}
