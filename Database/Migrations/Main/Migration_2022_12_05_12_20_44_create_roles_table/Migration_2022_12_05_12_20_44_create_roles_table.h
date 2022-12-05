#ifndef MELLIANCORE_MIGRATION_2022_12_05_12_20_44_CREATE_ROLES_TABLE_H
#define MELLIANCORE_MIGRATION_2022_12_05_12_20_44_CREATE_ROLES_TABLE_H

#include "Migration.h"

class Migration_2022_12_05_12_20_44_create_roles_table : public Migration
{
public:
    void up() override;

    void down() override;

    std::string getSchemaName() override;

    std::string getMigrationName() override;
};

#endif //MELLIANCORE_MIGRATION_2022_12_05_12_20_44_CREATE_ROLES_TABLE_H