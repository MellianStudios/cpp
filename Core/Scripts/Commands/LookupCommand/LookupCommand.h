#ifndef MELLIANCORE_LOOKUPCOMMAND_H
#define MELLIANCORE_LOOKUPCOMMAND_H

#include "../CommandContract/CommandContract.h"

class LookupCommand : public CommandContract
{
public:
    CommandDefinition getCommands() override;

    static bool handleItem(const std::vector<std::string> &args);

    static bool handleFaction(const std::vector<std::string> &args);
};

#endif //MELLIANCORE_LOOKUPCOMMAND_H
