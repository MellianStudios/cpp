#include "MigrateCommand.h"
#include "MigrationManager.h"

CommandDefinition MigrateCommand::getCommands() {
    return {"migrate", true, CommandList{
        {"",      true, &handleMigrate},
        {"fresh", true, &handleMigrateFresh},
    }};
}

bool MigrateCommand::handleMigrate(const std::vector<std::string> &args) {
    MigrationManager::update();

    return true;
}

bool MigrateCommand::handleMigrateFresh(const std::vector<std::string> &args) {
    MigrationManager::fresh();

    return true;
}
