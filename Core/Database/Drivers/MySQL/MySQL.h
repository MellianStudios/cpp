#ifndef MELLIANCORE_MYSQL_H
#define MELLIANCORE_MYSQL_H

#include <map>
#include <string>
#include <vector>
#include <mysql-cppconn-8/mysqlx/xdevapi.h>
#include "Config.h"

class MySQL
{
private:
    static mysqlx::Session getSession()
    {
        mysqlx::Session session(
            Config::Main::Database::host,
            Config::Main::Database::port,
            Config::Main::Database::username,
            Config::Main::Database::password
        );

        return session;
    }

public:
    static void unprepared(const std::string &raw_statement)
    {
        mysqlx::Session session = getSession();

        session.sql(raw_statement).execute();
    }

    template<typename T>
    static std::vector<T> all(const std::string &raw_statement)
    {
        mysqlx::Session session = getSession();

        std::list<mysqlx::Row> rows = session.sql(raw_statement).execute().fetchAll();

        std::vector<T> result;

        if (!rows.empty()) {
            for (mysqlx::Row row: rows) {
                T object;

                for (const auto &[column, definition]: object.getColumnList()) {
                    switch (definition.at("type")) {
                        case Config::Global::data_types::type_uint64:
                            object.setMember(
                                definition.at("position"),
                                0,
                                row.get(definition.at("position")).operator uint64_t(),
                                0.0f,
                                "",
                                false
                            );
                            break;
                        case Config::Global::data_types::type_string:
                            object.setMember(
                                definition.at("position"),
                                0,
                                0,
                                0.0f,
                                row.get(definition.at("position")).operator std::string(),
                                false
                            );
                            break;
                    }
                }

                result.emplace_back(object);
            }
        }

        return result;
    }

    template<typename T>
    static void first(
        const std::string &query,
        const std::vector<Config::Database::input_types> &bindings,
        const std::map<std::string, std::map<std::string, std::int_fast32_t>> &column_list,
        const std::vector<std::string> &select = {}
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

        T instance;

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

    static bool tableExists(const std::string &database, const std::string &table)
    {
        mysqlx::Session session = getSession();

        return session.getSchema(database).getTable(table).existsInDatabase();
    }
};

#endif //MELLIANCORE_MYSQL_H
