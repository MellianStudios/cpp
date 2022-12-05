#include "MigrationCommand.h"
#include "MigrationManager.h"

CommandDefinition MigrationCommand::getCommands()
{
    return {"migration", true, CommandList{
        {"run",       true, &handleMigrationRun},
        {"run:fresh", true, &handleMigrationFresh},
        {"create",    true, &handleMigrationCreate},
    }};
}

bool MigrationCommand::handleMigrationRun(const std::vector<std::string> &args)
{
    MigrationManager::update();

    return true;
}

bool MigrationCommand::handleMigrationFresh(const std::vector<std::string> &args)
{
    MigrationManager::fresh();

    return true;
}

bool MigrationCommand::handleMigrationCreate(const std::vector<std::string> &args)
{
    MigrationManager::create(args.at(2));

    return false;
}
