#ifndef MELLIANCORE_MIGRATIONMANAGER_H
#define MELLIANCORE_MIGRATIONMANAGER_H

#include <filesystem>
#include <fstream>
#include <string>
#include "Support/String.h"
#include "Support/DateTime.h"
#include "Core/Database/DB/DB.h"
#include "Config/Config.h"
#include "Support/Log/Log.h"
#include "Database/Migrations/Main/Migration_2022_12_05_13_15_28_create_migrations_table.h"
#include "Database/Migrations/Main/Migration_2022_11_27_01_47_07_create_accounts_table.h"
#include "Database/Migrations/Main/Migration_2022_12_05_12_20_44_create_roles_table.h"
#include "Database/Migrations/Main/Migration_2022_12_08_10_00_45_create_permissions_table.h"
#include "Database/Migrations/Main/Migration_2022_12_08_10_19_31_create_role_permission_table.h"
#include "Database/Migrations/Main/Migration_2022_12_08_10_19_41_create_account_role_table.h"
#include "Database/Migrations/Main/Migration_2022_12_08_18_38_47_create_console_permission_table.h"

class MigrationObject
{
public:
    std::uint_fast64_t m_id;
    std::string m_name;

    std::map<std::string, std::map<std::string, std::int_fast32_t>> getColumnList()
    {
        return {
            {"id",   {{"position", 0}, {"type", Config::Global::data_types::type_uint64}}},
            {"name", {{"position", 1}, {"type", Config::Global::data_types::type_string}}},
        };
    }

    void setMember(
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
                m_name = string_value;
                break;
            default:
                MEL_ERROR("column of position {0} was not found", order);
        }
    }
};

class MigrationManager
{
private:
    template<typename T>
    static void runMigration(const std::vector<MigrationObject> &migrations, bool &nothing_to_migrate)
    {
        T migration;

        bool not_migrated = std::none_of(
            migrations.begin(),
            migrations.end(),
            [&migration](const MigrationObject &object) {
                return object.m_name == migration.getMigrationName();
            }
        );

        if (not_migrated) {
            migration.up();

            saveMigration(migration.getMigrationName());

            nothing_to_migrate = false;
        }
    }

    template<typename T>
    static void refreshMigration()
    {
        T migration;

        migration.down();
        migration.up();

        saveMigration(migration.getMigrationName());
    }

    static void saveMigration(const std::string &migration)
    {
        DB::unprepared(
            "INSERT INTO " + Config::Main::Database::name + ".migrations (`name`) VALUES (\"" + migration + "\")"
        );
    }

public:
    static void update()
    {
        std::vector<MigrationObject> executed_migrations;

        if (!DB::tableExists(Config::Main::Database::name, "migrations")) {
            Migration_2022_12_05_13_15_28_create_migrations_table migration;
            migration.up();
            saveMigration(migration.getMigrationName());
        } else {
            executed_migrations = DB::all<MigrationObject>(
                "SELECT * FROM " + Config::Main::Database::name + ".migrations"
            );
        }

        bool nothing_to_migrate = true;

        runMigration<Migration_2022_11_27_01_47_07_create_accounts_table>(executed_migrations, nothing_to_migrate);
        runMigration<Migration_2022_12_05_12_20_44_create_roles_table>(executed_migrations, nothing_to_migrate);
        runMigration<Migration_2022_12_08_10_00_45_create_permissions_table>(executed_migrations, nothing_to_migrate);
        runMigration<Migration_2022_12_08_10_19_31_create_role_permission_table>(executed_migrations,
                                                                                 nothing_to_migrate);
        runMigration<Migration_2022_12_08_10_19_41_create_account_role_table>(executed_migrations, nothing_to_migrate);
        runMigration<Migration_2022_12_08_18_38_47_create_console_permission_table>(executed_migrations,
                                                                                    nothing_to_migrate);

        if (nothing_to_migrate) {
            MEL_INFO("nothing to migrate");
        }
    }

