#ifndef MELLIANCORE_MIGRATION_H
#define MELLIANCORE_MIGRATION_H

#include <string>
#include "DB.h"

class Migration
{
protected:
    std::string m_query;
    std::string m_operation;

    void createTable(const std::string &table)
    {
        m_query = "CREATE TABLE " + getSchemaName() + "." + table + "(";
        m_operation = "create";
    }

    void dropTable(const std::string &table)
    {
        m_query = "DROP TABLE " + getSchemaName() + "." + table + ";";
        m_operation = "drop";
    }

    void setColumns(const std::string &columns)
    {
        m_query += columns;
    }

    void execute()
    {
        if (m_operation == "create") {
            m_query += ");";
        }

        DB::unprepared(m_query);
    }

public:
    virtual void up() = 0;

    virtual void down() = 0;

    virtual std::string getSchemaName() = 0;

    virtual std::string getMigrationName() = 0;
};

#endif //MELLIANCORE_MIGRATION_H
