#ifndef MELLIANCORE_ACCOUNTCOMMAND_H
#define MELLIANCORE_ACCOUNTCOMMAND_H

#include "Scripts/Commands/CommandContract.h"
#include "Support/Log/Log.h"

class AccountCommand : public CommandContract
{
public:
    CommandDefinition getCommands() override
    {
        return {"account", true, CommandList{
            {"",    true, &handleAccount},
            {"set", true, CommandList{
                {"password", true, &handleSetPassword},
            }}
        }};
    }

    static bool handleAccount(const std::vector<std::string> &args)
    {
        MEL_DEBUG("account");

        return true;
    }

    static bool handleSetPassword(const std::vector<std::string> &args)
    {
        MEL_DEBUG("set password {0}", args[3]);

        return true;
    }
};

#endif //MELLIANCORE_ACCOUNTCOMMAND_H
