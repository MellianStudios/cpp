#ifndef MELLIANCORE_MIGRATION_H
#define MELLIANCORE_MIGRATION_H

#include <iostream>

class Migration
{
protected:
    std::string m_query;
    std::string m_operation;

public:
    virtual void up() = 0;

    virtual void down() = 0;

    virtual std::string getSchemaName() = 0;

    void createTable(const std::string &table);

    void dropTable(const std::string &table);

    void setColumns(const std::string &columns);

    void execute();
};

#endif //MELLIANCORE_MIGRATION_H
