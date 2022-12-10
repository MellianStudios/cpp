#ifndef MELLIANCORE_COMMAND_H
#define MELLIANCORE_COMMAND_H

#include <string>
#include "Database/DB/DB.h"
#include "Database/QueryBuilder/QueryBuilder.h"
#include "Models/Main/ConsolePermissionModel/ConsolePermissionModel.h"
#include "Models/Main/PermissionModel/PermissionModel.h"
#include "Support/String.h"
#include "Scripts/Commands/AccountCommand.h"
#include "Scripts/Commands/CommandContract.h"
#include "Scripts/Commands/LookupCommand.h"
#include "Scripts/Commands/MigrationCommand.h"
#include "Support/Log/Log.h"

class Command
{
public:
    enum App
    {
        API,
        Auth,
        Chat,
        Guild,
        Instance,
        Mail,
        Manager,
        World,
    };

private:
    static App m_running_server;
    static std::vector<PermissionModel> m_console_permissions;
    static std::map<std::uint8_t, std::string> m_app_names;

    static CommandContract::CommandHandler getHandler(
        const CommandContract::CommandList &commands,
        const std::vector<std::string> &arguments,
        std::string &full_command,
        std::uint8_t index = 0
    )
    {
        if (index > arguments.size()) {
            return &commandNotFound;
        }

        for (const CommandDefinition &command: commands) {
            if (command.name == arguments[index] || (command.name.empty() && arguments.size() == index)) {
                if (std::holds_alternative<CommandContract::CommandList>(command.handler)) {
                    full_command += command.name + ".";

                    return getHandler(std::get<CommandContract::CommandList>(command.handler), arguments, full_command,
                                      ++index);
                } else {
                    full_command += command.name;

                    return std::get<CommandContract::CommandHandler>(command.handler);
                }
            }
        }

        return &commandNotFound;
    }

    static bool commandNotFound(const std::vector<std::string> &args)
    {
        MEL_WARN("command not found");

        return false;
    }

    static bool commandForbidden(const std::vector<std::string> &args)
    {
        MEL_ERROR("forbidden");

        return false;
    }

public:
    static bool run(const std::string &command, bool in_console = false)
    {
        AccountCommand account_command;
        LookupCommand lookup_command;
        MigrationCommand migrate_command;

        CommandContract::CommandList commands = {
            account_command.getCommands(),
            lookup_command.getCommands(),
            migrate_command.getCommands(),
        };

        std::vector<std::string> arguments = String::explode(command, " ");

        std::string full_command;

        CommandContract::CommandHandler command_handler = getHandler(commands, arguments, full_command);

        bool forbidden = std::none_of(
            m_console_permissions.begin(),
            m_console_permissions.end(),
            [&full_command](const PermissionModel &permission) {
                return permission.m_name == full_command;
            });

        if (forbidden) {
            return commandForbidden(arguments);
        }

        return command_handler(arguments);
    }

    static void init(const App &app)
    {
        m_running_server = app;

        m_console_permissions = DB::all<PermissionModel>(
            QueryBuilder::select()
                ->from(PermissionModel::getTableNameWithDBPrefix())
                .where(QueryBuilder::column("id").inRaw(
                    QueryBuilder::select("id")
                        ->from(ConsolePermissionModel::getTableNameWithDBPrefix())
                        .where(QueryBuilder::column("name") == m_app_names.at(app))
                        .str()
                ))
                .str()
        );
    }
};

#endif //MELLIANCORE_COMMAND_H
