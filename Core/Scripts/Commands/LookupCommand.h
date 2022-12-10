#ifndef MELLIANCORE_LOOKUPCOMMAND_H
#define MELLIANCORE_LOOKUPCOMMAND_H

#include <iostream>
#include "Scripts/Commands/CommandContract.h"
#include "Support/Log/Log.h"

class LookupCommand : public CommandContract
{
public:
    CommandDefinition getCommands() override
    {
        return {"lookup", CommandList{
            {"item",    &handleItem},
            {"faction", &handleFaction},
        }};
    }

    static bool handleItem(const std::vector<std::string> &args)
    {
        MEL_DEBUG("lookup item");

        return true;
    }

    static bool handleFaction(const std::vector<std::string> &args)
    {
        MEL_DEBUG("lookup faction");

        return true;
    }
};

#endif //MELLIANCORE_LOOKUPCOMMAND_H