    static void fresh()
    {
        refreshMigration<Migration_2022_12_05_13_15_28_create_migrations_table>();
        refreshMigration<Migration_2022_11_27_01_47_07_create_accounts_table>();
        refreshMigration<Migration_2022_12_05_12_20_44_create_roles_table>();
        refreshMigration<Migration_2022_12_08_10_00_45_create_permissions_table>();
        refreshMigration<Migration_2022_12_08_10_19_31_create_role_permission_table>();
        refreshMigration<Migration_2022_12_08_10_19_41_create_account_role_table>();
        refreshMigration<Migration_2022_12_08_18_38_47_create_console_permission_table>();
    }

    static void create(const std::string &path)
    {
        std::string folder;
        std::string name;

        if (path.find('/') != std::string::npos) {
            auto segments = String::explode(path, "/");

            folder = segments.at(0);
            name = segments.at(1);
        } else {
            name = path;
        }

        std::string absolute_path = Config::Global::project_path + "/Database/Migrations";

        if (!folder.empty()) {
            absolute_path += "/" + folder;

            if (!std::filesystem::exists(absolute_path)) {
                std::filesystem::create_directory(absolute_path);

                std::ofstream cmake_lists(absolute_path + "/CMakeLists.txt");
                cmake_lists.close();

                std::ofstream upper_cmake_lists;
                upper_cmake_lists.open(Config::Global::project_path + "/Database/Migrations/CMakeLists.txt",
                                       std::ios::app);
                upper_cmake_lists << "add_subdirectory(" + folder + ")\n";
                upper_cmake_lists.close();
            }
        }

        std::string datetime = DateTime::getCurrentInFormat("%Y_%m_%d_%H_%M_%S");

        std::string base_name = datetime + "_" + name;
        std::string migration_name = "Migration_" + base_name;
        std::string migration_name_upper = String::toUpper(migration_name);

        std::ofstream header(absolute_path + "/" + migration_name + ".h");

        //<editor-fold desc="file content">
        header <<
               "#ifndef MELLIANCORE_" + migration_name_upper + "_H\n" +
               "#define MELLIANCORE_" + migration_name_upper + "_H\n" +
               "\n"
               "#include \"Migration.h\"\n"
               "#include \"Config.h\"\n"
               "#include \"Support/Log/Log.h\"\n"
               "\n"
               "class " + migration_name + " : public Migration\n" +
               "{\n"
               "public:\n"
               "    void up() override\n"
               "    {\n"
               "        createTable(\"\");\n"
               "\n"
               "        setColumns(\"\");\n"
               "\n"
               "        execute();\n"
               "\n"
               "        MEL_INFO(\"" + base_name + " migrated\");\n" +
               "    }\n"
               "\n"
               "    void down() override\n"
               "    {\n"
               "        dropTable(\"\");\n"
               "\n"
               "        execute();\n"
               "\n"
               "        MEL_INFO(\"" + base_name + " dropped\");\n" +
               "    }\n"
               "\n"
               "    std::string getSchemaName() override\n"
               "    {\n"
               "        return Config::" + folder + "::Database::name;\n" +
               "    }\n"
               "\n"
               "    std::string getMigrationName() override\n"
               "    {\n"
               "        return \"" + migration_name + "\";\n" +
               "    }\n"
               "};\n"
               "\n"
               "#endif //MELLIANCORE_" + migration_name_upper + "_H\n";
        //</editor-fold>

        header.close();

        std::ofstream cmake_lists;

        cmake_lists.open(absolute_path + "/CMakeLists.txt", std::ios::app);

        cmake_lists
            << "\nadd_library(" + migration_name + " " + migration_name + ".h)\n" +
               "set_target_properties(" + migration_name + " PROPERTIES LINKER_LANGUAGE CXX)\n" +
               "target_include_directories(" + migration_name +
               " PUBLIC \"${PROJECT_SOURCE_DIR}/Core/Database/Migration\")\n" +
               "target_include_directories(" + migration_name + " PUBLIC \"${PROJECT_SOURCE_DIR}/Config\")\n" +
               "target_link_libraries(" + migration_name + " PUBLIC Migration Config)\n";

        cmake_lists.close();

        MEL_INFO("{0} created", migration_name);
    }
};

#endif //MELLIANCORE_MIGRATIONMANAGER_H
