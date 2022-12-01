#ifndef MELLIANCORE_ACCOUNT_H
#define MELLIANCORE_ACCOUNT_H

#include <iostream>
#include <map>
#include <vector>
#include <variant>
#include "Config.h"
#include "Model.h"

class Account : public Model
{
private:
    static const std::string m_table;
    static const std::map<std::string, std::map<std::string, std::int_fast32_t>> m_column_list;
public:
    std::uint64_t m_id;
    std::string m_username;
    std::string m_email;
    std::string m_reg_mail;
    std::string m_last_ip;
    std::string m_last_attempt_ip;
    std::int64_t m_failed_logins;
    std::int64_t m_locked;
    std::string m_lock_country;
    std::int64_t m_online;
    std::int64_t m_expansion;
    std::int64_t m_mutetime;
    std::string m_mutereason;
    std::string m_muteby;
    std::int64_t m_locale;
    std::string m_os;
    std::int64_t m_recruiter;
    std::int64_t m_totaltime;

    std::string getTableName() override;

    std::string getDatabaseName() override;

    std::map<std::string, std::map<std::string, std::int_fast32_t>> getColumnList() override;

    void setMember(
        const std::int_fast32_t &order,
        const std::int_fast64_t &int64_value,
        const std::uint_fast64_t &uint64_value,
        const double &float_value,
        const std::string &string_value,
        const bool &bool_value
    ) override;

    static Account *getByColumnValue(
        const std::string &where_clause,
        const std::vector<Config::Database::input_types> &bindings,
        const std::vector<std::string> &select_columns = {}
    );
};

#endif //MELLIANCORE_ACCOUNT_H
