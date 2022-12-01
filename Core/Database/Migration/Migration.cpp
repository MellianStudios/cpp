#include "Migration.h"
#include "DB.h"

void Migration::createTable(const std::string &table)
{
    m_query = "CREATE TABLE " + getSchemaName() + "." + table + "(";
    m_operation = "create";
}

void Migration::dropTable(const std::string &table)
{
    m_query = "DROP TABLE " + getSchemaName() + "." + table + ";";
    m_operation = "drop";
}

void Migration::setColumns(const std::string &columns)
{
    m_query += columns;
}

void Migration::execute()
{
    if (m_operation == "create") {
        m_query += ");";
    }

    DB::unprepared(m_query);
}
