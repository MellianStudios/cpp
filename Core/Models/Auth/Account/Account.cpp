#include <iostream>
#include <map>
#include "Account.h"

const std::string Account::m_table = "account";

const std::map<std::string, std::map<std::string, std::int_fast32_t>> Account::m_column_list = {
    {"id",              {{"position", 0},  {"type", Config::Global::data_types::type_uint64}}},
    {"username",        {{"position", 1},  {"type", Config::Global::data_types::type_string}}},
    {"salt",            {{"position", 2},  {"type", Config::Global::data_types::type_binary}}},
    {"verifier",        {{"position", 3},  {"type", Config::Global::data_types::type_binary}}},
    {"session_key",     {{"position", 4},  {"type", Config::Global::data_types::type_binary}}},
    {"totp_secret",     {{"position", 5},  {"type", Config::Global::data_types::type_binary}}},
    {"email",           {{"position", 6},  {"type", Config::Global::data_types::type_string}}},
    {"reg_mail",        {{"position", 7},  {"type", Config::Global::data_types::type_string}}},
    {"joindate",        {{"position", 8},  {"type", Config::Global::data_types::type_timestamp}}},
    {"last_ip",         {{"position", 9},  {"type", Config::Global::data_types::type_string}}},
    {"last_attempt_ip", {{"position", 10}, {"type", Config::Global::data_types::type_string}}},
    {"failed_logins",   {{"position", 11}, {"type", Config::Global::data_types::type_int64}}},
    {"locked",          {{"position", 12}, {"type", Config::Global::data_types::type_int64}}},
    {"lock_country",    {{"position", 13}, {"type", Config::Global::data_types::type_string}}},
    {"last_login",      {{"position", 14}, {"type", Config::Global::data_types::type_timestamp}}},
    {"online",          {{"position", 15}, {"type", Config::Global::data_types::type_int64}}},
    {"expansion",       {{"position", 16}, {"type", Config::Global::data_types::type_int64}}},
    {"mutetime",        {{"position", 17}, {"type", Config::Global::data_types::type_int64}}},
    {"mutereason",      {{"position", 18}, {"type", Config::Global::data_types::type_string}}},
    {"muteby",          {{"position", 19}, {"type", Config::Global::data_types::type_string}}},
    {"locale",          {{"position", 20}, {"type", Config::Global::data_types::type_int64}}},
    {"os",              {{"position", 21}, {"type", Config::Global::data_types::type_string}}},
    {"recruiter",       {{"position", 22}, {"type", Config::Global::data_types::type_int64}}},
    {"totaltime",       {{"position", 23}, {"type", Config::Global::data_types::type_int64}}}
};

std::string Account::getTableName()
{
    return Account::m_table;
}

std::string Account::getDatabaseName()
{
    return Config::Auth::Database::name;
}

std::map<std::string, std::map<std::string, std::int_fast32_t>> Account::getColumnList()
{
    return Account::m_column_list;
}

void Account::setMember(
    const std::int_fast32_t &order,
    const std::int_fast64_t &int64_value,
    const std::uint_fast64_t &uint64_value,
    const double &float_value,
    const std::string &string_value,
    const bool &bool_value
)
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
            std::cout << "column of position " << order << " was not found" << std::endl;
    }
}

Account *Account::getByColumnValue(
    const std::string &where_clause,
    const std::vector<Config::Database::input_types> &bindings,
    const std::vector<std::string> &select_columns
)
{
    auto *account = new Account;

    account->loadByColumnValue(where_clause, bindings, select_columns);

    return account;
}
