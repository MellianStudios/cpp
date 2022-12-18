#include <iostream>
#include "Config.h"
#include "DotEnv.h"

DotEnv &env = DotEnv::getInstance();

const bool Config::Global::debug = (env.getValue("GLOBAL_DEBUG", "false") == "true");

const std::string Config::Global::project_path = env.getValue("GLOBAL_PROJECT_PATH", "");
const std::string Config::Global::data_path = env.getValue("GLOBAL_DATA_PATH", "");

const std::string Config::Main::Database::host = env.getValue("MAIN_DATABASE_HOST", "127.0.0.1");
const std::uint32_t Config::Main::Database::port = std::stoi(env.getValue("MAIN_DATABASE_PORT", "33060"));
const std::string Config::Main::Database::name = env.getValue("MAIN_DATABASE_NAME", "mellian_core_main");
const std::string Config::Main::Database::username = env.getValue("MAIN_DATABASE_USERNAME", "root");
const std::string Config::Main::Database::password = env.getValue("MAIN_DATABASE_PASSWORD", "");

const std::string Config::API::ssl_certificate_path = env.getValue("API_SSL_CERTIFICATE_PATH", "");
const std::string Config::API::ssl_key_path = env.getValue("API_SSL_KEY_PATH", "");
const std::uint32_t Config::API::port = std::stoi(env.getValue("API_PORT", "9080"));
