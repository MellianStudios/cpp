#ifndef MELLIANCORE_ACCOUNTCOMMAND_H
#define MELLIANCORE_ACCOUNTCOMMAND_H

#include "../CommandContract/CommandContract.h"

class AccountCommand : public CommandContract
{
public:
    CommandDefinition getCommands() override;

    static bool handleAccount(const std::vector<std::string> &args);

    static bool handleSetPassword(const std::vector<std::string> &args);
};

#endif //MELLIANCORE_ACCOUNTCOMMAND_H
