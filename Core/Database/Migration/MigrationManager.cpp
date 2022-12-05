#include <filesystem>
#include <fstream>
#include <string>
#include "Core/Support/String/String.h"
#include "Core/Support/DateTime/DateTime.h"
#include "Core/Database/DB/DB.h"
#include "Config/Config.h"
#include "MigrationManager.h"
#include "Database/Migrations/Main/Migration_2022_12_05_13_15_28_create_migrations_table/Migration_2022_12_05_13_15_28_create_migrations_table.h"
#include "Database/Migrations/Auth/2022_11_27_01_47_07_create_accounts_table/Migration_2022_11_27_01_47_07_create_accounts_table.h"
#include "Database/Migrations/Main/Migration_2022_12_05_12_20_44_create_roles_table/Migration_2022_12_05_12_20_44_create_roles_table.h"

void MigrationManager::update()
{
    ensureMigrationTableExists();

    //<editor-fold desc="Auth">
    runMigration<Migration_2022_11_27_01_47_07_create_accounts_table>();
    //</editor-fold>

    //<editor-fold desc="Main">
    runMigration<Migration_2022_12_05_12_20_44_create_roles_table>();
    //</editor-fold>
}

void MigrationManager::fresh()
{
    ensureMigrationTableExists();

    //<editor-fold desc="Auth">
    runMigration<Migration_2022_11_27_01_47_07_create_accounts_table>(true);
    //</editor-fold>

    //<editor-fold desc="Main">
    runMigration<Migration_2022_12_05_12_20_44_create_roles_table>(true);
    //</editor-fold>
}

void MigrationManager::create(const std::string &path)
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
            upper_cmake_lists.open(Config::Global::project_path + "/Database/Migrations/CMakeLists.txt", std::ios::app);
            upper_cmake_lists << "add_subdirectory(" + folder + ")\n";
            upper_cmake_lists.close();
        }
    }

    // migrate create Main/create_roles_table
    std::string datetime = DateTime::getCurrentInFormat("%Y_%m_%d_%H_%M_%S");

    std::string base_name = datetime + "_" + name;
    std::string migration_name = "Migration_" + base_name;
    std::string migration_name_upper = String::toUpper(migration_name);

    std::filesystem::create_directory(absolute_path + "/" + migration_name);

    std::ofstream header(absolute_path + "/" + migration_name + "/" + migration_name + ".h");

    header <<
           "#ifndef MELLIANCORE_" + migration_name_upper + "_H\n" +
           "#define MELLIANCORE_" + migration_name_upper + "_H\n" +
           "\n"
           "#include \"Migration.h\"\n"
           "\n"
           "class " + migration_name + " : public Migration\n" +
           "{\n"
           "public:\n"
           "    void up() override;\n"
           "\n"
           "    void down() override;\n"
           "\n"
           "    std::string getSchemaName() override;\n"
           "\n"
           "    std::string getMigrationName() override;\n"
           "};\n"
           "\n"
           "#endif //MELLIANCORE_" + migration_name_upper + "_H\n";

    header.close();

    std::ofstream cpp(absolute_path + "/" + migration_name + "/" + migration_name + ".cpp");

    cpp <<
        "#include \"" + migration_name + ".h\"\n" +
        "#include \"Config.h\"\n"
        "\n"
        "void " + migration_name + "::up()\n{\n" +
        "    createTable(\"\");\n"
        "\n"
        "    setColumns(\"\");\n"
        "\n"
        "    execute();\n"
        "\n"
        "    std::cout << \"" + base_name + " migrated\" << std::endl;\n" +
        "}\n"
        "\n"
        "void " + migration_name + "::down()\n{\n" +
        "    dropTable(\"\");\n"
        "\n"
        "    execute();\n"
        "\n"
        "    std::cout << \"" + base_name + " migrated\" << std::endl;\n" +
        "}\n"
        "\n"
        "std::string " + migration_name + "::getSchemaName()\n{\n" +
        "    return Config::" + folder + "::Database::name;\n" +
        "}\n"
        "\n"
        "std::string " + migration_name + "::getMigrationName()\n{\n" +
        "    return \"" + migration_name + "\";\n" +
        "}\n";

    cpp.close();

    std::ofstream cmake_lists;

    cmake_lists.open(absolute_path + "/CMakeLists.txt", std::ios::app);

    cmake_lists
        << "\nadd_library(" + migration_name + " " + migration_name + "/" + migration_name + ".h " + migration_name +
           "/" + migration_name + ".cpp)\n" +
           "target_include_directories(" + migration_name +
           " PUBLIC \"${PROJECT_SOURCE_DIR}/Core/Database/Migration\")\n" +
           "target_include_directories(" + migration_name + " PUBLIC \"${PROJECT_SOURCE_DIR}/Config\")\n" +
           "target_link_libraries(" + migration_name + " PUBLIC Migration Config)\n";

    cmake_lists.close();

    std::cout << migration_name << " created" << std::endl;
}

template<typename T>
void MigrationManager::runMigration(const bool fresh)
{
    T migration;

    if (fresh) {
        migration.down();
    }

    migration.up();

    DB::unprepared(
        "INSERT INTO " + Config::Main::Database::name + ".migrations (`name`) VALUES (\"" +
        migration.getMigrationName() + "\")"
    );
}

void MigrationManager::ensureMigrationTableExists()
{
    if (!DB::tableExists(Config::Main::Database::name, "migrations")) {
        runMigration<Migration_2022_12_05_13_15_28_create_migrations_table>();
    }
}
