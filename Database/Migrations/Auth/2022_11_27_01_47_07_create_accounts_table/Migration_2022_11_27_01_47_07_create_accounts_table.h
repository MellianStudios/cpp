#ifndef MELLIANCORE_MIGRATION_2022_11_27_01_47_07_CREATE_ACCOUNTS_TABLE_H
#define MELLIANCORE_MIGRATION_2022_11_27_01_47_07_CREATE_ACCOUNTS_TABLE_H

#include "Migration.h"

class Migration_2022_11_27_01_47_07_create_accounts_table : public Migration
{
public:
    void up() override;

    void down() override;

    std::string getSchemaName() override;

    std::string getMigrationName() override;
};

#endif //MELLIANCORE_MIGRATION_2022_11_27_01_47_07_CREATE_ACCOUNTS_TABLE_H
