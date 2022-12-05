#ifndef MELLIANCORE_MIGRATIONMANAGER_H
#define MELLIANCORE_MIGRATIONMANAGER_H

#include <string>

class MigrationManager
{
private:
    template<typename T>
    static void runMigration(bool fresh = false);

    static void ensureMigrationTableExists();

public:
    static void update();

    static void fresh();

    static void create(const std::string &path);
};

#endif //MELLIANCORE_MIGRATIONMANAGER_H
