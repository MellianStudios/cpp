#ifndef MELLIANCORE_MIGRATECOMMAND_H
#define MELLIANCORE_MIGRATECOMMAND_H

#include "../CommandContract/CommandContract.h"

class MigrateCommand : public CommandContract
{
public:
    CommandDefinition getCommands() override;

    static bool handleMigrate(const std::vector<std::string> &args);

    static bool handleMigrateFresh(const std::vector<std::string> &args);
};

#endif //MELLIANCORE_MIGRATECOMMAND_H
