#include <map>
#include <vector>
#include <string>
#include <mysql-cppconn-8/mysqlx/xdevapi.h>
#include "Config.h"
#include "MySQL.h"

mysqlx::Session MySQL::getSession()
{
    mysqlx::Session session(
        Config::Auth::Database::host,
        std::stoi(Config::Auth::Database::port),
        Config::Auth::Database::username,
        Config::Auth::Database::password
    );

    return session;
}

void MySQL::unprepared(const std::string &raw_statement)
{
    mysqlx::Session session = getSession();

    session.sql(raw_statement).execute();
}

std::map<std::int64_t, std::map<std::string, std::string>> MySQL::all(const std::string &raw_statement)
{
    std::map<std::int64_t, std::map<std::string, std::string>> result;

    return result;
}

void MySQL::first(
    Model &instance,
    const std::string &query,
    const std::vector<Config::Database::input_types> &bindings,
    const std::map<std::string, std::map<std::string, std::int_fast32_t>> &column_list,
    const std::vector<std::string> &select
)
{
    mysqlx::Session session = getSession();

    mysqlx::SqlStatement statement = session.sql(query + " LIMIT 1;");

    for (const Config::Database::input_types &binding: bindings) {
        std::visit([&statement](auto &argument) {
            statement.bind(argument);
        }, binding);
    }

    mysqlx::Row row = statement.execute().fetchOne();

    if (select.empty()) {
        for (const auto &column: column_list) {
            switch (column.second.at("type")) {
                case Config::Global::data_types::type_int64:
                    instance.setMember(
                        column.second.at("position"),
                        row.get(column.second.at("position")).operator int64_t(),
                        0,
                        0.0f,
                        "",
                        false
                    );
                    break;
                case Config::Global::data_types::type_uint64:
                    instance.setMember(
                        column.second.at("position"),
                        0,
                        row.get(column.second.at("position")).operator uint64_t(),
                        0.0f,
                        "",
                        false
                    );
                    break;
                case Config::Global::data_types::type_float:
                    instance.setMember(
                        column.second.at("position"),
                        0,
                        0,
                        row.get(column.second.at("position")).operator double(),
                        "",
                        false
                    );
                    break;
                case Config::Global::data_types::type_string:
                    instance.setMember(
                        column.second.at("position"),
                        0,
                        0,
                        0.0f,
                        row.get(column.second.at("position")).operator std::string(),
                        false
                    );
                    break;
                case Config::Global::data_types::type_bool:
                    instance.setMember(
                        column.second.at("position"),
                        0,
                        0,
                        0.0f,
                        "",
                        row.get(column.second.at("position")).operator bool()
                    );
                    break;
            }
        }
    } else {
        for (const auto &column: select) {
            switch (column_list.at(column).at("type")) {
                case Config::Global::data_types::type_int64:
                    instance.setMember(
                        column_list.at(column).at("position"),
                        row.get(column_list.at(column).at("position")).operator int64_t(),
                        0,
                        0.0f,
                        "",
                        false
                    );
                    break;
                case Config::Global::data_types::type_uint64:
                    instance.setMember(
                        column_list.at(column).at("position"),
                        0,
                        row.get(column_list.at(column).at("position")).operator uint64_t(),
                        0.0f,
                        "",
                        false
                    );
                    break;
                case Config::Global::data_types::type_float:
                    instance.setMember(
                        column_list.at(column).at("position"),
                        0,
                        0,
                        row.get(column_list.at(column).at("position")).operator double(),
                        "",
                        false
                    );
                    break;
                case Config::Global::data_types::type_string:
                    instance.setMember(
                        column_list.at(column).at("position"),
                        0,
                        0,
                        0.0f,
                        row.get(column_list.at(column).at("position")).operator std::string(),
                        false
                    );
                    break;
                case Config::Global::data_types::type_bool:
                    instance.setMember(
                        column_list.at(column).at("position"),
                        0,
                        0,
                        0.0f,
                        "",
                        row.get(column_list.at(column).at("position")).operator bool()
                    );
                    break;
            }
        }
    }
}

bool MySQL::tableExists(const std::string &database, const std::string &table)
{
    mysqlx::Session session = getSession();

    return session.getSchema(database).getTable(table).existsInDatabase();
}
