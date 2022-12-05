#ifndef MELLIANCORE_MIGRATIONCOMMAND_H
#define MELLIANCORE_MIGRATIONCOMMAND_H

#include "Scripts/Commands/CommandContract/CommandContract.h"

class MigrationCommand : public CommandContract
{
public:
    CommandDefinition getCommands() override;

    static bool handleMigrationRun(const std::vector<std::string> &args);

    static bool handleMigrationFresh(const std::vector<std::string> &args);

    static bool handleMigrationCreate(const std::vector<std::string> &args);
};

#endif //MELLIANCORE_MIGRATIONCOMMAND_H
