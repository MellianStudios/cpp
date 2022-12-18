### prerequisites
- mysqlcppconn 8.0.x

### install
1. mkdir build
2. cmake -S . -B build/ -DSERVER_TARGET_PATH=/path_to_where_you_want_executables_and_config
3. .env by default contains only required settings you are free to override any other setting by adding it to .env you can find list of all settings in Config/Config.cpp

#### currently you have to change path in Core/Support/DotEnv/DotEnv.cpp to run this program

- if you want to run it in IDE you need absolute path to project .env in DotEnv
- if you want to run it as standalone executable you need relative path to .env in DotEnv
- if you want to work with this program you can create .env in project root
