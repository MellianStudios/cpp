#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

#include <iostream>
#include <variant>
#include <map>

class Config
{
private:
    Config() = default;

public:
    class Global
    {
    private:
        Global() = default;

    public:
        static const bool debug;
        static const std::string data_path;
        static const std::string project_path;
        enum data_types
        {
            type_int64 = 0,
            type_uint64 = 1,
            type_float = 2,
            type_string = 3,
            type_bool = 4,
            type_binary = 5,
            type_timestamp = 6
        };
    };

    class Main
    {
    private:
        Main() = default;

    public:
        class Database
        {
        private:
            Database() = default;

        public:
            static const std::string host;
            static const std::string port;
            static const std::string name;
            static const std::string username;
            static const std::string password;
        };
    };

    class Database
    {
    private:
        Database() = default;

    public:
        typedef std::variant<std::uint64_t, std::int64_t, double, std::string, bool> input_types;
    };
};

#endif //PROJECT_CONFIG_H
