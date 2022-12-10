#ifndef MELLIANCORE_MIGRATIONCOMMAND_H
#define MELLIANCORE_MIGRATIONCOMMAND_H

#include "MigrationManager.h"
#include "Scripts/Commands/CommandContract.h"

class MigrationCommand : public CommandContract
{
public:
    CommandDefinition getCommands() override
    {
        return {"migration", CommandList{
            {"run",       &handleMigrationRun},
            {"run:fresh", &handleMigrationFresh},
            {"create",    &handleMigrationCreate},
        }};
    }

    static bool handleMigrationRun(const std::vector<std::string> &args)
    {
        MigrationManager::update();

        return true;
    }

    static bool handleMigrationFresh(const std::vector<std::string> &args)
    {
        MigrationManager::fresh();

        return true;
    }

    static bool handleMigrationCreate(const std::vector<std::string> &args)
    {
        MigrationManager::create(args.at(2));

        return false;
    }
};

#endif //MELLIANCORE_MIGRATIONCOMMAND_H
