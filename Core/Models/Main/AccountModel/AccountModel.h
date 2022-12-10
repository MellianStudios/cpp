#ifndef MELLIANCORE_ACCOUNTMODEL_H
#define MELLIANCORE_ACCOUNTMODEL_H

#include <iostream>
#include <map>
#include <vector>
#include <variant>
#include "Config.h"
#include "Models/Model.h"
#include "Support/Log/Log.h"

class AccountModel : public Model
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

    std::string getTableName() override
    {
        return AccountModel::m_table;
    }

    std::string getDatabaseName() override
    {
        return Config::Main::Database::name;
    }

    std::map<std::string, std::map<std::string, std::int_fast32_t>> getColumnList() override
    {
        return AccountModel::m_column_list;
    }

    void setMember(
        const std::int_fast32_t &order,
        const std::int_fast64_t &int64_value,
        const std::uint_fast64_t &uint64_value,
        const double &float_value,
        const std::string &string_value,
        const bool &bool_value
    ) override
    {
        switch (order) {
            case 0:
                m_id = uint64_value;
                break;
            case 1:
                m_username = string_value;
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                m_email = string_value;
                break;
            case 7:
                m_reg_mail = string_value;
                break;
            case 8:
                break;
            case 9:
                m_last_ip = string_value;
                break;
            case 10:
                m_last_attempt_ip = string_value;
                break;
            case 11:
                m_failed_logins = int64_value;
                break;
            case 12:
                m_locked = int64_value;
                break;
            case 13:
                m_lock_country = string_value;
                break;
            case 14:
                break;
            case 15:
                m_online = int64_value;
                break;
            case 16:
                m_expansion = int64_value;
                break;
            case 17:
                m_mutetime = int64_value;
                break;
            case 18:
                m_mutereason = string_value;
                break;
            case 19:
                m_muteby = string_value;
                break;
            case 20:
                m_locale = int64_value;
                break;
            case 21:
                m_os = string_value;
                break;
            case 22:
                m_recruiter = int64_value;
                break;
            case 23:
                m_totaltime = int64_value;
                break;
            default:
                MEL_ERROR("column of position {0} was not found", order);
        }
    }

    static AccountModel *getByColumnValue(
        const std::string &where_clause,
        const std::vector<Config::Database::input_types> &bindings,
        const std::vector<std::string> &select_columns = {}
    )
    {
        auto *account = new AccountModel;

        account->loadByColumnValue<AccountModel>(where_clause, bindings, select_columns);

        return account;
    }
};

#endif //MELLIANCORE_ACCOUNTMODEL_H
