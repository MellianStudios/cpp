#include <iostream>
#include "Config.h"
#include "DotEnv.h"

DotEnv &env = DotEnv::getInstance();

const bool Config::Global::debug = (env.getValue("GLOBAL_DEBUG", "false") == "true") ? true : false;
const std::string Config::Global::data_path = env.getValue("GLOBAL_DATA_PATH", "");

const std::string Config::Auth::Database::host = env.getValue("AUTH_DATABASE_HOST", "127.0.0.1");
const std::string Config::Auth::Database::port = env.getValue("AUTH_DATABASE_PORT", "33060");
const std::string Config::Auth::Database::name = env.getValue("AUTH_DATABASE_NAME", "project_auth");
const std::string Config::Auth::Database::username = env.getValue("AUTH_DATABASE_USERNAME", "root");
const std::string Config::Auth::Database::password = env.getValue("AUTH_DATABASE_PASSWORD", "");
