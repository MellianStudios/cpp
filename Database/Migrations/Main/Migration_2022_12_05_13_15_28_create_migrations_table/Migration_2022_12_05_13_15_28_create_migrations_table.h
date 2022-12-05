#ifndef MELLIANCORE_MIGRATION_2022_12_05_13_15_28_CREATE_MIGRATIONS_TABLE_H
#define MELLIANCORE_MIGRATION_2022_12_05_13_15_28_CREATE_MIGRATIONS_TABLE_H

#include "Migration.h"

class Migration_2022_12_05_13_15_28_create_migrations_table : public Migration
{
public:
    void up() override;

    void down() override;

    std::string getSchemaName() override;

    std::string getMigrationName() override;
};

#endif //MELLIANCORE_MIGRATION_2022_12_05_13_15_28_CREATE_MIGRATIONS_TABLE_H
