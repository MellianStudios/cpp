#include <iostream>
#include <map>
#include "AccountModel.h"

const std::string AccountModel::m_table = "accounts";

const std::map<std::string, std::map<std::string, std::int_fast32_t>> AccountModel::m_column_list = {
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
